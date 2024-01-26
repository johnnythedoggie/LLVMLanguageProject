//
//  CTypeType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CTypeType.hpp"

std::string CTypeType::id() {
	return "Type";
}

Type* CTypeType::asLLVMType(Compiler* compiler) {
	StructType* type = StructType::get(*compiler->llvmContext, { });
	return type;
}
