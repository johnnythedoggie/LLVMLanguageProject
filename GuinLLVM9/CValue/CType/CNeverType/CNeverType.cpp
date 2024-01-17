//
//  CNeverType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "CNeverType.hpp"

std::string CNeverType::identifierString() {
	return "Never";
}

Type* CNeverType::asLLVMType(Compiler* compiler) {
	return StructType::get(*compiler->llvmContext, { });
}
