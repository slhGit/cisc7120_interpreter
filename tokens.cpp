// tokens.cpp
// By: Sanders Hernandez
//
// class function definitions for Tokens
//

#include "tokens.h"

// TOKEN
Token::Token(int t) : tag(t) {}

std::string Token::toString() { 
	return std::string(1, char(tag)); 
}

bool operator<(const Token& A, const Token& B) { 
	return A.tag < B.tag; 
}


// NUM
Num::Num(int v) : Token(Tag().NUM), value(v) {}

std::string Num::toString() { 
	return std::to_string(value); 
}

// WORD
Word::Word() : Token(0), lexeme("") {}
Word::Word(std::string s, int tag) : Token(tag), lexeme(s) {}

std::string Word::toString() { return lexeme; }


Word* Word::minus = new Word("minus", Tag().MINUS);
Word* Word::plus = new Word("plus", Tag().PLUS);
