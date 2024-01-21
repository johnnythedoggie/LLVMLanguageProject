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
	
	bool isPrecededByNewLine = true;
	
	while (!tokens.empty()) {
		Token token = tokens.front();
		
		bool shouldPush = !isPrecededByNewLine || token.type != Token::TokenType::NewLine;
		
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
	if (!result) result = parseReturn(tokens);
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
	PValue* result = nullptr;
	if (!result) result = parseSelect(tokens);
	if (!result) result = parseFunctionType(tokens);
	if (!result) result = parseIdentifier(tokens);
	if (!result) result = parseParenedValue(tokens);
	if (!result) result = parseInt(tokens);
	if (!result) result = parseArgument(tokens);
	
	if (!result) return nullptr;
	
	std::string errorMessage = "Could not parse dot usage.";
	while (!tokens.empty() && tokens.front().value == ".") {
		tokens.pop();
		if (tokens.front().type != Token::TokenType::AlphaIdentifier) throw errorMessage;
		result = new PTupleElementAccess(result, tokens.front().value);
		tokens.pop();
	}
	
	return result;
}

PValue* Parser::parseValue(std::queue<Token>& tokens) {
	PValue* value = parseProtectedValue(tokens);
	return addValueContinuations(value, tokens);
}

PValue* Parser::addValueContinuations(PValue* value, std::queue<Token>& tokens) {
	PFunctionDefinition* functionDefinition = parseOptionalFunctionDefinitionContinuation(value, tokens);
	if (functionDefinition) value = functionDefinition;
	PFunctionCall* functionCall = parseOptionalFunctionCallContinuation(value, tokens);
	if (functionCall) value = functionCall;
	return value;
}

PValue* Parser::parseParenedValue(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "(") return nullptr;
	std::string errorMessage = "Failed to parse parenthesized value.";
	tokens.pop();
	if (tokens.front().value == "\n") tokens.pop();
	PValue* finalValue = nullptr;
	if (tokens.front().value == ")") {
		finalValue = new PTuple({});
	} else if (tokens.front().type == Token::TokenType::AlphaIdentifier) {
		// maybe a tuple
		std::string label = tokens.front().value;
		tokens.pop();
		if (tokens.front().value == "=") {
			tokens.pop();
			PValue* value = parseValue(tokens);
			if (!value) throw errorMessage;
			std::vector<PTupleElement> elements = {};
			elements.push_back(PTupleElement(label, value));
			while (tokens.front().value == ",") {
				tokens.pop();
				if (tokens.front().value == "\n") tokens.pop();
				if (tokens.front().type != Token::TokenType::AlphaIdentifier) throw errorMessage;
				std::string label = tokens.front().value;
				tokens.pop();
				if (tokens.front().value != "=") throw errorMessage;
				tokens.pop();
				PValue* value = parseValue(tokens);
				if (!value) throw errorMessage;
				elements.push_back(PTupleElement(label, value));
			}
			finalValue = new PTuple(elements);
		} else if (tokens.front().value == ":") {
			tokens.pop();
			PValue* value = parseValue(tokens);
			if (!value) throw errorMessage;
			std::vector<PTupleTypeElement> elements = {};
			elements.push_back(PTupleTypeElement(label, value));
			while (tokens.front().value == ",") {
				tokens.pop();
				if (tokens.front().value == "\n") tokens.pop();
				if (tokens.front().type != Token::TokenType::AlphaIdentifier) throw errorMessage;
				std::string label = tokens.front().value;
				tokens.pop();
				if (tokens.front().value != ":") throw errorMessage;
				tokens.pop();
				PValue* value = parseValue(tokens);
				if (!value) throw errorMessage;
				elements.push_back(PTupleTypeElement(label, value));
			}
			finalValue = new PTupleType(elements);
		} else {
			// not a tuple
			// this is embarrasing, I took too much from the queue
			// its hard to put it all back, but I'll do it
			std::queue<Token> copy = tokens;
			tokens = {};
			tokens.push({ Token::TokenType::AlphaIdentifier, label });
			while (!copy.empty()) {
				tokens.push(copy.front());
				copy.pop();
			}
			finalValue = parseValue(tokens);
		}
	} else {
		finalValue = parseValue(tokens);
	}
	if (!finalValue) throw errorMessage;
	if (tokens.front().value == "\n") tokens.pop();
	if (tokens.front().value != ")") throw errorMessage;
	tokens.pop();
	return finalValue;
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

PFunctionType* Parser::parseFunctionType(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	bool isPure;
	if (tokens.front().value == "pure") {
		isPure = true;
	} else if (tokens.front().value == "impure") {
		isPure = false;
	} else {
		return nullptr;
	}
	tokens.pop();
	std::string errorMessage = "Erorr parsing function type.";
	PValue* inputType = parseProtectedValue(tokens);
	if (!inputType) throw errorMessage;
	if (tokens.front().value != "->") throw errorMessage;
	tokens.pop();
	PValue* outputType = parseProtectedValue(tokens);
	if (!outputType) throw errorMessage;
	return new PFunctionType(isPure, inputType, outputType);
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

PArgument* Parser::parseArgument(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "$") return nullptr;
	tokens.pop();
	return new PArgument();
}

PReturn* Parser::parseReturn(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "return") return nullptr;
	tokens.pop();
	std::string errorMessage = "Error parsing return.";
	PValue* value = parseValue(tokens);
	if (!value) throw errorMessage;
	return new PReturn(value);
}

PSelect* Parser::parseSelect(std::queue<Token>& tokens) {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "#") return nullptr;
	tokens.pop();
	std::string errorMessage = "Error parsing select.";
	if (tokens.front().value != "select") throw errorMessage;
	tokens.pop();
	if (tokens.front().value != "(") throw errorMessage;
	tokens.pop();
	PValue* condition = parseValue(tokens);
	if (!condition) throw errorMessage;
	if (tokens.front().value != ",") throw errorMessage;
	tokens.pop();
	PValue* caseTrue = parseValue(tokens);
	if (!caseTrue) throw errorMessage;
	if (tokens.front().value != ",") throw errorMessage;
	tokens.pop();
	PValue* caseFalse = parseValue(tokens);
	if (!caseFalse) throw errorMessage;
	if (tokens.front().value != ")") throw errorMessage;
	tokens.pop();
	return new PSelect(condition, caseTrue, caseFalse);
}
