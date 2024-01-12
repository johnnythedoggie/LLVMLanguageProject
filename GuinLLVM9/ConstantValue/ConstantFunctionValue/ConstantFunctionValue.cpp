//
//  ConstantFunctionValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantFunctionValue.hpp"
#include "ConstantFunctionType.hpp"

int ConstantFunctionValue::globalIdentifier = 0;

std::string ConstantFunctionValue::identifierString() {
	return "function" + std::to_string(identifier);
}

ConstantType* ConstantFunctionValue::getConstantType() {
	return new ConstantFunctionType(inputType, outputType);
}
