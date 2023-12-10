//
//  IRGenerator.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "IRGenerator.h"

IRGenerator::IRGenerator(std::queue<GStatement*> statements) {
	
	llvmContext = new LLVMContext();
	llvmModule = new Module("moduleName", *llvmContext);
	llvmBuilder = new IRBuilder<>(*llvmContext);
	
	identifierToValueMap = {};
	
	generate(statements);
	
}

void IRGenerator::generate(std::queue<GStatement*> statements) {
	
	auto mainFunctionType = FunctionType::get(Type::getVoidTy(*llvmContext), {}, false);
	
	auto mainFunction = Function::Create(
		mainFunctionType,
		Function::ExternalLinkage,
		"main",
		llvmModule
	);
	
	auto entryBlock = BasicBlock::Create(*llvmContext, "entry", mainFunction);
	llvmBuilder->SetInsertPoint(entryBlock);
	
	while (!statements.empty()) {
		
		GStatement* statement = statements.front();
		statements.pop();
		
		statement->generateIR(this);
		
	}
	
	llvmBuilder->CreateRetVoid();
	
	verifyFunction(*mainFunction);
	
	mainFunction->print(errs());
	
}
