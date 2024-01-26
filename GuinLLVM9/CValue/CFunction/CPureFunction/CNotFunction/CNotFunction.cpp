//
//  CNotFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#include "CNotFunction.hpp"

void CNotFunction::makeBody(Compiler* compiler) {
	Value* input = compiler->scope->argument;
	Value* result = compiler->llvmBuilder->CreateNot(input);
	compiler->llvmBuilder->CreateRet(result);
}
