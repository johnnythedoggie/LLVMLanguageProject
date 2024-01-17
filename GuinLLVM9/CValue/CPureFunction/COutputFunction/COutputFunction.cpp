//
//  COutputFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "COutputFunction.hpp"
#include "CTuple.hpp"

void COutputFunction::makeFunction(Compiler* compiler) {
	Type* intType = Type::getInt32Ty(*compiler->llvmContext);
	std::vector<Type*> printfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* printfType = FunctionType::get(intType, printfArgTypes, true);
	Function::Create(printfType, Function::ExternalLinkage, "printf", *compiler->llvmModule);
	this->printfFormat = compiler->llvmBuilder->CreateGlobalStringPtr("%u\n", "printf_format");
	CPureFunction::makeFunction(compiler);
	function->setName("output");
}

void COutputFunction::makeBody(Compiler* compiler, Value* argument) {
	Function* printf = compiler->llvmModule->getFunction("printf");
	std::vector<Value*> printfArgs = { printfFormat, argument };
	compiler->llvmBuilder->CreateCall(printf, printfArgs);
	Value* result = CTuple({}).getLLVMValue(compiler);
	compiler->llvmBuilder->CreateRet(result);
}
