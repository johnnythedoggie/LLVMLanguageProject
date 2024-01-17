//
//  PFunctionDefinition.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PFunctionDefinition.hpp"
#include "ConstantUserDefinedFunction.hpp"

ConstantValue* PFunctionDefinition::asConstantValue(Compiler* compiler) {
	ConstantFunctionType* ft = getConstantType(compiler);
	ConstantType* inputType = ft->inputType;
	ConstantType* outputType = ft->outputType;
	return new ConstantUserDefinedFunction(functionBody, inputType, outputType);
}

ConstantFunctionType* PFunctionDefinition::getConstantType(Compiler* compiler) {
	auto ft = dynamic_cast<ConstantFunctionType*>(fucntionType->asConstantValue(compiler));
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
