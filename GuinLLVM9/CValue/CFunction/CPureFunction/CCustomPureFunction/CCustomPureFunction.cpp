//
//  CCustomPureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "CCustomPureFunction.hpp"
#include "PReturn.hpp"
#include "CTuple.hpp"
#include "CTupleType.hpp"
#include <cassert>

void CCustomPureFunction::makeBody(Compiler* compiler) {
	
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
	
}
