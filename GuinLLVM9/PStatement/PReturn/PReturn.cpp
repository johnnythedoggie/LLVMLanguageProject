//
//  PReturn.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PReturn.hpp"

void PReturn::compile(Compiler* compiler) {
	CType* returnType = compiler->scope->returnType;
	value->expectedType(returnType);
	CType* valueType = value->getConstantType(compiler);
	assert(returnType && "Cannot return from outer scope.");
	assert(valueType->id() == returnType->id()
		   && "The value returned must match the return type of the scope.");
	Value* llvmValue = value->asLLVMValue(compiler);
	compiler->llvmBuilder->CreateRet(llvmValue);
}
