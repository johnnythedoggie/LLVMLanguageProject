//
//  PTuple.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#include "PTuple.hpp"
#include "CTuple.hpp"

Value* PTuple::asLLVMValue(Compiler* compiler) {
	std::vector<Type*> llvmTypes = {};
	for (const PTupleElement& element : elements) {
		Type* llvmType = element.value->getLLVMType(compiler);
		llvmTypes.push_back(llvmType);
	}
	StructType* structType = StructType::get(*compiler->llvmContext, llvmTypes);
	Value* struture = ConstantStruct::get(structType, {});
	for (int i = 0; i < elements.size(); i += 1) {
		Value* llvmValue = elements[i].value->asLLVMValue(compiler);
		struture = compiler->llvmBuilder->CreateInsertValue(struture, llvmValue, i);
	}
	return struture;
}

CValue* PTuple::asConstantValue(Compiler* compiler) {
	std::vector<CTupleElement> constantElements = {};
	for (const PTupleElement& element : elements) {
		CValue* value = element.value->asConstantValue(compiler);
		if (!value) return nullptr;
		constantElements.push_back({element.label, value});
	}
	return new CTuple(constantElements);
}

CType* PTuple::getConstantType(Compiler* compiler) {
	std::vector<CTupleTypeElement> constantElements = {};
	for (const PTupleElement& element : elements) {
		CType* type = element.value->getConstantType(compiler);
		constantElements.push_back({element.label, type});
	}
	return new CTupleType(constantElements);
}

PVariance PTuple::getVariance(Compiler* compiler) {
	for (PTupleElement element : elements) {
		if (element.value->getVariance(compiler) != PVariance::CONST) {
			return PVariance::LET;
		}
	}
	return PVariance::CONST;
}
