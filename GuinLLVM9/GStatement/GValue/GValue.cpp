//
//  GValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GValue.h"
#include "GBool.h"
#include "GInt.h"
#include "GType.h"
#include "GIdentifier.h"
#include "GVoid.h"

GValue* GValue::fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap) {
	
	GInt* intValue = GInt::fromTokens(tokens, identifierToGValueMap);
	
	if (intValue) {
		return intValue;
	}
	
	GType* typeValue = GType::fromTokens(tokens, identifierToGValueMap);
	
	if (typeValue) {
		return typeValue;
	}
	
	GVoid* voidValue = GVoid::fromTokens(tokens, identifierToGValueMap);
	
	if (voidValue) {
		return voidValue;
	}
	
	GValue* identifierValue = GIdentifier::fromTokens(tokens, identifierToGValueMap);
	
	if (identifierValue) {
		return identifierValue;
	}
	
	return nullptr;
	
}
