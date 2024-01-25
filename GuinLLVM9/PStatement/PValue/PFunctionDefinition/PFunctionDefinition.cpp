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
	auto ft = dynamic_cast<CFunctionType*>(fucntionType->asConstantValue(compiler));
	assert(ft && "Function must be of constant function type.");
	return ft;
}

Value* PFunctionDefinition::asLLVMValue(Compiler* compiler) {
	return asConstantValue(compiler)->getLLVMValue(compiler);
}

PVariance PFunctionDefinition::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}
