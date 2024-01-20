//
//  CPureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CPureFunction.hpp"
#include "CPureFunctionType.hpp"

CType* CPureFunction::getConstantType() {
	return new CPureFunctionType(inputType, outputType);
}

void CPureFunction::makeFunction(Compiler* compiler) {
	
	std::vector<Type*> argTypes = { inputType->asLLVMType(compiler) };
	FunctionType* type = FunctionType::get(outputType->asLLVMType(compiler), argTypes, false);
	
	Function::Create(type, Function::ExternalLinkage, identifierString(), *compiler->llvmModule);
	
	function = compiler->llvmModule->getFunction(identifierString());
	
	BasicBlock* entryBlock = BasicBlock::Create(*compiler->llvmContext, "entry", function);
	
	IRBuilder<>::InsertPoint previousLocation = compiler->llvmBuilder->saveIP();
	compiler->llvmBuilder->SetInsertPoint(entryBlock);
	
	// Prepare a new scope
	Scope* newScope = new Scope();
	newScope->parentScope = compiler->scope;
	newScope->argumentType = inputType;
	newScope->returnType = outputType;
	newScope->argument = function->args().begin();
	newScope->isPureScope = true;
	
	compiler->scope = newScope;
	
	this->makeBody(compiler);
	
	// Put back how things were
	compiler->scope = newScope->parentScope;
	delete newScope;
	
	compiler->llvmBuilder->restoreIP(previousLocation);
	
}
