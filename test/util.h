#include <string>

string hex2bin(string hex_){
	uint16_t len = hex_.length();
	string bin("");
	
	for (uint64_t i = 0; i < len; i++){
		char H = hex_.at(i);
		string B;
		if(H == '0') B = "0000";
		else if(H == '1') B = "0001";
		else if(H == '2') B = "0010";
		else if(H == '3') B = "0011";
		else if(H == '4') B = "0100";
		else if(H == '5') B = "0101";
		else if(H == '6') B = "0110";
		else if(H == '7') B = "0111";
		else if(H == '8') B = "1000";
		else if(H == '9') B = "1001";
		else if((H == 'a')||(H == 'A')) B = "1010";
		else if((H == 'b')||(H == 'B')) B = "1011";
		else if((H == 'c')||(H == 'C')) B = "1100";
		else if((H == 'd')||(H == 'D')) B = "1101";
		else if((H == 'e')||(H == 'E')) B = "1110";
		else if((H == 'f')||(H == 'F')) B = "1111";
		bin = bin + B;
	}
	return bin;
}

string bin2hex(string bin){
	uint16_t len = bin.length();
	if (len%4) bin.insert(0, 4-len%4, '0');
	len = bin.length();
	string hex_("");
	
	for (uint64_t i = 0; i < len; i+=4){
		string B = bin.substr(i, 4);
		string H;
		if(B == "0000") H = "0";
		else if(B == "0001") H = "1";
		else if(B == "0010") H = "2";
		else if(B == "0011") H = "3";
		else if(B == "0100") H = "4";
		else if(B == "0101") H = "5";
		else if(B == "0110") H = "6";
		else if(B == "0111") H = "7";
		else if(B == "1000") H = "8";
		else if(B == "1001") H = "9";
		else if(B == "1010") H = "A";
		else if(B == "1011") H = "B";
		else if(B == "1100") H = "C";
		else if(B == "1101") H = "D";
		else if(B == "1110") H = "E";
		else if(B == "1111") H = "F";
		hex_ = hex_ + H;
	}
	return hex_;
}

void fill_input(bool *in, string input_hex_str, int input_bit_width){	
	memset(in, false, input_bit_width);
	
	string input_bin_str = hex2bin(input_hex_str);
	int d = input_bin_str.size() - input_bit_width;
	if(d > 0)	
		for (int i = 0; i < input_bit_width; ++i)
			in[input_bit_width-i-1] = (input_bin_str[i+d] == '1')? true:false;
	else
		for (int i = 0; i < input_bin_str.size(); ++i)
			in[input_bin_str.size()-i-1] = (input_bin_str[i] == '1')? true:false;
}

string read_output(bool *out, int output_bit_width){	
	string  output_hex_str, output_bin_str = "";
	for(int i = output_bit_width-1; i >= 0; --i)
			output_bin_str += (out[i]?"1":"0");

	output_hex_str = bin2hex(output_bin_str);
	
	return output_hex_str;	
}