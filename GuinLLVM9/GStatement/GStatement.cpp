//
//  GStatement.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GStatement.h"
#include "GValue.h"
#include "GDeclaration.h"

bool GStatement::hasNewLineNext(const std::queue<Token>& tokens) {
	return !tokens.empty() && tokens.front().type == Token::TokenType::NewLine;
}

GStatement* GStatement::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	auto storedTokens = tokens;
	
	GStatement* result = nullptr;
	
	while (hasNewLineNext(tokens)) {
		tokens.pop();
	}
	
	if (!result) {
		result = GDeclaration::fromTokens(tokens, identifierToGValueMap);
	}
	
	if (!result) {
		result = GValue::fromTokens(tokens, identifierToGValueMap);
	}
	
	if (!result) {
		return nullptr;
	}
	
	if (!tokens.empty() && !hasNewLineNext(tokens)) {
		tokens = storedTokens;
		return nullptr;
	}
	
	while (hasNewLineNext(tokens)) {
		tokens.pop();
	}
	
	return result;
	
}
