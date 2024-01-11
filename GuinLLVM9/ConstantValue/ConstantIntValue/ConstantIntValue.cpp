//
//  ConstantInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantIntValue.hpp"
#include "ConstantIntType.hpp"

std::string ConstantIntValue::identifierString() {
	return std::to_string(value);
}

Value* ConstantIntValue::getLLVMValue(Compiler* compiler) {
	return ConstantInt::get(Type::getInt32Ty(*compiler->llvmContext), value);
}

ConstantType* ConstantIntValue::getConstantType() {
	return new ConstantIntType();
}
