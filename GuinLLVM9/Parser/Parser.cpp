//
//  Parser.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/8/23.
//

#include "Parser.h"

std::queue<GStatement*> Parser::getStatementsFrom(std::queue<Token> tokens) {
	
	std::queue<GStatement*> statements = {};
	
	auto tokenCount = tokens.size();
	GStatement* statement = GStatement::fromTokens(tokens, identifierToGValueMap);
	
	while (statement && tokens.size() < tokenCount) {
		statements.push(statement);
		tokenCount = tokens.size();
		statement = GStatement::fromTokens(tokens, identifierToGValueMap);
	}
	
	assert(tokens.empty() && "Could not parse all tokens.");
	
	return statements;
	
}
