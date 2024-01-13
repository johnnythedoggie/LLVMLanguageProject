//
//  ConstantNeverType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#include "ConstantNeverType.hpp"
#include "ConstantVoidType.hpp"

std::string ConstantNeverType::identifierString() {
	return "Never";
}

Type* ConstantNeverType::getLLVMType(Compiler* compiler) {
	// Never is the same as Void in LLVM IR
	return ConstantVoidType().getLLVMType(compiler);
}
