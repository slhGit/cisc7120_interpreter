#pragma once
#include "parser.h"


Parser::Parser() : symbol(new SymbolTable), input(std::cin) {}
Parser::Parser(std::ifstream& in) : symbol(new SymbolTable), input(in) {}
Parser::~Parser() { delete look; delete symbol; }

void Parser::move() { // Have the lexer scan the next token.
	look = lex.scan();
}

void Parser::error(std::string n) { // Print an error
	std::cout << "ERROR: " + n << std::endl;
	parseError = true;
}

// check if the current token matches an expected tag, if so, move to next token, else report error. 
void Parser::match(int t) {
	if (look->tag == t) {
		move();
	}
	else {
		char c = t;
		std::string s = "Expected: '";
		switch (t) {
		case 256:
			s += "an Id";
			break;
		case 257:
			s += "a Constant";
			break;
		case 258:
			s += "-";
			break;
		case 259:
			s += "+";
			break;
		default:
			s += c;
		}
		s += "'";
		error(s);
	}
}

// main program loop for parser
void Parser::program() {
	std::string temp, in;

	while (input >> temp) { // do as long as there is input.
		int i = temp.find_last_of(";"); // find inf there is a ";" in input
		if (i < temp.length()) { // if so, parse assignment.
			in += temp.substr(0, i + 1);
			lex.input << in;
			move();

			while (look->tag != 0) {
				Assignment* a = assignment();
				if (parseError) { //if there was an error parsing, do not evaluate, and remove assignment id from symbol table, if exists.
					if (a->id && !a->id->init) {
						symbol->remove(a->id->op);
					}
					parseError = false; //reset parseError
				}
				else {
					a->eval(); //if parse without error, evaluate.
				}
			}
			lex.input.str(""); // reset lexer input.
			lex.input.clear();
			
			in = temp.substr(i + 1); // if there was any input after the ";" set that as the new input.
		}
		else {
			in += temp; // If a ";" has not been found, continue to concactinate input.
		}
	}
}

// parse and assignment
Assignment* Parser::assignment() {
	Assignment* stmt;
	Token* t = look;

	match(Tag().ID); //Assignment should start with and Id.

	Id* id = symbol->get(t); //Find Id in sympol table, if not there, make one and add it.
	if (id == NULL) {
		id = new Id(dynamic_cast<Word*>(t), 0);
		symbol->put(t, id);
	}

	match('='); //Next should be an equals sign
	stmt = new Assignment(id, expr()); //Create the root node of the parse tree

	match(';'); //should end with a ";'

	return stmt;
}

//parse an expr
Expr* Parser::expr() {
	Expr* x = term(); // Expression begin with a term.
	while (look->tag == '+' || look->tag == '-') { // as long as there are +/-'s create nested Ariths: a + (b - (c + d))) etc
		Token* tok = look;
		move();
		x = new Arith(tok, x, term());
	}
	return x;
}

//parse term
Expr* Parser::term() {
	Expr* x = fact(); // Terms begin with fact's 
	while (look->tag == '*') { // as long as there are mults, create nests Arith's a * (b * (c * ... )))
		Token* tok = look;
		move();
		x = new Arith(tok, x, fact());
	}
	return x;
}

//parse fact
Expr* Parser::fact() {
	Expr* x = NULL;
	switch (look->tag) {
	case '(':  // fact -> ( expr )
		move();
		x = expr();
		match(')');
		return x;
	case '-': { // fact => -fact
		move();
		Unary* x = new Unary(Word().minus, fact());
		return x;
	}
	case '+': // fact -> +fact
		move();
		return new Unary(Word().plus, fact());
	case Tag().NUM: // fact -> NUM
		x = new Constant(look);
		move();
		return x;
	case Tag().ID: { // fact -> Id
		Id* id = symbol->get(look);

		if (id == NULL) {
			error(look->toString() + " undeclared");
		}
		move();
		return id;
	}
	default: // Error
		error("Expected one of: (, +, -, Num, Id");
		return x;
	}
}




