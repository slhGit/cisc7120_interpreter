// Parser.h
// By: Sanders Hernandez
//
// The Parser Prototype.
//



#pragma once
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <set>

#include "lexer.h"
#include "classes.h"

//Parser class
class Parser {
public:
	Parser(); 
	Parser(std::ifstream&);
	~Parser();

	void move();
	void error(std::string n);
	void match(int t);

	void program(); // Parse program

	Assignment* assignment();  // Parse assignment
	Expr* expr(); // Parse expr
	Expr* term(); // Parse term
	Expr* fact(); // Parse fact

private:
	std::istream& input;
	Lexer lex;
	Token* look = NULL;
	SymbolTable* symbol;
	int used = 0;
	bool parseError = false;
};



