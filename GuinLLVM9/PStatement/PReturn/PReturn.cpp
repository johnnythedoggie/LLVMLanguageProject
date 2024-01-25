//
//  PReturn.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PReturn.hpp"

void PReturn::compile(Compiler* compiler) {
	CType* valueType = value->getConstantType(compiler);
	CType* returnType = compiler->scope->returnType;
	assert(returnType && "Cannot return from outer scope.");
	assert(valueType->identifierString() == returnType->identifierString()
		   && "The value returned must match the return type of the scope.");
	Value* llvmValue = value->asLLVMValue(compiler);
	compiler->llvmBuilder->CreateRet(llvmValue);
}
