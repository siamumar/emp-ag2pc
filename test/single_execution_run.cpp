#include <emp-tool/emp-tool.h>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <cstdlib>
#include "emp-ag2pc/emp-ag2pc.h"
#include "test/util.h"

using namespace std;
using namespace emp;
namespace po = boost::program_options;

const string circuit_file_location = macro_xstr(EMP_CIRCUIT_PATH);

string single_execution_run(int party, NetIO* io, string circuit_file_address, string input_hex_str = "") {
	uint64_t c0, dc;
	double t0, dt;
	
	BristolFormat cf(circuit_file_address.c_str());
	start_timer(c0, t0);
	C2PC <NetIO> twopc(io, party, &cf);
	io->flush();
	get_timer(c0, dc, t0, dt);
	cout << "one:\t" << dc << "\tcc\t" << dt << "\tms" << endl;

	start_timer(c0, t0);
	twopc.function_independent();
	io->flush();
	get_timer(c0, dc, t0, dt);
	cout << "inde:\t" << dc << "\tcc\t" << dt << "\tms" << endl;

	start_timer(c0, t0);
	twopc.function_dependent();
	io->flush();
	get_timer(c0, dc, t0, dt);
	cout << "dep:\t" << dc << "\tcc\t" << dt << "\tms" << endl;
	
	int input_bit_width;
	if (party == ALICE){
		input_bit_width = cf.n1;
		start_timer(c0, t0);
		io->send_data(&input_bit_width, sizeof(int));
		get_timer(c0, dc, t0, dt);
		cout << "send:\t" << dc << "\tcc\t" << dt << "\tms" << endl;
	}
	else{
		input_bit_width = cf.n2;
		io->recv_data(&input_bit_width, sizeof(int));
		cout << input_bit_width << endl;
	}
	
	bool *in = new bool[input_bit_width];
	fill_input (in, input_hex_str, input_bit_width);
	
	bool *out = new bool[cf.n3];
	memset(out, false, cf.n3);	
	
	start_timer(c0, t0);
	twopc.online(in, out);
	get_timer(c0, dc, t0, dt);
	cout << "online:\t" << dc << "\tcc\t" << dt << "\tms" << endl;
	
	string output_hex_str = read_output(out, cf.n3);
	
	delete[] in;
	delete[] out;
	
	return output_hex_str;
}

int main(int argc, char* argv[]) {
	int party, port;
	string circuit_file_address;
	string server_ip;
	string input_hex_str;
	
	po::options_description desc{"EMP Authenticated Garbling Two party \nAllowed options"};
	desc.add_options()  //
	("help,h", "produce help message")  //
	("party,k", po::value<int>(&party)->default_value(1), "party id: 1 for garbler, 2 for evaluator")  //
	("circuit_file,c", po::value<string>(&circuit_file_address)->default_value(circuit_file_location + "adder_32bit.txt"), "circuit file address.")  //
	("port,p", po::value<int>(&port)->default_value(1234), "socket port")  //
	("server_ip,s", po::value<string>(&server_ip)->default_value(IP), "server's IP.")  //
	("input,i", po::value<string>(&input_hex_str)->default_value(""),"hexadecimal input (little endian).");
	
	po::variables_map vm;
	try {
		po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
		po::store(parsed, vm);
		if (vm.count("help")) {
			cout << desc << endl;
			return 0;
		}
		po::notify(vm);
	}catch (po::error& e) {
		cout << "ERROR: " << e.what() << endl << endl;
		cout << desc << endl;
		return -1;
	}
	
	/*cout << party << endl;
	cout << port << endl;
	cout << circuit_file_address << endl;
	cout << server_ip << endl;
	cout << input_hex_str << endl;*/
	
	NetIO* io = new NetIO(party==ALICE ? nullptr:server_ip.c_str(), port);
	io->set_nodelay();
	string output_hex_str = single_execution_run(party, io, circuit_file_address, input_hex_str);
	cout << "Party " << party << "\nInput\t" << input_hex_str << "\nOutput\t" << output_hex_str << endl;
	
	delete io;
	return 0;
}