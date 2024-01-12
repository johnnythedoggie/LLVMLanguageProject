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
#include "ConstantVoid.hpp"
#include "ConstantVoidType.hpp"
#include "ConstantInputFunction.hpp"

Compiler::Compiler() {
	
	valueForIdentifier["Int"] = ValueHandler::newConstantValue(this, new ConstantIntType(), "Int");
	valueForIdentifier["true"] = ValueHandler::newConstantValue(this, new ConstantBoolValue(true), "true");
	valueForIdentifier["false"] = ValueHandler::newConstantValue(this, new ConstantBoolValue(false), "false");
	valueForIdentifier["Bool"] = ValueHandler::newConstantValue(this, new ConstantBoolType(), "Bool");
	valueForIdentifier["Type"] = ValueHandler::newConstantValue(this, new ConstantTypeType(), "Type");
	valueForIdentifier["void"] = ValueHandler::newConstantValue(this, new ConstantVoid(), "void");
	valueForIdentifier["Void"] = ValueHandler::newConstantValue(this, new ConstantVoidType(), "Void");
	valueForIdentifier["input"] = ValueHandler::newConstantValue(this, new ConstantInputFunction(), "input");
	
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
