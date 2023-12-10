//
//  Parser.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/8/23.
//

#include "Parser.h"

void Parser::removeComments(std::queue<Token>& tokens) const {
	
	std::queue<Token> filteredTokens = {};
	
	bool isInComment = false;
	
	while (!tokens.empty()) {
		Token token = tokens.front();
		
		if (token.type == Token::TokenType::CommentStart) {
			isInComment = true;
		} else if (token.value == "\n") {
			isInComment = false;
		}
		
		tokens.pop();
		if (!isInComment) {
			filteredTokens.push(token);
		}
	}
	
	tokens = filteredTokens;
	
}

std::queue<GStatement*> Parser::getStatementsFrom(std::queue<Token> tokens) {
	
	removeComments(tokens);
	
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
