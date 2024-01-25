//
//  CCustomPureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "CCustomPureFunction.hpp"
#include "PReturn.hpp"
#include <cassert>

void CCustomPureFunction::makeBody(Compiler* compiler) {
	
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
	
	assert(foundReturn && statements.empty() && "Function must end with a return");
	
}
