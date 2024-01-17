//
//  ConstantTupleType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#include "ConstantTupleType.hpp"


std::string ConstantTupleType::identifierString() {
	std::string str = "( ";
	for (ConstantTupleTypeElement element : elements) {
		str += element.label;
		str += ": ";
		str += element.type->identifierString();
		str += ", ";
	}
	str += ")";
	return str;
}

Type* ConstantTupleType::asLLVMType(Compiler* compiler) {
	std::vector<Type*> llvmTypes = {};
	for (const ConstantTupleTypeElement& element : elements) {
		Type* llvmType = element.type->asLLVMType(compiler);
		llvmTypes.push_back(llvmType);
	}
	StructType* structType = StructType::get(*compiler->llvmContext, llvmTypes);
	return structType;
}
