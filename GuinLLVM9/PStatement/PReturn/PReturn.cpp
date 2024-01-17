//
//  PReturn.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PReturn.hpp"

void PReturn::compile(Compiler* compiler) {
	std::string errorMessage = "Yeah that didn't work.";
	CType* valueType = value->getConstantType(compiler);
	CType* returnType = compiler->scope.returnType;
	if (!returnType) throw errorMessage;
	if (valueType->identifierString() != returnType->identifierString()) throw errorMessage;
	Value* llvmValue = value->asLLVMValue(compiler);
	compiler->llvmBuilder->CreateRet(llvmValue);
}
