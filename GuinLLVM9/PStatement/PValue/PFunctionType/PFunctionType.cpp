//
//  PFunctionType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PFunctionType.hpp"
#include "ConstantFunctionType.hpp"
#include "ConstantTypeType.hpp"

ConstantValue* PFunctionType::getConstantValue(Compiler* compiler) {
	ConstantType* left = dynamic_cast<ConstantType*>(inputType->getConstantValue(compiler));
	ConstantType* right = dynamic_cast<ConstantType*>(outputType->getConstantValue(compiler));
	std::string errorMessage = "Function type composed from functions.";
	if (!left || !right) throw errorMessage;
	return new ConstantFunctionType(left, right);
}

ConstantType* PFunctionType::getConstantType(Compiler* compiler) {
	return new ConstantTypeType();
}

Value* PFunctionType::getLLVMValue(Compiler* compiler) {
	return nullptr;
}

PVariance PFunctionType::getVariance(Compiler* compiler) {
	PVariance inputVariance = inputType->getVariance(compiler);
	PVariance outputVariance = outputType->getVariance(compiler);
	if (inputVariance == PVariance::CONST && outputVariance == PVariance::CONST) {
		return PVariance::CONST;
	} else {
		return PVariance::LET;
	}
}
