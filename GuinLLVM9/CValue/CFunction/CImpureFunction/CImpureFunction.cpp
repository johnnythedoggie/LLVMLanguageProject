//
//  CImpureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#include "CImpureFunction.hpp"
#include "CImpureFunctionType.hpp"

CType* CImpureFunction::getConstantType() {
	return new CImpureFunctionType(inputType, outputType);
}

void CImpureFunction::makeFunction(Compiler* compiler) {
	
	Type* opaqueContextLLVMType = CImpureFunctionType::opaqueContextLLVMType(compiler);
	
	std::vector<Type*> argTypes = { inputType->asLLVMType(compiler), opaqueContextLLVMType->getPointerTo() };
	FunctionType* type = FunctionType::get(outputType->asLLVMType(compiler), argTypes, false);
	
	Function::Create(type, Function::ExternalLinkage, id(), *compiler->llvmModule);
	
	function = compiler->llvmModule->getFunction(id());
	
	BasicBlock* entryBlock = BasicBlock::Create(*compiler->llvmContext, "entry", function);
	
	//IRBuilder<>::InsertPoint continueLocation = compiler->llvmBuilder->saveIP();
	
	// Prepare a new scope
	Scope* newScope = new Scope();
	newScope->parentScope = compiler->scope;
	newScope->argumentType = inputType;
	newScope->returnType = outputType;
	newScope->argument = function->args().begin();
	newScope->captureArgument = std::next(function->arg_begin(), 1);
	newScope->isPureScope = false;
	newScope->parentInsertPoint = compiler->llvmBuilder->saveIP();
	
	compiler->scope = newScope;
	compiler->llvmBuilder->SetInsertPoint(entryBlock);
	
	// make the actual function
	this->makeBody(compiler);
	
	// Put back how things were
	compiler->llvmBuilder->restoreIP(newScope->parentInsertPoint);
	
	compiler->scope = newScope->parentScope;
	delete newScope;
	
}
