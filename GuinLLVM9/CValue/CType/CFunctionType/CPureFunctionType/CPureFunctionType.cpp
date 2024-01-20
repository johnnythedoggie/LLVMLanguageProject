//
//  CPureFunctionType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CPureFunctionType.hpp"

std::string CPureFunctionType::identifierString() {
	return "pure (" + inputType->identifierString() + ") -> " + outputType->identifierString();
}

Type* CPureFunctionType::asLLVMType(Compiler* compiler) {
	return getLLVMFunctionType(compiler)->getPointerTo();
}

FunctionType* CPureFunctionType::getLLVMFunctionType(Compiler* compiler) {
	return FunctionType::get(
		outputType->asLLVMType(compiler),
		{ inputType->asLLVMType(compiler) },
		false
	);
}
