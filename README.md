# cisc7120_interpreter
Interpreter for a baby language.

Can be run with a file as and argument and it will interpret that file on the command line.
Or, without a file, and it will run as a command line interpreter.

Files:

interpreter.cpp   Where the main function lives.
tokens.h/.cpp     Declaration and Definitions for tokens.
lexer.h/.cpp      Declaration and Definitions for the Lexer.
classes.h/cpp     Declaration and Definitions for Parse Tree Nodes.
parser.h/.cpp     Declaration and Definitions for the Parser.



The language this interprets is as follows:

Program:
	Assignment*

Assignment:
	Identifier = Exp;

Exp: 
	Exp + Term | Exp - Term | Term

Term:
	Term * Fact  | Fact

Fact:
	( Exp ) | - Fact | + Fact | Literal | Identifier

Identifier:
     	Letter [Letter | Digit]*

Letter:
	a|...|z|A|...|Z|_

Literal:
	0 | NonZeroDigit Digit*
		
NonZeroDigit:
	1|...|9

Digit:
	0|1|...|9
