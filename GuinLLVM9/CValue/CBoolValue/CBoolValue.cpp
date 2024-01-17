//
//  CBoolValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CBoolValue.hpp"
#include "CBoolType.hpp"

std::string CBoolValue::identifierString() {
	return value ? "true" : "false";
}

Value* CBoolValue::getLLVMValue(Compiler* compiler) {
	return ConstantInt::get(Type::getInt1Ty(*compiler->llvmContext), value);
}

CType* CBoolValue::getConstantType() {
	return new CBoolType();
}

