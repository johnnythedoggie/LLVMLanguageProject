//
//  PFunctionCall.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PFunctionCall.hpp"
#include "CPureFunctionType.hpp"
#include "CImpureFunctionType.hpp"
#include "CImpureFunction.hpp"

CValue* PFunctionCall::asConstantValue(Compiler* compiler) {
	return nullptr;
}

CType* PFunctionCall::getConstantType(Compiler* compiler) {
	CType* type = functionValue->getConstantType(compiler);
	CFunctionType* functionType = dynamic_cast<CFunctionType*>(type);
	return functionType->outputType;
}

Value* PFunctionCall::asLLVMValue(Compiler* compiler) {
	std::string errorMessage = "Incorrect types for function call.";
	CType* constantType = functionValue->getConstantType(compiler);
	CPureFunctionType* pureFunctionType = dynamic_cast<CPureFunctionType*>(constantType);
	CImpureFunctionType* impureFunctionType = dynamic_cast<CImpureFunctionType*>(constantType);
	if (pureFunctionType) {
		std::string functionInputType = pureFunctionType->inputType->identifierString();
		std::string argumentType = argumentValue->getConstantType(compiler)->identifierString();
		if (functionInputType != argumentType) throw errorMessage;
		Value* function = functionValue->asLLVMValue(compiler);
		Value* argument = argumentValue->asLLVMValue(compiler);
		return compiler->llvmBuilder->CreateCall(pureFunctionType->getLLVMFunctionType(compiler), function, { argument });
	} else if (impureFunctionType) {
		std::string functionInputType = impureFunctionType->inputType->identifierString();
		std::string argumentType = argumentValue->getConstantType(compiler)->identifierString();
		if (functionInputType != argumentType) throw errorMessage;
		Value* functionCaptureListPair = functionValue->asLLVMValue(compiler);
		Value* function = compiler->llvmBuilder->CreateExtractValue(functionCaptureListPair, 0);
		Value* captureArgument = compiler->llvmBuilder->CreateExtractValue(functionCaptureListPair, 1);
		Value* argument = argumentValue->asLLVMValue(compiler);
		
		return compiler->llvmBuilder->CreateCall(impureFunctionType->getLLVMFunctionType(compiler), function, { argument, captureArgument });
	} else {
		throw errorMessage;
	}
}

PVariance PFunctionCall::getVariance(Compiler* compiler) {
	return PVariance::LET;
}
