//
//  GDeclaration.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GDeclaration.h"
#include "GType.h"
#include "IRGenerator.h"


GDeclaration* GDeclaration::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	auto originalTokens = tokens;
	
	if (tokens.front().value != "const") {
		return nullptr;
	}
	
	tokens.pop();
	
	if (tokens.front().type != Token::TokenType::AlphaIdentifier) {
		tokens = originalTokens;
		return nullptr;
	}
	
	std::string identifier = tokens.front().value;
	
	tokens.pop();
	
	if (tokens.front().value != ":") {
		tokens = originalTokens;
		return nullptr;
	}
	
	tokens.pop();
	
	GValue* type = GValue::fromTokens(tokens, identifierToGValueMap);
	
	if (!type) {
		tokens = originalTokens;
		return nullptr;
	}
	
	if (tokens.front().value != "=") {
		tokens = originalTokens;
		return nullptr;
	}
	
	tokens.pop();
	
	GValue* value = GValue::fromTokens(tokens, identifierToGValueMap);
	
	if (!value) {
		tokens = originalTokens;
		return nullptr;
	}
	
	if (value->typeOf()->description() != type->description()) {
		tokens = originalTokens;
		return nullptr;
	}
	
	identifierToGValueMap[identifier] = value;
	
	return new GDeclaration(identifier, type, value);
	
}

std::string GDeclaration::description() const {
	return "const " + identifier + ": " + value->typeOf()->description() + " = " + value->description();
}

Value* GDeclaration::generateIR(IRGenerator* generator) const {
	// do we have to generate ir for the type?
	type->generateIR(generator);
	Value* irValue = value->generateIR(generator);
	generator->identifierToValueMap[identifier] = irValue;
	return irValue;
}
