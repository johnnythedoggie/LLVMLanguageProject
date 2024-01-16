//
//  ConstantTuple.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#include "ConstantTuple.hpp"

std::string ConstantTuple::identifierString() {
	std::string str = "( ";
	for (ConstantTupleElement element : elements) {
		str += element.label;
		str += " = ";
		str += element.value->identifierString();
		str += ", ";
	}
	str += ")";
	return str;
}

Value* ConstantTuple::getLLVMValue(Compiler* compiler) {
	std::vector<Type*> llvmTypes = {};
	for (ConstantTupleElement element : elements) {
		Type* llvmType = element.value->getConstantType()->getLLVMType(compiler);
		llvmTypes.push_back(llvmType);
	}
	StructType* structType = StructType::get(*compiler->llvmContext, llvmTypes);
	Value* struture = ConstantStruct::get(structType, {});
	for (int i = 0; i < elements.size(); i += 1) {
		Value* llvmValue = elements[i].value->getLLVMValue(compiler);
		struture = compiler->llvmBuilder->CreateInsertValue(struture, llvmValue, i);
	}
	return struture;
}

ConstantType* ConstantTuple::getConstantType() {
	std::vector<ConstantTupleTypeElement> typeElements;
	for (ConstantTupleElement element : elements) {
		ConstantType* elementType = element.value->getConstantType();
		if (!elementType) return nullptr;
		typeElements.push_back({ element.label, elementType });
	}
	return new ConstantTupleType(typeElements);
}
