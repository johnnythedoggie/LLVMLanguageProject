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

void addBuiltIn(Compiler* compiler, std::string id, CValue* value) {
	compiler->scope->scopedIdentifierToValue[id] = ValueHandler::newConstantValue(compiler, value, id);
}

Compiler::Compiler() {
	
	scope = new Scope();
	
	addBuiltIn(this, "Int", new CIntType());
	addBuiltIn(this, "true", new CBoolValue(true));
	addBuiltIn(this, "false", new CBoolValue(false));
	addBuiltIn(this, "Bool", new CBoolType());
	addBuiltIn(this, "Type", new CTypeType());
	addBuiltIn(this, "Void", new CTupleType({}));
	
	// should input and output be considered 'const'?
	// They do have a constant value...
	// They also mess up pure functions if they dont have to be captured
	addBuiltIn(this, "input", new CInputFunction());
	addBuiltIn(this, "output", new COutputFunction());
	
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
