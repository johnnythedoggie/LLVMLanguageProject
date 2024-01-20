//
//  COutputFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "COutputFunction.hpp"
#include "CTuple.hpp"

void COutputFunction::makeBody(Compiler* compiler) {
	Type* intType = Type::getInt32Ty(*compiler->llvmContext);
	std::vector<Type*> printfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* printfType = FunctionType::get(intType, printfArgTypes, true);
	Function::Create(printfType, Function::ExternalLinkage, "printf", *compiler->llvmModule);
	Value* printfFormat = compiler->llvmBuilder->CreateGlobalStringPtr("%u\n", "printf_format");
	
	Function* printf = compiler->llvmModule->getFunction("printf");
	std::vector<Value*> printfArgs = { printfFormat, compiler->scope->argument };
	compiler->llvmBuilder->CreateCall(printf, printfArgs);
	Value* result = CTuple({}).getLLVMValue(compiler);
	compiler->llvmBuilder->CreateRet(result);
}
