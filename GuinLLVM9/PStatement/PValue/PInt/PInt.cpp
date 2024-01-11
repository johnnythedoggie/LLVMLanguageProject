//
//  PInt.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#include "PInt.hpp"

Value* PInt::getLLVMValue(Compiler* compiler) {
	return ConstantInt::get(Type::getInt32Ty(*compiler->llvmContext), value);
}

void PInt::compile(Compiler* compiler) {
	// do nothing
	return;
}

PVariance PInt::getVariance(Compiler* compiler) {
	return PVariance::CONST;
}
