//
//  CTupleType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#include "CTupleType.hpp"


std::string CTupleType::identifierString() {
	std::string str = "( ";
	for (CTupleTypeElement element : elements) {
		str += element.label;
		str += ": ";
		str += element.type->identifierString();
		str += ", ";
	}
	str += ")";
	return str;
}

Type* CTupleType::asLLVMType(Compiler* compiler) {
	std::vector<Type*> llvmTypes = {};
	for (const CTupleTypeElement& element : elements) {
		Type* llvmType = element.type->asLLVMType(compiler);
		llvmTypes.push_back(llvmType);
	}
	StructType* structType = StructType::get(*compiler->llvmContext, llvmTypes);
	return structType;
}
