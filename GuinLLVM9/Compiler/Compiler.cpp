//
//  Compiler.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "Compiler.hpp"
#include "ValueHandler.hpp"
#include "CIntType.hpp"
#include "CBoolType.hpp"
#include "CBoolValue.hpp"
#include "CTypeType.hpp"
#include "CInputFunction.hpp"
#include "COutputFunction.hpp"
#include "CTupleType.hpp"

Compiler::Compiler() {
	
	valueForIdentifier["Int"] = ValueHandler::newConstantValue(this, new CIntType(), "Int");
	valueForIdentifier["true"] = ValueHandler::newConstantValue(this, new CBoolValue(true), "true");
	valueForIdentifier["false"] = ValueHandler::newConstantValue(this, new CBoolValue(false), "false");
	valueForIdentifier["Bool"] = ValueHandler::newConstantValue(this, new CBoolType(), "Bool");
	valueForIdentifier["Type"] = ValueHandler::newConstantValue(this, new CTypeType(), "Type");
	valueForIdentifier["input"] = ValueHandler::newConstantValue(this, new CInputFunction(), "input");
	valueForIdentifier["output"] = ValueHandler::newConstantValue(this, new COutputFunction(), "output");
	valueForIdentifier["Void"] = ValueHandler::newConstantValue(this, new CTupleType({}), "Void");
	
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
