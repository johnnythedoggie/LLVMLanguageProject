//
//  CIntEqualFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#include "CIntEqualFunction.hpp"

void CIntEqualFunction::makeBody(Compiler* compiler) {
	Value* a = compiler->llvmBuilder->CreateExtractValue(compiler->scope->argument, 0);
	Value* b = compiler->llvmBuilder->CreateExtractValue(compiler->scope->argument, 1);
	Value* result = compiler->llvmBuilder->CreateICmpEQ(a, b);
	compiler->llvmBuilder->CreateRet(result);
}
