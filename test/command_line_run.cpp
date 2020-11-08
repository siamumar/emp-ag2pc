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


// string hex2bin(string hex_){
// 	uint16_t len = hex_.length();
// 	string bin("");
	
// 	for (uint64_t i = 0; i < len; i++){
// 		char H = hex_.at(i);
// 		string B;
// 		if(H == '0') B = "0000";
// 		else if(H == '1') B = "0001";
// 		else if(H == '2') B = "0010";
// 		else if(H == '3') B = "0011";
// 		else if(H == '4') B = "0100";
// 		else if(H == '5') B = "0101";
// 		else if(H == '6') B = "0110";
// 		else if(H == '7') B = "0111";
// 		else if(H == '8') B = "1000";
// 		else if(H == '9') B = "1001";
// 		else if((H == 'a')||(H == 'A')) B = "1010";
// 		else if((H == 'b')||(H == 'B')) B = "1011";
// 		else if((H == 'c')||(H == 'C')) B = "1100";
// 		else if((H == 'd')||(H == 'D')) B = "1101";
// 		else if((H == 'e')||(H == 'E')) B = "1110";
// 		else if((H == 'f')||(H == 'F')) B = "1111";
// 		bin = bin + B;
// 	}
// 	return bin;
// }

// string bin2hex(string bin){
// 	uint16_t len = bin.length();
// 	if (len%4) bin.insert(0, 4-len%4, '0');
// 	len = bin.length();
// 	string hex_("");
	
// 	for (uint64_t i = 0; i < len; i+=4){
// 		string B = bin.substr(i, 4);
// 		string H;
// 		if(B == "0000") H = "0";
// 		else if(B == "0001") H = "1";
// 		else if(B == "0010") H = "2";
// 		else if(B == "0011") H = "3";
// 		else if(B == "0100") H = "4";
// 		else if(B == "0101") H = "5";
// 		else if(B == "0110") H = "6";
// 		else if(B == "0111") H = "7";
// 		else if(B == "1000") H = "8";
// 		else if(B == "1001") H = "9";
// 		else if(B == "1010") H = "A";
// 		else if(B == "1011") H = "B";
// 		else if(B == "1100") H = "C";
// 		else if(B == "1101") H = "D";
// 		else if(B == "1110") H = "E";
// 		else if(B == "1111") H = "F";
// 		hex_ = hex_ + H;
// 	}
// 	return hex_;
// }

// void fill_input(bool *in, string input_hex_str, int input_bit_width){	
// 	memset(in, false, input_bit_width);
	
// 	string input_bin_str = hex2bin(input_hex_str);
// 	int d = input_bin_str.size() - input_bit_width;
// 	if(d > 0)	
// 		for (int i = 0; i < input_bit_width; ++i)
// 			in[input_bit_width-i-1] = (input_bin_str[i+d] == '1')? true:false;
// 	else
// 		for (int i = 0; i < int(input_bin_str.size()); ++i)
// 			in[input_bin_str.size()-i-1] = (input_bin_str[i] == '1')? true:false;
// }

// string read_output(bool *out, int output_bit_width){	
// 	string  output_hex_str, output_bin_str = "";
// 	for(int i = output_bit_width-1; i >= 0; --i)
// 			output_bin_str += (out[i]?"1":"0");

// 	output_hex_str = bin2hex(output_bin_str);
	
// 	return output_hex_str;	
// }

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