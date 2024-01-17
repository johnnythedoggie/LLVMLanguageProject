//
//  PFunctionDefinition.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PFunctionDefinition.hpp"
#include "CCustomPureFunction.hpp"

CValue* PFunctionDefinition::asConstantValue(Compiler* compiler) {
	CPureFunctionType* ft = getConstantType(compiler);
	CType* inputType = ft->inputType;
	CType* outputType = ft->outputType;
	return new CCustomPureFunction(functionBody, inputType, outputType);
}

CPureFunctionType* PFunctionDefinition::getConstantType(Compiler* compiler) {
	auto ft = dynamic_cast<CPureFunctionType*>(fucntionType->asConstantValue(compiler));
	std::string errorMessage = "Cannot define function of non constant function type.";
	if (!ft) throw errorMessage;
	return ft;
}

Value* PFunctionDefinition::asLLVMValue(Compiler* compiler) {
	return asConstantValue(compiler)->getLLVMValue(compiler);
}

PVariance PFunctionDefinition::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}
