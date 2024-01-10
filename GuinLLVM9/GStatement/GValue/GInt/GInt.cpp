//
//  GInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GInt.h"
#include "GBuiltInType.h"
#include "IRGenerator.h"

GInt* GInt::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	if (tokens.empty()) {
		return nullptr;
	}
	
	if (tokens.front().type != Token::TokenType::IntegerLiteral) {
		return nullptr;
	}
	
	int64_t value = 0;
	
	for (char character : tokens.front().value) {
		value *= 10;
		value += character - '0';
	}
	
	tokens.pop();
	
	return new GInt(value, Variance::CONST);
	
}

Value* GInt::generateIR(IRGenerator* generator) const {
	IntegerType* intType = Type::getInt64Ty(*generator->llvmContext);
	Value* irValue = ConstantInt::get(intType, (uint64_t)value, true);
	return irValue;
}

GType* GInt::typeOf() const {
	return new GBuiltInType(GBuiltInType::BuiltIn::Int, Variance::CONST);
}
