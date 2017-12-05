#include "lexer.h"

//
// LEXER CLASS
//
Lexer::Lexer() {}
Lexer::~Lexer() {}

void Lexer::readch() { //read next char
	if (input)
		input >> peek;
	else {
		peek = 0;
	}
}

Token* Lexer::scan() { //scan next Token
	for (; ; readch()) { //ignore whitespace until shomething else is read.
		if (peek == ' ' || peek == '\t' || peek == '\n') {
			continue;
		}
		else {
			break;
		}
	}

	if (isdigit(peek)) { //digit was found, make Num
		int v = 0;

		do {
			v = v * 10 + (peek - '0');
			readch();
		} while (isdigit(peek));
		return new Num(v);
	}

	if (isalpha(peek) || peek == '_') { //letter or '_' found, make Word
		std::string b;
		do {
			b += peek;
			readch();
		} while (isalnum(peek) || peek == '_'); //add to word name as long as alphanumeric or '_'

		if (words.count(b) == 0) {//if not already in words, add it.
			Word w(b, Tag().ID);
			words.insert(std::pair<std::string, Word>(b, Word(b, Tag().ID)));
		}
		return &words[b];
	}

	Token* t = new Token(peek); //if not word or num, make whatever a new token.
	peek = ' ';
	return t;
}

