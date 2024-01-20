//
//  PFunctionType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "PFunctionType.hpp"
#include "CImpureFunctionType.hpp"
#include "CPureFunctionType.hpp"
#include "CTypeType.hpp"

CValue* PFunctionType::asConstantValue(Compiler* compiler) {
	CType* left = dynamic_cast<CType*>(inputType->asConstantValue(compiler));
	CType* right = dynamic_cast<CType*>(outputType->asConstantValue(compiler));
	std::string errorMessage = "Function type composed from functions.";
	if (!left || !right) throw errorMessage;
	if (isPure) {
		return new CPureFunctionType(left, right);
	} else {
		return new CImpureFunctionType(left, right);
	}
}

CType* PFunctionType::getConstantType(Compiler* compiler) {
	return new CTypeType();
}

Value* PFunctionType::asLLVMValue(Compiler* compiler) {
	StructType* type = StructType::get(*compiler->llvmContext, { });
	return ConstantStruct::get(type, { });
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
