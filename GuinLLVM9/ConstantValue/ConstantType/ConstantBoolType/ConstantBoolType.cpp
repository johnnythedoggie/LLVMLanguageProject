//
//  ConstantBoolType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantBoolType.hpp"

std::string ConstantBoolType::identifierString() {
	return "Bool";
}

Type* ConstantBoolType::asLLVMType(Compiler* compiler) {
	return Type::getInt1Ty(*compiler->llvmContext);
}
