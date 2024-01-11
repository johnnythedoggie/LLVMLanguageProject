//
//  ConstantIntType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantIntType.hpp"

std::string ConstantIntType::identifierString() {
	return "Int";
}

Type* ConstantIntType::getLLVMType(Compiler* compiler) {
	return Type::getInt32Ty(*compiler->llvmContext);
}

