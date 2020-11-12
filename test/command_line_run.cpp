//#include <emp-tool/emp-tool.h>
//#include "emp-ag2pc/emp-ag2pc.h"
#include <boost/program_options.hpp>
#include <boost/format.hpp>
//#include <cstdlib>
//#include "test/single_execution.h"
#include "test/command_line_utils.hpp"

using namespace std;
using namespace emp;
using namespace boost::program_options;

template<typename T>
string single_execution_run(int party, T* io, string name, string input_hex_str = "", string check_output = "") {
    string file = name; //set the file name to input of circuit_file_location + name;
    BristolFormat cf(file.c_str()); //initializ BristolFormat 
    // .c_str class Return const pointer to String, turns string into a class variable
    
    auto t1 = clock_start(); // start clock and set variable as t1, assume type with auto
    C2PC<T> twopc(io, party, &cf); //instantiate class C2PC
    io -> flush();
    cout << "one time:\t" << party << "\t" << time_from(t1) << endl;

    t1 = clock_start();
    twopc.function_independent();
    io -> flush();
    cout << "inde:\t" << party << "\t" << time_from(t1) << endl;

    t1 = clock_start();
    twopc.function_dependent();
    io -> flush();
    cout << "dep:\t" << party << "\t" << time_from(t1) << endl; //some sort of testing

    bool *in = new bool[max(cf.n1, cf.n2)]; // initialize boolean array
    bool * out = new bool[cf.n3];
    //memset(in, false, max(cf.n1, cf.n2));
    fill_input (in, input_hex_str, max(cf.n1, cf.n2));
    memset(out, false, cf.n3);

    t1 = clock_start();
    twopc.online(in, out, true);
    cout << "online:\t" << party << "\t" << time_from(t1) << endl;

    string output_hex_str = read_output(out, cf.n3);

    if (check_output.size() > 0){
        string res = "";
        for (int i=0; i < cf.n3; ++i) 
            res += (out[i] ? "1" : "0");
        cout << (res == hex_to_binary(check_output) ? "GOOD!" : "BAD!") << endl;
    } 

	delete[] in;
	delete[] out;

    return output_hex_str;
}

int main(int argc, char* argv[]) {
	int party, port;
	string circuit_file_address;
	string server_ip;
	string input_hex_str;
	
	options_description desc{"EMP Authenticated Garbling Two party \nAllowed options"};
	desc.add_options()  //
	("help,h", "produce help message")  //
	("party,k", value<int>(&party)->default_value(1), "party id: 1 for garbler, 2 for evaluator")  //
	("circuit_file,c", value<string>(&circuit_file_address)->default_value(circuit_file_location + "adder_32bit.txt"), "circuit file address.")  //
	("port,p", value<int>(&port)->default_value(1234), "socket port")  //
	("server_ip,s", value<string>(&server_ip)->default_value(IP), "server's IP.")  //
	("input,i", value<string>(&input_hex_str)->default_value(""),"hexadecimal input (little endian).");
	
	variables_map vm;
	try {
		parsed_options parsed = command_line_parser(argc, argv).options(desc).allow_unregistered().run();
		store(parsed, vm);
		if (vm.count("help")) {
			cout << desc << endl;
			return 0;
		}
		notify(vm);
	}catch (boost::program_options::error& e) {
		cout << "ERROR: " << e.what() << endl << endl;
		cout << desc << endl;
		return -1;
	}
	
	NetIO* io = new NetIO(party==ALICE ? nullptr:server_ip.c_str(), port);
	io->set_nodelay();
	string output_hex_str = single_execution_run(party, io, circuit_file_address, input_hex_str);
	cout << "Party " << party << "\nInput\t" << input_hex_str << "\nOutput\t" << output_hex_str << endl;
	
	delete io;
	return 0;
}