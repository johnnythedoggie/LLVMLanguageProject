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
#include "PFunctionDefinition.hpp"
#include <cassert>

CValue* PFunctionCall::asConstantValue(Compiler* compiler) {
	CValue* constantValue = firstValue->asConstantValue(compiler);
	CFunctionType* type = dynamic_cast<CFunctionType*>(constantValue);
	PFunctionDefinition* body = dynamic_cast<PFunctionDefinition*>(secondValue);
	if(!type || !body) return nullptr;
	secondValue->expectedType(type);
	return secondValue->asConstantValue(compiler);
}

CType* PFunctionCall::getConstantType(Compiler* compiler) {
	CType* type = firstValue->getConstantType(compiler);
	CFunctionType* functionType = dynamic_cast<CFunctionType*>(type);
	if (functionType) {
		// function call
		return functionType->outputType;
	} else {
		// function type specification
		CValue* value = firstValue->asConstantValue(compiler);
		CType* ctype = dynamic_cast<CType*>(value);
		assert(ctype && "This isn't a function call or type specification.");
		return ctype;
	}
}

Value* PFunctionCall::valueAsPureFunctionCall(Compiler* compiler) {
	CType* constantType = firstValue->getConstantType(compiler);
	CPureFunctionType* pureFunctionType = dynamic_cast<CPureFunctionType*>(constantType);
	if (!pureFunctionType) return nullptr;
	std::string functionInputType = pureFunctionType->inputType->id();
	secondValue->expectedType(pureFunctionType->inputType);
	std::string argumentType = secondValue->getConstantType(compiler)->id();
	assert(functionInputType == argumentType && "Argument type must match pure function input type.");
	Value* function = firstValue->asLLVMValue(compiler);
	Value* argument = secondValue->asLLVMValue(compiler);
	FunctionType* type = pureFunctionType->getLLVMFunctionType(compiler);
	return compiler->llvmBuilder->CreateCall(type, function, { argument });
}

Value* PFunctionCall::valueAsImpureFunctionCall(Compiler* compiler) {
	CType* constantType = firstValue->getConstantType(compiler);
	CImpureFunctionType* impureFunctionType = dynamic_cast<CImpureFunctionType*>(constantType);
	if (!impureFunctionType) return nullptr;
	std::string functionInputType = impureFunctionType->inputType->id();
	secondValue->expectedType(impureFunctionType->inputType);
	std::string argumentType = secondValue->getConstantType(compiler)->id();
	assert(functionInputType == argumentType && "Argument type must match impure function input type.");
	Value* functionCaptureListPair = firstValue->asLLVMValue(compiler);
	Value* function = compiler->llvmBuilder->CreateExtractValue(functionCaptureListPair, 0);
	Value* captureArgument = compiler->llvmBuilder->CreateExtractValue(functionCaptureListPair, 1);
	Value* argument = secondValue->asLLVMValue(compiler);
	FunctionType* type = impureFunctionType->getLLVMFunctionType(compiler);
	return compiler->llvmBuilder->CreateCall(type, function, { argument, captureArgument });
}

Value* PFunctionCall::valueAsFunctionTypeSpecification(Compiler* compiler) {
	CValue* constantValue = firstValue->asConstantValue(compiler);
	CFunctionType* type = dynamic_cast<CFunctionType*>(constantValue);
	PFunctionDefinition* body = dynamic_cast<PFunctionDefinition*>(secondValue);
	if(!type || !body) return nullptr;
	assert(!body->functionType && "Cannot type a function twice.");
	secondValue->expectedType(type);
	return secondValue->asLLVMValue(compiler);
}

Value* PFunctionCall::asLLVMValue(Compiler* compiler) {
	Value* result;
	result = valueAsPureFunctionCall(compiler);
	if (result) return result;
	result = valueAsImpureFunctionCall(compiler);
	if (result) return result;
	result = valueAsFunctionTypeSpecification(compiler);
	if (result) return result;
	assert(false && "The left of a PFunctionCall must be a function or function type.");
}

PVariance PFunctionCall::getVariance(Compiler* compiler) {
	CType* type = firstValue->getConstantType(compiler);
	CFunctionType* functionType = dynamic_cast<CFunctionType*>(type);
	if (functionType) {
		// this is a function call, eventually this will be able to be const
		return PVariance::LET;
	} else {
		// this is a function body type specification
		return PVariance::CONST;
	}
}
