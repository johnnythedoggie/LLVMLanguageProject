//
//  GType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GType.h"
#include "GBuiltInType.h"
#include "GPureFunctionType.h"

GType* GType::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	GPureFunctionType* funcType = GPureFunctionType::fromTokens(tokens, identifierToGValueMap);
	
	if (funcType) {
		return funcType;
	}
	
	return nullptr;
	
}

GType* GType::typeOf() const {
	return new GBuiltInType(GBuiltInType::BuiltIn::Type, Variance::CONST);
}
