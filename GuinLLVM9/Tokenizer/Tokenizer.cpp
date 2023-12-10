//
//  Tokenizer.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/8/23.
//

#include "Tokenizer.h"

Tokenizer::CharacterType Tokenizer::characterTypeOf(char character) {
	
	switch (character) {
		case '(':
			return CharacterType::OpenParen;
		case ')':
			return CharacterType::CloseParen;
		case ' ':
		case '\t':
			return CharacterType::WhiteSpace;
		case '\n':
		case ';':
			return CharacterType::NewLine;
		case '~':
		case '`':
		case '!':
		case '@':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '-':
		case '+':
		case ':':
		case '=':
		case '|':
		case '\\':
		case '/':
		case '<':
		case '>':
		case '?':
			return CharacterType::Symbol;
		case '#':
			return CharacterType::CommentSymbol;
	}
	
	if (isalpha(character) || character == '_') {
		return CharacterType::IdentifierCharacter;
	}
	
	if (isdigit(character)) {
		return CharacterType::Digit;
	}
	
	return CharacterType::Unkown;
	
}

bool Tokenizer::shouldPush(CharacterType characterType) {
	
	switch (characterType) {
		case CharacterType::WhiteSpace:
		case CharacterType::Unkown:
			return false;
		default:
			return true;
	}
	
}

bool Tokenizer::shouldPushIndependently(CharacterType characterType) {
	
	switch (characterType) {
		case CharacterType::NewLine:
		case CharacterType::OpenParen:
		case CharacterType::CloseParen:
		case CharacterType::CommentSymbol:
			return true;
		default:
			return false;
	}
	
}

Token::TokenType Tokenizer::getTokenTypeForCharacterType(CharacterType characterType) {
	
	switch (characterType) {
		case CharacterType::IdentifierCharacter:
			return Token::TokenType::AlphaIdentifier;
		case CharacterType::Digit:
			return Token::TokenType::IntegerLiteral;
		case CharacterType::Symbol:
			return Token::TokenType::Symbolidentifier;
		case CharacterType::NewLine:
			return Token::TokenType::NewLine;
		case CharacterType::OpenParen:
			return Token::TokenType::OpenParen;
		case CharacterType::CloseParen:
			return Token::TokenType::CloseParen;
		case CharacterType::CommentSymbol:
			return Token::TokenType::CommentStart;
			
		default:
			assert(false && "Cannot get token tyoe for this character type.");
	}
	
}

std::queue<Token> Tokenizer::getTokensFrom(const std::string& input) {
	
	std::queue<Token> tokens = {};
	
	std::string currentString = "";
	CharacterType currentStringCharacterType = CharacterType::WhiteSpace;
	
	// the extra space will make sure we handle all the important tokens
	auto loopReadyInput = input + std::string(" ");
	
	for (char character : loopReadyInput) {
		
		auto characterType = characterTypeOf(character);
		
		assert(characterType != CharacterType::Unkown && "Unkown character type.");
		
		if (characterType == currentStringCharacterType) {
			
			currentString.push_back(character);
			
		} else {
			
			if (shouldPushIndependently(currentStringCharacterType)) {
				for (char c : currentString) {
					Token token = {
						getTokenTypeForCharacterType(currentStringCharacterType),
						std::string(1, c)
					};
					tokens.push(token);
				}
			} else if (shouldPush(currentStringCharacterType)) {
				Token token = {
					getTokenTypeForCharacterType(currentStringCharacterType),
					currentString
				};
				tokens.push(token);
			}
			
			currentString = std::string(1, character);
			currentStringCharacterType = characterType;
			
		}
		
	}
	
	return tokens;
	
}

bool Tokenizer::test() {
	
	std::string input = "let x += 5 + (3 *   (345-3))";
	std::vector<std::string> expectedOutput = {
		"let", "x", "+=", "5", "+", "(", "3", "*", "(", "345", "-", "3", ")", ")"
	};
	auto actualOutput = getTokensFrom(input);
	
	if (actualOutput.size() != expectedOutput.size()) {
		return false;
	}
	
	for (int i = 0; i < expectedOutput.size(); i += 1, actualOutput.pop()) {
		if (actualOutput.front().value != expectedOutput[i]) {
			return false;
		}
	}
	
	return true;
	
}
