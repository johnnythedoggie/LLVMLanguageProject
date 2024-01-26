//
//  CBoolType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CBoolType.hpp"

std::string CBoolType::id() {
	return "Bool";
}

Type* CBoolType::asLLVMType(Compiler* compiler) {
	return Type::getInt1Ty(*compiler->llvmContext);
}
