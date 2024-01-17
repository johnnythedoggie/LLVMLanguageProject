//
//  ConstantTypeType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "ConstantTypeType.hpp"

std::string ConstantTypeType::identifierString() {
	return "Type";
}

Type* ConstantTypeType::asLLVMType(Compiler* compiler) {
	StructType* type = StructType::get(*compiler->llvmContext, { });
	return type;
}
