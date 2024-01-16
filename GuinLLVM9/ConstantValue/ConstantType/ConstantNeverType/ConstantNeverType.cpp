//
//  ConstantNeverType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "ConstantNeverType.hpp"

std::string ConstantNeverType::identifierString() {
	return "Never";
}

Type* ConstantNeverType::getLLVMType(Compiler* compiler) {
	return StructType::get(*compiler->llvmContext, { });
}
