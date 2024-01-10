//
//  GVoid.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/10/23.
//

#include "GVoid.h"
#include "GBuiltInType.h"

GVoid* GVoid::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	if (tokens.empty()) {
		return nullptr;
	}
	
	if (tokens.front().type != Token::TokenType::OpenParen) {
		return nullptr;
	}
	
	tokens.pop();
	
	if (tokens.front().type != Token::TokenType::CloseParen) {
		return nullptr;
	}
	
	tokens.pop();
	
	return new GVoid(Variance::CONST);
	
}

Value* GVoid::generateIR(IRGenerator* generator) const {
	// TODO: figure out how to represent void in IR
	return nullptr;
}

GType* GVoid::typeOf() const {
	return new GBuiltInType(GBuiltInType::BuiltIn::Void, Variance::CONST);
}
