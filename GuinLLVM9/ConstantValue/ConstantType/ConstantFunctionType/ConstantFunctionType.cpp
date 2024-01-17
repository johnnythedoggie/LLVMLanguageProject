//
//  ConstantFunctionType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantFunctionType.hpp"

std::string ConstantFunctionType::identifierString() {
	return "(" + inputType->identifierString() + ") -> " + outputType->identifierString();
}

Type* ConstantFunctionType::asLLVMType(Compiler* compiler) {
	return getLLVMFunctionType(compiler)->getPointerTo();
}

FunctionType* ConstantFunctionType::getLLVMFunctionType(Compiler* compiler) {
	return FunctionType::get(
		outputType->asLLVMType(compiler),
		{ inputType->asLLVMType(compiler) },
		false
	);
}
