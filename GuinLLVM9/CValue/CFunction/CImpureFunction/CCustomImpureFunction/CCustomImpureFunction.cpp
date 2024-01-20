//
//  CCustomImpureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#include "CCustomImpureFunction.hpp"
#include "PReturn.hpp"

void CCustomImpureFunction::makeBody(Compiler* compiler) {
	
	
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
	
	captureList = compiler->scope->capturedValues;
	
}
