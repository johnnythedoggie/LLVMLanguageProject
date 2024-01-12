//
//  ConstantFunctionValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantFunctionValue.hpp"
#include "ConstantFunctionType.hpp"

std::string ConstantFunctionValue::identifierString() {
	return "{" + name + ", " + inputType->identifierString() + ", " + outputType->identifierString() + "}";
}

ConstantType* ConstantFunctionValue::getConstantType() {
	return new ConstantFunctionType(inputType, outputType);
}
