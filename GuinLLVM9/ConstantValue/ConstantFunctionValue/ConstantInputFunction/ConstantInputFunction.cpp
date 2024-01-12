//
//  ConstantInputFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantInputFunction.hpp"

Function* ConstantInputFunction::input = nullptr;

void ConstantInputFunction::setup(Compiler* compiler) {
	
	std::vector<Type*> scanfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* scanfType = FunctionType::get(compiler->llvmBuilder->getInt32Ty(), scanfArgTypes, true);
	
	Function::Create(scanfType, Function::ExternalLinkage, "scanf", *compiler->llvmModule);
	
	Value* format = compiler->llvmBuilder->CreateGlobalStringPtr("%u", "scanf_format");
	
	Function* scanf = compiler->llvmModule->getFunction("scanf");
	
	Type* intType = Type::getInt32Ty(*compiler->llvmContext);
	Type* voidType = StructType::get(*compiler->llvmContext, { });
	
	FunctionType* inputFunctionType = FunctionType::get(intType, { voidType }, false);
	
	Function* inputFunction = Function::Create(
		inputFunctionType,
		Function::ExternalLinkage,
		"input",
		compiler->llvmModule
	);
	
	BasicBlock* entryBlock = BasicBlock::Create(*compiler->llvmContext, "entry", inputFunction);
	
	IRBuilder<>::InsertPoint previousLocation = compiler->llvmBuilder->saveIP();
	
	compiler->llvmBuilder->SetInsertPoint(entryBlock);
	
	Value* scanfArgument = compiler->llvmBuilder->CreateAlloca(intType, nullptr);
	
	std::vector<Value*> scanfArgs = { format, scanfArgument };
	
	compiler->llvmBuilder->CreateCall(scanf, scanfArgs);
	
	Value* result = compiler->llvmBuilder->CreateLoad(intType, scanfArgument);
	
	compiler->llvmBuilder->CreateRet(result);
	
	compiler->llvmBuilder->restoreIP(previousLocation);
	
	input = inputFunction;
	
	input->setName("input");
	
}

Value* ConstantInputFunction::getLLVMValue(Compiler* compiler) {
	if (!input) setup(compiler);
	return input;
}
