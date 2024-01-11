//
//  Compiler.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "Compiler.hpp"

Compiler::Compiler() {
	
	llvmContext = new LLVMContext();
	llvmModule = new Module("moduleName", *llvmContext);
	llvmBuilder = new IRBuilder<>(*llvmContext);
	
	FunctionType* mainFunctionType = FunctionType::get(Type::getVoidTy(*llvmContext), {}, false);
	
	mainFunction = Function::Create(
		 mainFunctionType,
		 Function::ExternalLinkage,
		 "main",
		 llvmModule
	);
	
	auto entryBlock = BasicBlock::Create(*llvmContext, "entry", mainFunction);
	llvmBuilder->SetInsertPoint(entryBlock);
	
}

void Compiler::close() {
	
	llvmBuilder->CreateRetVoid();
	
	verifyFunction(*mainFunction);
	
	mainFunction->print(errs());
	
}
