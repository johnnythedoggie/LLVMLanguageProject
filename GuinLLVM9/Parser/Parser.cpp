//
//  Parser.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/8/23.
//

#include "Parser.h"

void Parser::formatTokens(std::queue<Token>& tokens) const {
	
	tokens.push({ Token::TokenType::NewLine, "\n" });
	
	std::queue<Token> formattedTokens = {};
	
	bool isInComment = false;
	bool isPrecededByNewLine = true;
	
	while (!tokens.empty()) {
		Token token = tokens.front();
		
		if (token.type == Token::TokenType::CommentStart) {
			isInComment = true;
		} else if (token.value == "\n") {
			isInComment = false;
		}
		
		bool shouldPush = !isInComment && !(isPrecededByNewLine && token.type == Token::TokenType::NewLine);
		
		isPrecededByNewLine = token.type == Token::TokenType::NewLine;
		
		if (shouldPush) {
			formattedTokens.push(token);
		}
		
		tokens.pop();
		
	}
	
	tokens = formattedTokens;
	
}

PStatement* Parser::parseStatement(std::queue<Token>& tokens) {
	PStatement* result;
	result = parseDeclaration(tokens);
	if (!result) result = parseInput(tokens);
	if (!result) result = parseOutput(tokens);
	if (!result) result = parseValue(tokens);
	if (!result) return nullptr;
	std::string errorMessage = "Expected end of statement after statement.";
	if (tokens.front().type != Token::TokenType::NewLine) throw errorMessage;
	tokens.pop();
	return result;
}

PDeclaration* Parser::parseDeclaration(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().type != Token::TokenType::AlphaIdentifier) return nullptr;
	std::string varianceString = tokens.front().value;
	PVariance variance;
	if (varianceString == "const") {
		variance = PVariance::CONST;
	} else if (varianceString == "let") {
		variance = PVariance::LET;
	} else if (varianceString == "var") {
		variance = PVariance::VAR;
	} else {
		return nullptr;
	}
	std::string errorMessage = "Failed to parse declaration.";
	tokens.pop();
	if (tokens.front().type != Token::TokenType::AlphaIdentifier) throw errorMessage;
	std::string identifier = tokens.front().value;
	tokens.pop();
	if (tokens.front().value != "=") throw errorMessage;
	tokens.pop();
	PValue* value = parseValue(tokens);
	if (!value) throw errorMessage;
	return new PDeclaration(variance, identifier, value);
}

PValue* Parser::parseValue(std::queue<Token>& tokens) {
	PValue* result;
	result = parseInt(tokens);
	if (result) return result;
	result = parseIdentifier(tokens);
	if (result) return result;
	result = parseParenedValue(tokens);
	if (result) return result;
	return nullptr;
}

PValue* Parser::parseParenedValue(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "(") return nullptr;
	std::string errorMessage = "Failed to parse parenthesized value.";
	tokens.pop();
	PValue* value = parseValue(tokens);
	if (!value) throw errorMessage;
	if (tokens.front().value != ")") throw errorMessage;
	return nullptr;
}


PInt* Parser::parseInt(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().type != Token::TokenType::IntegerLiteral) return nullptr;
	int value = 0;
	for (const char digit : tokens.front().value) {
		value *= 10;
		value += digit - '0';
	}
	tokens.pop();
	return new PInt(value);
}

PIdentifier* Parser::parseIdentifier(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().type != Token::TokenType::AlphaIdentifier) return nullptr;
	PIdentifier* result = new PIdentifier(tokens.front().value);
	tokens.pop();
	return result;
}

std::queue<PStatement*> Parser::parse(std::queue<Token>& tokens) {
	formatTokens(tokens);
	std::queue<PStatement*> results = {};
	std::string errorMessage = "Failed to parse tokens.";
	while (!tokens.empty()) {
		PStatement* statement = parseStatement(tokens);
		if (!statement) throw errorMessage;
		results.push(statement);
	}
	return results;
}

PInput* Parser::parseInput(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "input") return nullptr;
	std::string errorMessage = "Failed to parse input command.";
	tokens.pop();
	PIdentifier* identifier = parseIdentifier(tokens);
	if (!identifier) throw errorMessage;
	return new PInput(identifier);
}

POutput* Parser::parseOutput(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "output") return nullptr;
	std::string errorMessage = "Failed to parse output command.";
	tokens.pop();
	PValue* value = parseValue(tokens);
	if (!value) throw errorMessage;
	return new POutput(value);
}

