//
//  CDifferenceFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#include "CDifferenceFunction.hpp"

void CDifferenceFunction::makeBody(Compiler* compiler) {
	Value* a = compiler->llvmBuilder->CreateExtractValue(compiler->scope->argument, 0);
	Value* b = compiler->llvmBuilder->CreateExtractValue(compiler->scope->argument, 1);
	Value* result = compiler->llvmBuilder->CreateSub(a, b);
	compiler->llvmBuilder->CreateRet(result);
}
