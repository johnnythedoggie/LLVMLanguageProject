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

Type* ConstantTypeType::getLLVMType(Compiler* compiler) {
	return nullptr;
}
