//
//  GType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GType.h"
#include "GBuiltInType.h"

GType* GType::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	// Here for tuple types and function types and stuff...
	
	return nullptr;
	
}

GType* GType::typeOf() const {
	return new GBuiltInType(GBuiltInType::BuiltIn::Type, Variance::Const);
}
