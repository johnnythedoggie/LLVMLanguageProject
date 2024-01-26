//
//  CTuple.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#include "CTuple.hpp"

std::string CTuple::id() {
	std::string str = "( ";
	for (CTupleElement element : elements) {
		str += element.label;
		str += " = ";
		str += element.value->id();
		str += ", ";
	}
	str += ")";
	return str;
}

Value* CTuple::getLLVMValue(Compiler* compiler) {
	std::vector<Type*> llvmTypes = {};
	for (CTupleElement element : elements) {
		Type* llvmType = element.value->getConstantType()->asLLVMType(compiler);
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

CType* CTuple::getConstantType() {
	std::vector<CTupleTypeElement> typeElements;
	for (CTupleElement element : elements) {
		CType* elementType = element.value->getConstantType();
		if (!elementType) return nullptr;
		typeElements.push_back({ element.label, elementType });
	}
	return new CTupleType(typeElements);
}
