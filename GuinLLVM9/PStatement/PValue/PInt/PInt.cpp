//
//  PInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PInt.hpp"
#include "CIntValue.hpp"
#include "CIntType.hpp"

Value* PInt::asLLVMValue(Compiler* compiler) {
	return asConstantValue(compiler)->getLLVMValue(compiler);
}

PVariance PInt::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}

CValue* PInt::asConstantValue(Compiler* compiler) {
	return new CIntValue(value);
}

CType* PInt::getConstantType(Compiler* compiler) {
	return new CIntType();
}
