//
//  PInput.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PInput.hpp"

Value* PInput::format = nullptr;
Function* PInput::scanf = nullptr;

void PInput::setup(Compiler* compiler) {
	
	std::vector<Type*> scanfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* scanfType = FunctionType::get(compiler->llvmBuilder->getInt32Ty(), scanfArgTypes, true);
	
	Function::Create(scanfType, Function::ExternalLinkage, "scanf", *compiler->llvmModule);
	
	format = compiler->llvmBuilder->CreateGlobalStringPtr("%u", "scanf_format");
	
	scanf = compiler->llvmModule->getFunction("scanf");
	
}

void PInput::compile(Compiler* compiler) {
	
	if (!scanf) setup(compiler);
	
	Value* llvmArgument = argument->getMemoryLocation(compiler);
	
	std::vector<Value*> scanfArgs = { format, llvmArgument };
	
	compiler->llvmBuilder->CreateCall(scanf, scanfArgs);
	
}
