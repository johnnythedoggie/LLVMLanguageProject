//
//  PArgument.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "PArgument.hpp"


Value* PArgument::asLLVMValue(Compiler* compiler) {
	return compiler->scope.argument;
}

ConstantValue* PArgument::asConstantValue(Compiler* compiler) {
	return nullptr;
}

ConstantType* PArgument::getConstantType(Compiler* compiler) {
	return compiler->scope.argumentType;
}

PVariance PArgument::getVariance(Compiler* compiler) {
	return PVariance::LET;
}
