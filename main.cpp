#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <algorithm>


#define M_REM(a, b) ((a) - (int32_t)((a) / (b)) * (b))


std::string ToBinary(int decimal, size_t bit_size) {
	const size_t DIFF_SIZE = bit_size - 1;
 std::vector<char> binary(bit_size);
 
	size_t current_size = bit_size;
	
	while(current_size > 0) {
		current_size--;
		char current_bit = ((decimal << current_size) >> DIFF_SIZE) & 1;
		binary.at(current_size) = (current_bit ? '1' : '0');
	}
	return std::string(binary.data());
}



std::string ToOctal(int decimal) {
	const size_t OCTAL_BASE = 8;
	const float INV_OCTAL_BASE = 0.125;
	
	std::vector<char> octal;
	
	while(decimal != 0) {
		octal.push_back('0' + M_REM(decimal, OCTAL_BASE)); 
  decimal = static_cast<int>(
   static_cast<float>(decimal) * INV_OCTAL_BASE);
	}
	std::reverse(octal.begin(), octal.end());
	
	return std::string(octal.data());
}



std::string ToHexadecimal(int decimal, size_t bytes_size, bool start_hex, bool upercase) {
	const size_t HEX_BASE = 16;
	const float INV_HEX_BASE = 0.0625;
	
	std::vector<char> hex((bytes_size * 2) + (start_hex ? 2 : 0));

	std::fill(hex.begin(), hex.end(), '0');
	
	if(start_hex) {
 	hex.at(0) = '0';
	 hex.at(1) = 'x';
	}
	
	int i = hex.size()-1;
	while(decimal != 0) {
		
		int r = M_REM(decimal, HEX_BASE);
		
		hex.at(i--) = (r < 9 ? ('0' + r) : ((upercase ? 'A' : 'a') + (r-10))); 
  decimal = static_cast<int>(
   static_cast<float>(decimal) * INV_HEX_BASE);
	}
	return std::string(hex.data());
}


int main() {
	
	int decimal;
	
	std::cout << "Input Number : ";
	std::cin >> decimal;

	//4 byte hex
	std::cout << "Hex    : " << ToHexadecimal(decimal, 4, true, true) << std::endl;
	std::cout << "Octal  : " << ToOctal(decimal) << std::endl;
	// 32 bit binary
	std::cout << "Binary : " << ToBinary(decimal, 32) << std::endl;

	return 0;
}
