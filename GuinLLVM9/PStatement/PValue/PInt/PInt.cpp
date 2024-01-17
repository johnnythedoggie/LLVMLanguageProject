//
//  PInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PInt.hpp"
#include "ConstantIntValue.hpp"
#include "ConstantIntType.hpp"

Value* PInt::asLLVMValue(Compiler* compiler) {
	return asConstantValue(compiler)->getLLVMValue(compiler);
}

PVariance PInt::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}

ConstantValue* PInt::asConstantValue(Compiler* compiler) {
	return new ConstantIntValue(value);
}

ConstantType* PInt::getConstantType(Compiler* compiler) {
	return new ConstantIntType();
}
