//
//  PInput.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PInput.hpp"
#include "ConstantIntType.hpp"

Value* PInput::format = nullptr;
Function* PInput::scanf = nullptr;

void PInput::setup(Compiler* compiler) {
	
	std::vector<Type*> scanfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* scanfType = FunctionType::get(compiler->llvmBuilder->getInt32Ty(), scanfArgTypes, true);
	
	Function::Create(scanfType, Function::ExternalLinkage, "scanf", *compiler->llvmModule);
	
	format = compiler->llvmBuilder->CreateGlobalStringPtr("%u", "scanf_format");
	
	scanf = compiler->llvmModule->getFunction("scanf");
	
}

ConstantValue* PInput::getConstantValue(Compiler* compiler) {
	return nullptr;
}

ConstantType* PInput::getConstantType(Compiler* compiler) {
	return new ConstantIntType();
}

Value* PInput::getLLVMValue(Compiler* compiler) {
	
	if (!scanf) setup(compiler);
	
	Type* type = Type::getInt32Ty(*compiler->llvmContext);
	
	Value* llvmArgument = compiler->llvmBuilder->CreateAlloca(type, nullptr);
	
	std::vector<Value*> scanfArgs = { format, llvmArgument };
	
	compiler->llvmBuilder->CreateCall(scanf, scanfArgs);
	
	return compiler->llvmBuilder->CreateLoad(type, llvmArgument);
	
}

PVariance PInput::getVariance(Compiler* compiler) {
	return PVariance::LET;
}
