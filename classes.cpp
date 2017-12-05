// classes.cpp
// By: Sanders Hernandez
//
// Definitions for the classes for the Parse Tree nodes and the symbol table.
//

#pragma once
#include "classes.h"

//
// EXPR CLASS
//
Expr::Expr(Token* tok) : op(tok) {}
Expr::~Expr() { delete op; }

//Stringify Node
std::string Expr::toString() {
	if (op == NULL) {
		return "";
	}
	return op->toString();
}

//Return node value
int Expr::eval() { return 0; }


//
// CONSTANT CLASS
//
Constant::Constant(Token* tok) : Expr(tok) {}
Constant::Constant(int i) : Expr(new Num(i)) {}

// return value of constant
int Constant::eval() { return dynamic_cast<Num*>(op)->value; }

//
// ID CLASS
//
Id::Id(Word* id, int b) : Expr(id) {}

// return value of costant
int Id::eval() { return value; }


//
// ARITH CLASS
//
Arith::Arith(Token* tok, Expr* x1, Expr* x2) : Expr(tok), expr1(x1), expr2(x2) {}
Arith::~Arith() { delete expr1; delete expr2; }

// Stringify
std::string Arith::toString() {
	return expr1->toString() + " " + op->toString() + " " + expr2->toString();
}

// Evalue arithmetic expression
int Arith::eval() {
	switch (op->tag) {
	case '+': //is it addition?
		return expr1->eval() + expr2->eval();
	case '-': //or it substraction?
		return expr1->eval() - expr2->eval();
	case '*': //or multiplication
		return expr1->eval() * expr2->eval();
	// no default case as error checking prevents an Arith class from being made if the op Token is incorrect
	}
}


//
//Unary
//
Unary::Unary(Token* tok, Expr* x) : Expr(tok), expr(x) {	}
Unary::~Unary() { delete expr; }

//stringify expression
std::string Unary::toString() {
	return op->toString() + " " + expr->toString();
}

//evaluate unary expression
int Unary::eval() {
	if (op->tag == Tag().MINUS) { // is it a - exression
		return -1 * expr->eval();
	} // or +
	return expr->eval();
}


//
// ASSIGNMENT CLASS
//
Assignment::Assignment() : id(NULL), expr(NULL) {}
Assignment::Assignment(Id* i, Expr* x) : id(i), expr(x) {}
Assignment::~Assignment() { delete id; delete expr; }

void Assignment::eval() {
	if (id == NULL || expr == NULL) return;
	id->value = expr->eval(); //evaluate the expression, assign its value to the Id 
	id->init = true; //label the Id as initiated, else it will be deleted if there are future assignment errors
	std::cout << ">> " + id->toString() << " = " << id->value << std::endl; //print result.
}




//
// SYMBOL TABLE CLASS
//
SymbolTable::SymbolTable() {}

//Add entry in table
void SymbolTable::put(Token* w, Id* i) {
	table[w] = i;
}

//Remove entry in table
void SymbolTable::remove(Token* w) {
	table.erase(w);
}

//Get entry table entry
Id* SymbolTable::get(Token* w) {
	return table[w];
}
