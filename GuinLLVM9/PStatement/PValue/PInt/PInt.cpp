//
//  PInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PInt.hpp"
#include "ConstantIntValue.hpp"
#include "ConstantIntType.hpp"

Value* PInt::getLLVMValue(Compiler* compiler) {
	return ConstantInt::get(Type::getInt32Ty(*compiler->llvmContext), value);
}

PVariance PInt::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}

ConstantValue* PInt::getConstantValue(Compiler* compiler) {
	return new ConstantIntValue(value);
}

ConstantType* PInt::getConstantType(Compiler* compiler) {
	return new ConstantIntType();
}
