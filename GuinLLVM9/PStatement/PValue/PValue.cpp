//
//  PValue.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PValue.hpp"

Type* PValue::getLLVMType(Compiler* compiler) {
	return getConstantType(compiler)->asLLVMType(compiler);
}

Value* PValue::getMemoryLocation(Compiler* compiler) {
	return nullptr;
}

void PValue::compile(Compiler* compiler) {
	asLLVMValue(compiler);
}

void PValue::expectedType(CType* type) {
	// do nothing
}
