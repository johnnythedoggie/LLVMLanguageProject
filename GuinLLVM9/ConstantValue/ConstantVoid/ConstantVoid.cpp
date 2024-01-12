//
//  ConstantVoid.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantVoid.hpp"
#include "ConstantVoidType.hpp"

ConstantType* ConstantVoid::getConstantType() {
	return new ConstantVoidType();
}

std::string ConstantVoid::identifierString() {
	return "void";
}

Value* ConstantVoid::getLLVMValue(Compiler* compiler) {
	StructType* type = StructType::get(*compiler->llvmContext, { });
	return ConstantStruct::get(type, { });
}
