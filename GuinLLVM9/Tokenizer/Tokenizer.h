//
//  Tokenizer.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef Tokenizer_h
#define Tokenizer_h

#include "Token.h"
#include <queue>
#include <iostream>

class Tokenizer {
	
	enum class CharacterType {
		IdentifierCharacter, // characters that can appear in an identifier
		Digit, // characters that can appeat in a number literal
		Symbol, // characters like '*', '^', and '='
		LoneSymbol, // characters like '.' and '$' that must always be treated seperately
		NewLine, // the newline character
		OpenParen, // '('
		CloseParen, // ')'
		OpenBracket, // '{'
		CloseBracket, // '}'
		WhiteSpace, // spaces and tabs
		Unkown // all other characters
	};
	
	static CharacterType characterTypeOf(char character);
	
	static bool shouldPush(CharacterType characterType);
	
	static bool shouldPushIndependently(CharacterType characterType);
	
	static Token::TokenType getTokenTypeForCharacterType(CharacterType characterType);
	
public:
	
	/*
	 Turns "let x= 5 + (3 *   (345-3))"
	 Into ["let", "x", "=", "5", "+", "(", "3", "*", "(", "345", "-", "3", ")", ")"]
	 */
	static std::queue<Token> getTokensFrom(const std::string& input);
	
	static bool test();
	
};


#endif /* Tokenizer_h */
