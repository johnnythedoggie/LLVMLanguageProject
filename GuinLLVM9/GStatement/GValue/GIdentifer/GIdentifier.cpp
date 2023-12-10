//
//  GIdentifier.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GIdentifier.h"

GValue* GIdentifier::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	if (tokens.empty()) {
		return nullptr;
	}
	
	if (tokens.front().type != Token::TokenType::AlphaIdentifier) {
		return nullptr;
	}
	
	std::string id = tokens.front().value;
	
	if (!identifierToGValueMap.contains(id)) {
		return nullptr;
	}
	
	tokens.pop();
	
	return identifierToGValueMap[id];
	
}
