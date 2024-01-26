//
//  Parser.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/8/23.
//

#include "Parser.h"
#include <cassert>

void Parser::formatTokens() {
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

PStatement* Parser::parseStatement() {
	PStatement* result;
	result = parseDeclaration();
	if (!result) result = parseReturn();
	if (!result) {
		PValue* left = parseValue();
		result = parseOptionalAssignmentContinuation(left);
	}
	if (!result) return nullptr;
	assert(tokens.front().type == Token::TokenType::NewLine
		   && "Expected new line after statement.");
	tokens.pop();
	return result;
}

PDeclaration* Parser::parseDeclaration() {
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
	tokens.pop();
	assert(tokens.front().type == Token::TokenType::AlphaIdentifier
		   && "Expected identifier after declaration keyword.");
	std::string identifier = tokens.front().value;
	tokens.pop();
	assert(tokens.front().value == "="
		   && "Expected '=' after identifier in declaration.");
	tokens.pop();
	PValue* value = parseValue();
	assert(value && "Expected value after '=' in declaration.");
	return new PDeclaration(variance, identifier, value);
}

PValue* Parser::parseProtectedValue() {
	PValue* result = nullptr;
	if (!result) result = parseSelect();
	if (!result) result = parseFunctionType();
	if (!result) result = parseIdentifier();
	if (!result) result = parseParenedValue();
	if (!result) result = parseInt();
	if (!result) result = parseArgument();
	if (!result) result = parseFunctionLiteral();
	
	if (!result) return nullptr;
	
	while (!tokens.empty() && tokens.front().value == ".") {
		tokens.pop();
		assert(tokens.front().type == Token::TokenType::AlphaIdentifier
			&& "Dot opperator must be followed by an identifier.");
		result = new PTupleElementAccess(result, tokens.front().value);
		tokens.pop();
	}
	
	return result;
}

PValue* Parser::parseValue() {
	PValue* value = parseProtectedValue();
	PFunctionCall* functionCall = parseOptionalFunctionCallContinuation(value);
	while (functionCall) {
		value = functionCall;
		functionCall = parseOptionalFunctionCallContinuation(value);
	}
	return value;
}

PInt* Parser::parseInt() {
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

PIdentifier* Parser::parseIdentifier() {
	if (tokens.empty()) return nullptr;
	if (tokens.front().type != Token::TokenType::AlphaIdentifier) return nullptr;
	PIdentifier* result = new PIdentifier(tokens.front().value);
	tokens.pop();
	return result;
}

std::queue<PStatement*> Parser::parse() {
	formatTokens();
	std::queue<PStatement*> results = {};
	while (!tokens.empty()) {
		PStatement* statement = parseStatement();
		assert(statement && "Expected statement.");
		results.push(statement);
	}
	return results;
}

PFunctionType* Parser::parseFunctionType() {
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
	PValue* inputType = parseProtectedValue();
	assert(inputType && "Expected input type in function type.");
	assert(tokens.front().value == "->" && "Expected symbol '->' in function type.");
	tokens.pop();
	PValue* outputType = parseProtectedValue();
	assert(outputType && "Expected output type in function type.");
	return new PFunctionType(isPure, inputType, outputType);
}

PStatement* Parser::parseOptionalAssignmentContinuation(PValue* value) {
	if (!value) return nullptr;
	if (tokens.empty()) return value;
	if (tokens.front().value != "=") return value;
	tokens.pop();
	PValue* rightValue = parseValue();
	assert(rightValue && "Expected value after '=' in assignment.");
	return new PAssignment(value, rightValue);
}

PFunctionCall* Parser::parseOptionalFunctionCallContinuation(PValue* value) {
	if (!value) return nullptr;
	if (tokens.empty()) return nullptr;
	PValue* argument = parseProtectedValue();
	if (!argument) return nullptr;
	return new PFunctionCall(value, argument);
}

PFunctionDefinition* Parser::parseFunctionLiteral() {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "{") return nullptr;
	tokens.pop();
	if (tokens.front().value == "\n") tokens.pop();
	std::queue<PStatement*> statements = {};
	while (!tokens.empty() && tokens.front().value != "}") {
		PStatement* statement = parseStatement();
		assert(statement && "Expected statement in function body.");
		statements.push(statement);
	}
	assert(tokens.front().value == "}" && "Expected matching close brace.");
	tokens.pop();
	return new PFunctionDefinition(statements);
}

PArgument* Parser::parseArgument() {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "$") return nullptr;
	tokens.pop();
	return new PArgument();
}

PReturn* Parser::parseReturn() {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "return") return nullptr;
	tokens.pop();
	PValue* value = parseValue();
	assert(value && "Expected value after return keyword.");
	return new PReturn(value);
}

PSelect* Parser::parseSelect() {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "#") return nullptr;
	tokens.pop();
	auto message = "Error parsing select command.";
	assert(tokens.front().value == "select" && message);
	tokens.pop();
	assert(tokens.front().value == "(" && message);
	tokens.pop();
	PValue* condition = parseValue();
	assert(condition && message);
	assert(tokens.front().value == "," && message);
	tokens.pop();
	PValue* caseTrue = parseValue();
	assert(caseTrue && message);
	assert(tokens.front().value == "," && message);
	tokens.pop();
	PValue* caseFalse = parseValue();
	assert(caseFalse && message);
	assert(tokens.front().value == ")" && message);
	tokens.pop();
	return new PSelect(condition, caseTrue, caseFalse);
}

