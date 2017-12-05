// tokens.h
// By: Sanders Hernandez
//
// Token class prototypes.
//

#pragma once
#include <string>
#include <iostream>

//
// Token Classes
//

// Used for identifying tokens
class Tag {
public:
	static const int
		ID = 256, NUM = 257, MINUS = 258, PLUS = 259; // tags for non char Tokens
};
// Base class
class Token {
public:
	Token(int);

	const int tag;
	virtual std::string toString(); 
	friend bool operator<(const Token&, const Token&); //Comparison operator, needed so Token can be added to a map.
};


// Token for numbers
class Num : public Token {
public:
	Num(int);

	const int value;
	std::string toString();
};


// Token for Ids
class Word : public Token {
public:
	Word();
	Word(std::string, int);

	const std::string lexeme;
	std::string toString();

	static Word* minus; //used when constructing Unary parser tree nodes
	static Word* plus;  //used when constructing Unary parser tree nodes
};