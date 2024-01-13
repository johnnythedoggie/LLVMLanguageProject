//
//  PReturn.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PReturn.hpp"

void PReturn::compile(Compiler* compiler) {
	std::string errorMessage = "Yeah that didn't work.";
	ConstantType* valueType = value->getConstantType(compiler);
	ConstantType* returnType = compiler->scope.returnType;
	if (!returnType) throw errorMessage;
	if (valueType->identifierString() != returnType->identifierString()) throw errorMessage;
	Value* llvmValue = value->getLLVMValue(compiler);
	compiler->llvmBuilder->CreateRet(llvmValue);
}