// TODO: Needs refactor
// This handles too much in one function - should be broken down into sub-cases
//PValue* Parser::parseParenedValue() {
//	if (tokens.empty()) return nullptr;
//	if (tokens.front().value != "(") return nullptr;
//	tokens.pop();
//	if (tokens.front().value == "\n") tokens.pop();
//	PValue* finalValue = nullptr;
//	if (tokens.front().value == ")") {
//		finalValue = new PTuple({});
//	} else if (tokens.front().type == Token::TokenType::AlphaIdentifier) {
//		// maybe a tuple
//		std::string label = tokens.front().value;
//		tokens.pop();
//		if (tokens.front().value == "=") {
//			tokens.pop();
//			PValue* value = parseValue();
//			assert(value && "Expected value after '=' in tuple value.");
//			std::vector<PTupleElement> elements = {};
//			elements.push_back(PTupleElement(label, value));
//			while (tokens.front().value == ",") {
//				tokens.pop();
//				if (tokens.front().value == "\n") tokens.pop();
//				assert(tokens.front().type == Token::TokenType::AlphaIdentifier
//					&& "Expected identifier in tuple value.");
//				std::string label = tokens.front().value;
//				tokens.pop();
//				assert(tokens.front().value == "="
//					&& "Expected symbol '=' in tuple value.");
//				tokens.pop();
//				PValue* value = parseValue();
//				assert(value && "Expected value after '=' in tuple value.");
//				elements.push_back(PTupleElement(label, value));
//			}
//			finalValue = new PTuple(elements);
//		} else if (tokens.front().value == ":") {
//			tokens.pop();
//			PValue* value = parseValue();
//			assert(value && "Expected type after ':' in tuple type.");
//			std::vector<PTupleTypeElement> elements = {};
//			elements.push_back(PTupleTypeElement(label, value));
//			while (tokens.front().value == ",") {
//				tokens.pop();
//				if (tokens.front().value == "\n") tokens.pop();
//				assert(tokens.front().type == Token::TokenType::AlphaIdentifier
//					&& "Expected identifier in tuple type.");
//				std::string label = tokens.front().value;
//				tokens.pop();
//				assert(tokens.front().value == ":"
//					&& "Expected ':' after identifier in tuple type.");
//				tokens.pop();
//				PValue* value = parseValue();
//				assert(value && "Expected type after ':' in tuple type.");
//				elements.push_back(PTupleTypeElement(label, value));
//			}
//			finalValue = new PTupleType(elements);
//		} else {
//			// not a tuple
//			// this is embarrasing, I took too much from the queue
//			// its hard to put it all back, but I'll do it
//			std::queue<Token> copy = tokens;
//			tokens = {};
//			tokens.push({ Token::TokenType::AlphaIdentifier, label });
//			while (!copy.empty()) {
//				tokens.push(copy.front());
//				copy.pop();
//			}
//			finalValue = parseValue();
//		}
//	} else {
//		finalValue = parseValue();
//	}
//	assert(finalValue && "Invalid parenthesized value.");
//	if (tokens.front().value == "\n") tokens.pop();
//	assert(tokens.front().value == ")" && "Expected matching close parenthese.");
//	tokens.pop();
//	return finalValue;
//}

Parser::TElement* Parser::parseTElement() {
	if (tokens.empty()) return nullptr;
	Parser::TElement* result = new TElement();
	if (tokens.front().type == Token::TokenType::AlphaIdentifier) {
		std::string identifier = tokens.front().value;
		tokens.pop();
		if (tokens.front().value == "=" || tokens.front().value == ":") {
			// it has an identifier!
			result->hasIdentifier = true;
			result->identifier = identifier;
			result->isType = (tokens.front().value == ":");
			tokens.pop();
		} else {
			// it doesn't have an identifier
			// result tokens to how it was before
			result->hasIdentifier = false;
			auto copy = tokens;
			tokens = {};
			tokens.push({ Token::TokenType::AlphaIdentifier, identifier });
			while (!copy.empty()) {
				tokens.push(copy.front());
				copy.pop();
			}
		}
	} else {
		// it doesnt have an identifier
		result->hasIdentifier = false;
	}
	// All cases arrive here
	result->value = parseValue();
	assert(result->value && "Expected value in tuple element.");
	return result;
}

PValue* Parser::parseParenedValue() {
	if (tokens.empty()) return nullptr;
	if (tokens.front().value != "(") return nullptr;
	tokens.pop();
	if (tokens.front().value == "\n") tokens.pop();
	
	if (tokens.front().value == ")") {
		tokens.pop();
		return new PTuple({});
	}
	
	bool isTupleType;
	std::vector<PTupleTypeElement> tupleTypeElements = {};
	std::vector<PTupleElement> tupleElements = {};
	
	TElement* element = parseTElement();
	isTupleType = (element->hasIdentifier && element->isType);
	
	if (isTupleType) {
		tupleTypeElements.emplace_back(element->identifier, element->value);
	} else {
		tupleElements.emplace_back(element->hasIdentifier, element->identifier, element->value);
	}
	
	while (tokens.front().value == ",") {
		tokens.pop();
		if (tokens.front().value == "\n") tokens.pop();
		TElement* element = parseTElement();
		if (isTupleType) {
			assert(element->hasIdentifier && element->isType);
			tupleTypeElements.emplace_back(element->identifier, element->value);
		} else {
			assert(!element->hasIdentifier || !element->isType);
			tupleElements.emplace_back(element->hasIdentifier, element->identifier, element->value);
		}
	}
	
	
	assert(tokens.front().value == ")" && "Expected matching close parenthese.");
	tokens.pop();
	
	if (tupleElements.size() == 1 && !tupleElements[0].hasLabel) {
		return tupleElements[0].value;
	}
	
	if (isTupleType) {
		return new PTupleType(tupleTypeElements);
	} else {
		return new PTuple(tupleElements);
	}
	
}
