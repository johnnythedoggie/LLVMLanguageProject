//
//  PFunctionCall.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PFunctionCall.hpp"
#include "CPureFunctionType.hpp"

CValue* PFunctionCall::asConstantValue(Compiler* compiler) {
	return nullptr;
}

CType* PFunctionCall::getConstantType(Compiler* compiler) {
	CType* type = functionValue->getConstantType(compiler);
	CPureFunctionType* functionType = dynamic_cast<CPureFunctionType*>(type);
	return functionType->outputType;
}

Value* PFunctionCall::asLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Incorrect types for function call.";
	CType* constantType = functionValue->getConstantType(compiler);
	CPureFunctionType* constantFunctionType = dynamic_cast<CPureFunctionType*>(constantType);
	if (!constantFunctionType) throw errorMessage;
	std::string functionInputType = constantFunctionType->inputType->identifierString();
	std::string argumentType = argumentValue->getConstantType(compiler)->identifierString();
	if (functionInputType != argumentType) throw errorMessage;
	Value* function = functionValue->asLLVMValue(compiler);
	Value* argument = argumentValue->asLLVMValue(compiler);
	return compiler->llvmBuilder->CreateCall(constantFunctionType->getLLVMFunctionType(compiler), function, { argument });
}

PVariance PFunctionCall::getVariance(Compiler* compiler) {
	return PVariance::LET;
}
