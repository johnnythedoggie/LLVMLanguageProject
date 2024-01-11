//
//  POutput.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "POutput.hpp"
#include "ConstantIntType.hpp"

Value* POutput::format = nullptr;
Function* POutput::printf = nullptr;

void POutput::setup(Compiler* compiler) {
	
	std::vector<Type*> printfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* printfType = FunctionType::get(compiler->llvmBuilder->getInt32Ty(), printfArgTypes, true);
	
	Function::Create(printfType, Function::ExternalLinkage, "printf", *compiler->llvmModule);
	
	format = compiler->llvmBuilder->CreateGlobalStringPtr("%u\n", "printf_format");
	
	printf = compiler->llvmModule->getFunction("printf");
	
}

void POutput::compile(Compiler* compiler) {
	
	if (!printf) setup(compiler);
	
	std::string inputType = ConstantIntType().identifierString();
	std::string argumentType = argument->getConstantType(compiler)->identifierString();
	
	std::string errorMessage = "Cannot output non-integer input.";
	if (argumentType != inputType) throw errorMessage;
	
	Value* llvmArgument = argument->getLLVMValue(compiler);
	
	std::vector<Value*> printfArgs = { format, llvmArgument };
	
	compiler->llvmBuilder->CreateCall(printf, printfArgs);
	
}
