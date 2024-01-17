//
//  CPureFunction.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CPureFunction.hpp"
#include "CPureFunctionType.hpp"

int CPureFunction::globalIdentifier = 0;

std::string CPureFunction::identifierString() {
	return "function" + std::to_string(identifier);
}

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
	
	// virtual
	this->makeBody(compiler, function->args().begin());
	
	compiler->llvmBuilder->restoreIP(previousLocation);
	
}
