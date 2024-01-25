//
//  Token.h
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#ifndef Token_h
#define Token_h

#include <string>

/**
 
 A Token is a basic building block of the Guin grammar.
 Tokens are extracted from strings using a Tokenizer.
 Tokens are parsed into PStatements using a Parser.
 
 */
struct Token {
	
	enum class TokenType {
		AlphaIdentifier,
		Symbolidentifier,
		IntegerLiteral,
		OpenParen,
		CloseParen,
		OpenBracket,
		CloseBracket,
		NewLine
	};
	
	TokenType type;
	std::string value;
	
};


#endif /* Token_h */
