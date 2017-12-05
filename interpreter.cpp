// interpreter.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include "parser.h"


int main(int argc, char** args) {
	//If openning from file.
	if (argc > 1) {
		std::ifstream in(args[1]);
		if (in.good()) {
			Parser parser(in); //initiate parser with fstream as input
			parser.program();
			in.close();
		}
		else {
			std::cout << "Invalid input file\n";
		}
	}
	//else interactive interpreter.
	else {
		Parser parser; //initiate parser with cin as input
		parser.program();
	}

	return 0;
}
