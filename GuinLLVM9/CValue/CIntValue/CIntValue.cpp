//
//  CInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CIntValue.hpp"
#include "CIntType.hpp"

std::string CIntValue::identifierString() {
	return std::to_string(value);
}

Value* CIntValue::getLLVMValue(Compiler* compiler) {
	return ConstantInt::get(Type::getInt32Ty(*compiler->llvmContext), value);
}

CType* CIntValue::getConstantType() {
	return new CIntType();
}
