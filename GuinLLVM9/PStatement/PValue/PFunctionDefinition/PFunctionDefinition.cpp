//
//  PFunctionDefinition.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PFunctionDefinition.hpp"
#include "CCustomPureFunction.hpp"
#include "CCustomImpureFunction.hpp"
#include "CImpureFunctionType.hpp"

CValue* PFunctionDefinition::asConstantValue(Compiler* compiler) {
	CFunctionType* ft = getConstantType(compiler);
	CType* inputType = ft->inputType;
	CType* outputType = ft->outputType;
	if (ft->isPure) {
		return new CCustomPureFunction(functionBody, inputType, outputType);
	} else {
		return new CCustomImpureFunction(functionBody, inputType, outputType);
	}
}

CFunctionType* PFunctionDefinition::getConstantType(Compiler* compiler) {
	assert(functionType && "Function does not have enough type information.");
	return functionType;
}

Value* PFunctionDefinition::asLLVMValue(Compiler* compiler) {
	return asConstantValue(compiler)->getLLVMValue(compiler);
}

PVariance PFunctionDefinition::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}

void PFunctionDefinition::expectedType(CType* type) {
	functionType = dynamic_cast<CFunctionType*>(type);
	assert(functionType && "Function must be of constant function type.");
};
