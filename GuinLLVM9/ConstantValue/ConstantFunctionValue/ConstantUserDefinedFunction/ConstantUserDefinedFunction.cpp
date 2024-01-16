//
//  ConstantUserDefinedFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "ConstantUserDefinedFunction.hpp"
#include "ConstantVoid.hpp"
#include "PReturn.hpp"

void ConstantUserDefinedFunction::makeBody(Compiler* compiler, Value* argument) {
	
	// Prepare a new scope
	auto savedIdentifiers = compiler->valueForIdentifier;
	compiler->valueForIdentifier = {};
	Scope savedScope = compiler->scope;
	compiler->scope = { inputType, outputType, function->args().begin() };
	
	for (auto x : savedIdentifiers) {
		if (x.second->variance == PVariance::CONST) {
			compiler->valueForIdentifier[x.first] = x.second;
		}
	}
	
	bool foundReturn = false;
	
	while(!statements.empty()) {
		
		PStatement* statement = statements.front();
		statements.pop();
		statement->compile(compiler);
		
		PReturn* value = dynamic_cast<PReturn*>(statement);
		if (value) {
			foundReturn = true;
			break;
		}
		
	}
	
	std::string errorMessage = "Function must end with a return.";
	
	if (!foundReturn) throw errorMessage;
	if (!statements.empty()) throw errorMessage;
	
	// Put back how things were
	compiler->valueForIdentifier = savedIdentifiers;
	compiler->scope = savedScope;
	
}
