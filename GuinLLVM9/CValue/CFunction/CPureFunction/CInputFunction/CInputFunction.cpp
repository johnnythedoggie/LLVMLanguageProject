//
//  CInputFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CInputFunction.hpp"

void CInputFunction::makeBody(Compiler* compiler) {
	Type* intType = Type::getInt32Ty(*compiler->llvmContext);
	std::vector<Type*> scanfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* scanfType = FunctionType::get(intType, scanfArgTypes, true);
	Function::Create(scanfType, Function::ExternalLinkage, "scanf", *compiler->llvmModule);
	Value* scanfFormat = compiler->llvmBuilder->CreateGlobalStringPtr("%u", "scanf_format");
	
	Function* scanf = compiler->llvmModule->getFunction("scanf");
	Value* scanfArgument = compiler->llvmBuilder->CreateAlloca(intType, nullptr);
	std::vector<Value*> scanfArgs = { scanfFormat, scanfArgument };
	compiler->llvmBuilder->CreateCall(scanf, scanfArgs);
	Value* result = compiler->llvmBuilder->CreateLoad(intType, scanfArgument);
	compiler->llvmBuilder->CreateRet(result);
}
