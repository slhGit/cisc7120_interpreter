// classes.h
// By: Sanders Hernandez
//
// Classes for the Parse Tree nodes. And the symbol table.
//

#pragma once
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <set>

#include "lexer.h"

//
//NODES FOR THE PARSE TREE
//

//Base Class for other Parse Tree Nodes
class Expr {
public:
	Expr(Token* tok);
	~Expr();
	Token* op; 

	virtual std::string toString();

	virtual int eval(); // returns the value of the expression.
};

//Node for numbers
class Constant : public Expr {
public:
	Constant(Token*);
	Constant(int);
	virtual int eval(); // returns the value of the expression.
};

//Node for Variables
class Id : public Expr {
public:
	Id(Word*, int);
	int value;
	bool init = false;
	
	virtual int eval(); // returns the value of the expression.
};

//Node for Arithmetic Expressions
class Arith : public Expr {
public:
	Arith(Token*, Expr*, Expr*);
	~Arith();
	Expr* expr1;
	Expr* expr2;

	virtual std::string toString();
	virtual int eval(); // returns the value of the expression.
};

//Node for Unary Expressions
class Unary : public Expr {
public:
	Unary(Token*, Expr*);
	~Unary();
	Expr* expr;

	virtual std::string toString();
	virtual int eval(); // returns the value of the expression.
};

//Node for Assignments, an Assignment is the root of any given Parse Tree here.
class Assignment {
public:
	Assignment();
	Assignment(Id*, Expr*);
	~Assignment();

	virtual void eval(); // evaluates expr, assigns its value to id->value.

	Id* id;
	Expr* expr;
};



//
//Class for the symbol table
//
class SymbolTable {
public:
	SymbolTable();

	void put(Token*, Id*);
	Id* get(Token*);
	void remove(Token*);
private:
	//The table is a map from Tokens to Ids
	std::map<Token*, Id*> table;
};