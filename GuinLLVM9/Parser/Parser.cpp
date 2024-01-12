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
	if (!result) {
		PValue* left = parseValue(tokens);
		result = parseOptionalAssignmentContinuation(left, tokens);
	}
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

PValue* Parser::parseProtectedValue(std::queue<Token>& tokens) {
	PValue* result;
	result = parseIdentifier(tokens);
	if (result) return result;
	result = parseParenedValue(tokens);
	if (result) return result;
	result = parseInt(tokens);
	if (result) return result;
	return nullptr;
}

PValue* Parser::parseValue(std::queue<Token>& tokens) {
	PValue* value = parseProtectedValue(tokens);
	PFunctionType* functionType = parseOptionalFunctionTypeContinuation(value, tokens);
	if (functionType) return functionType;
	PFunctionCall* functionCall = parseOptionalFunctionCallContinuation(value, tokens);
	if (functionCall) return functionCall;
	PFunctionDefinition* functionDefinition = parseOptionalFunctionDefinitionContinuation(value, tokens);
	if (functionDefinition) return functionDefinition;
	return value;
}

PValue* Parser::parseParenedValue(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "(") return nullptr;
	std::string errorMessage = "Failed to parse parenthesized value.";
	tokens.pop();
	if (tokens.front().value == "\n") tokens.pop();
	PValue* value = parseValue(tokens);
	if (!value) throw errorMessage;
	if (tokens.front().value == "\n") tokens.pop();
	if (tokens.front().value != ")") throw errorMessage;
	tokens.pop();
	return value;
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

PFunctionType* Parser::parseOptionalFunctionTypeContinuation(PValue* value, std::queue<Token>& tokens) {
	if (!value) return nullptr;
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "->") return nullptr;
	tokens.pop();
	PValue* rightValue = parseProtectedValue(tokens);
	std::string errorMessage = "Function type requires a right hand side.";
	if (!rightValue) throw errorMessage;
	return new PFunctionType(value, rightValue);
}

PStatement* Parser::parseOptionalAssignmentContinuation(PValue* value, std::queue<Token>& tokens) {
	if (!value) return nullptr;
	if (tokens.empty()) return value;
	if (tokens.front().value != "=") return value;
	tokens.pop();
	PValue* rightValue = parseValue(tokens);
	std::string errorMessage = "Assignment requires a right hand side.";
	if (!rightValue) throw errorMessage;
	return new PAssignment(value, rightValue);
}

PFunctionCall* Parser::parseOptionalFunctionCallContinuation(PValue* value, std::queue<Token>& tokens) {
	if (!value) return nullptr;
	if (tokens.empty()) return nullptr;
	PValue* argument = parseProtectedValue(tokens);
	if (!argument) return nullptr;
	return new PFunctionCall(value, argument);
}

PFunctionDefinition* Parser::parseOptionalFunctionDefinitionContinuation(PValue* value, std::queue<Token>& tokens) {
	if (!value) return nullptr;
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "{") return nullptr;
	std::string errorMessage = "Error parsing function body.";
	tokens.pop();
	if (tokens.front().value == "\n") tokens.pop();
	std::queue<PStatement*> statements = {};
	while (!tokens.empty() && tokens.front().value != "}") {
		PStatement* statement = parseStatement(tokens);
		if (!statement) throw errorMessage;
		statements.push(statement);
	}
	if (tokens.front().value != "}") throw errorMessage;
	tokens.pop();
	return new PFunctionDefinition(value, statements);
}
