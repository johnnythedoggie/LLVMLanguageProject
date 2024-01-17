//
//  ConstantFunctionValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantFunctionValue.hpp"
#include "ConstantFunctionType.hpp"

int ConstantFunctionValue::globalIdentifier = 0;

std::string ConstantFunctionValue::identifierString() {
	return "function" + std::to_string(identifier);
}

ConstantType* ConstantFunctionValue::getConstantType() {
	return new ConstantFunctionType(inputType, outputType);
}

void ConstantFunctionValue::makeFunction(Compiler* compiler) {
	
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
