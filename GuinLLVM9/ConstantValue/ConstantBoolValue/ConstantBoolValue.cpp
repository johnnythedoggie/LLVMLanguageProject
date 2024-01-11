//
//  ConstantBoolValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantBoolValue.hpp"
#include "ConstantBoolType.hpp"

std::string ConstantBoolValue::identifierString() {
	return value ? "true" : "false";
}

Value* ConstantBoolValue::getLLVMValue(Compiler* compiler) {
	return ConstantInt::get(Type::getInt1Ty(*compiler->llvmContext), value);
}

ConstantType* ConstantBoolValue::getConstantType() {
	return new ConstantBoolType();
}

