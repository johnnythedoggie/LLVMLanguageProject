//
//  CImpureFunctionType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#include "CImpureFunctionType.hpp"

std::string CImpureFunctionType::identifierString() {
	return "impure (" + inputType->identifierString() + ") -> " + outputType->identifierString();
}

StructType* CImpureFunctionType::asLLVMType(Compiler* compiler) {
	return StructType::get(*compiler->llvmContext, {
		getLLVMFunctionType(compiler)->getPointerTo(),
		opaqueContextLLVMType(compiler)->getPointerTo()
	});
}

Type* CImpureFunctionType::opaqueContextLLVMType(Compiler* compiler) {
	StructType* structType = StructType::get(*compiler->llvmContext, { });
	return structType->getPointerTo();
}

FunctionType* CImpureFunctionType::getLLVMFunctionType(Compiler* compiler) {
	return FunctionType::get(
		 outputType->asLLVMType(compiler),
		 { inputType->asLLVMType(compiler), opaqueContextLLVMType(compiler)->getPointerTo() },
		 false
	);
}
