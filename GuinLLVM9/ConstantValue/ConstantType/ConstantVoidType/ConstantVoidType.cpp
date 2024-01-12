//
//  ConstantVoidType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantVoidType.hpp"

std::string ConstantVoidType::identifierString() {
	return "Void";
}

Type* ConstantVoidType::getLLVMType(Compiler* compiler) {
	return StructType::get(*compiler->llvmContext, { });
}
