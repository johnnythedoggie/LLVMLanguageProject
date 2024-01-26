//
//  CCustomImpureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#include "CCustomImpureFunction.hpp"
#include "PReturn.hpp"
#include "CTupleType.hpp"
#include "CTuple.hpp"
#include <cassert>

void CCustomImpureFunction::makeBody(Compiler* compiler) {
	
	
	bool needsReturn = true;
	
	while(!statements.empty()) {
		
		PStatement* statement = statements.front();
		statements.pop();
		statement->compile(compiler);
		
		if (dynamic_cast<PReturn*>(statement)) {
			needsReturn = false;
			break;
		}
		
	}
	
	if (needsReturn && outputType->id() == CTupleType({}).id()) {
		compiler->llvmBuilder->CreateRet(CTuple({}).getLLVMValue(compiler));
		needsReturn = false;
	}
	
	assert(!needsReturn && statements.empty() && "Non-Void function must end with a return.");
	
	captureList = compiler->scope->capturedValues;
	
}
