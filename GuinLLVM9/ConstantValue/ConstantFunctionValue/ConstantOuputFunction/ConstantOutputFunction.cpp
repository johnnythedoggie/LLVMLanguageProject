//
//  ConstantOutputFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantOutputFunction.hpp"
#include "ConstantVoid.hpp"

Function* ConstantOutputFunction::output = nullptr;

void ConstantOutputFunction::setup(Compiler* compiler) {
	
	std::vector<Type*> printfArgTypes = { Type::getInt8PtrTy(*compiler->llvmContext) };
	FunctionType* printfType = FunctionType::get(compiler->llvmBuilder->getInt32Ty(), printfArgTypes, true);
	
	Function::Create(printfType, Function::ExternalLinkage, "printf", *compiler->llvmModule);
	
	Value* format = compiler->llvmBuilder->CreateGlobalStringPtr("%u\n", "printf_format");
	
	Function* printf = compiler->llvmModule->getFunction("printf");
	
	Type* intType = Type::getInt32Ty(*compiler->llvmContext);
	Type* voidType = StructType::get(*compiler->llvmContext, { });
	
	FunctionType* outputFunctionType = FunctionType::get(voidType, { intType }, false);
	
	Function* outputFunction = Function::Create(
		outputFunctionType,
		Function::ExternalLinkage,
		"output",
		compiler->llvmModule
	);
	
	BasicBlock* entryBlock = BasicBlock::Create(*compiler->llvmContext, "entry", outputFunction);
	
	IRBuilder<>::InsertPoint previousLocation = compiler->llvmBuilder->saveIP();
	
	compiler->llvmBuilder->SetInsertPoint(entryBlock);
	
	std::vector<Value*> printfArgs = { format, outputFunction->args().begin() };
	
	compiler->llvmBuilder->CreateCall(printf, printfArgs);
	
	Value* result = ConstantVoid().getLLVMValue(compiler);
	
	compiler->llvmBuilder->CreateRet(result);
	
	compiler->llvmBuilder->restoreIP(previousLocation);
	
	output = outputFunction;
	
}

Value* ConstantOutputFunction::getLLVMValue(Compiler* compiler) {
	if (!output) setup(compiler);
	return output;
}
