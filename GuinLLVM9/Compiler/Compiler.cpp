//
//  Compiler.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "Compiler.hpp"
#include "ValueHandler.hpp"

#include "ConstantIntType.hpp"
#include "ConstantBoolType.hpp"
#include "ConstantBoolValue.hpp"
#include "ConstantTypeType.hpp"

Compiler::Compiler() {
	
	valueForIdentifier["Int"] = ValueHandler::newConstantValue(this, new ConstantIntType(), "Int");
	valueForIdentifier["true"] = ValueHandler::newConstantValue(this, new ConstantBoolValue(true), "Int");
	valueForIdentifier["false"] = ValueHandler::newConstantValue(this, new ConstantBoolValue(false), "Int");
	valueForIdentifier["Bool"] = ValueHandler::newConstantValue(this, new ConstantBoolType(), "Int");
	valueForIdentifier["Type"] = ValueHandler::newConstantValue(this, new ConstantTypeType(), "Int");
	
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
	
}
