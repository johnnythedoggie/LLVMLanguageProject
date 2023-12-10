//
//  GPureFunctionType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/10/23.
//

#include "GPureFunctionType.h"

GPureFunctionType* GPureFunctionType::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	auto originalTokens = tokens;
	
	if (tokens.front().value != "pure") {
		return nullptr;
	}
	
	tokens.pop();
	
	auto inputType = GValue::fromTokens(tokens, identifierToGValueMap);
	
	if (!inputType) {
		tokens = originalTokens;
		return nullptr;
	}
	
	if (inputType->typeOf()->description() != "Type") {
		tokens = originalTokens;
		return nullptr;
	}
	
	if (tokens.front().value != "->") {
		tokens = originalTokens;
		return nullptr;
	}
	
	tokens.pop();
	
	auto outputType = GValue::fromTokens(tokens, identifierToGValueMap);
	
	if (!outputType) {
		tokens = originalTokens;
		return nullptr;
	}
	
	if (outputType->typeOf()->description() != "Type") {
		tokens = originalTokens;
		return nullptr;
	}
	
	// a pure function type is const iff the inputType and outputType are const, otherwise let.
	
	Variance variance;
	
	if (inputType->variance == Variance::Const && outputType->variance == Variance::Const) {
		variance = Variance::Const;
	} else {
		variance = Variance::Let;
	}
	
	return new GPureFunctionType(inputType, outputType, variance);
	
}
