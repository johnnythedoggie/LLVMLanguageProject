//
//  CIntType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#include "CIntType.hpp"

std::string CIntType::identifierString() {
	return "Int";
}

Type* CIntType::asLLVMType(Compiler* compiler) {
	return Type::getInt32Ty(*compiler->llvmContext);
}

