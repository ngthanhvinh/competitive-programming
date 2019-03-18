#include <fstream>
#include <iostream>
#include <cmath>

const double EPS = 1.0;

int main(int argc, char** argv){
	std::ifstream foutput(argv[3]);
	std::ifstream fpattern(argv[2]);
	double output, pattern;
	foutput >> output;
	fpattern >> pattern;
	if(fabs(output - pattern) < EPS){
		std::cout << 1;
		std::cerr << "translate:success";
		return 0;
	}
	std::cout << 0;
	std::cerr << "translate:wrong";
	return 0;
}
