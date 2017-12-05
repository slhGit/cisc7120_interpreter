////////////////
//
// Lexer prototype.
//
// By: Sanders Hernandez
//
/////////////////


#pragma once
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

#include "tokens.h"
//
// LEXER CLASS
//
class Lexer {
public:
	Lexer();
	~Lexer();

	std::stringstream input; //The input for the lexer is a string stream that is maintained in the parser.
 	char peek = ' ';

	std::map<std::string, Word> words; //Words already made

	void readch(); //read next char

	Token* scan(); //scan next Token of input
};
