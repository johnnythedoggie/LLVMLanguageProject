//
//  PFunctionCall.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PFunctionCall.hpp"
#include "ConstantFunctionType.hpp"

ConstantValue* PFunctionCall::getConstantValue(Compiler* compiler) {
	return nullptr;
}

ConstantType* PFunctionCall::getConstantType(Compiler* compiler) {
	ConstantType* type = functionValue->getConstantType(compiler);
	ConstantFunctionType* functionType = dynamic_cast<ConstantFunctionType*>(type);
	return functionType->outputType;
}

Value* PFunctionCall::getLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Incorrect types for function call.";
	ConstantType* constantType = functionValue->getConstantType(compiler);
	ConstantFunctionType* constantFunctionType = dynamic_cast<ConstantFunctionType*>(constantType);
	if (!constantFunctionType) throw errorMessage;
	std::string functionInputType = constantFunctionType->inputType->identifierString();
	std::string argumentType = argumentValue->getConstantType(compiler)->identifierString();
	if (functionInputType != argumentType) throw errorMessage;
	Value* function = functionValue->getLLVMValue(compiler);
	Value* argument = argumentValue->getLLVMValue(compiler);
	return compiler->llvmBuilder->CreateCall(constantFunctionType->getLLVMFunctionType(compiler), function, { argument });
}

PVariance PFunctionCall::getVariance(Compiler* compiler) {
	return PVariance::LET;
}
