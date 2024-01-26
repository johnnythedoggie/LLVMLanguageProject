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
		assert(element.hasLabel);
		constantElements.push_back(CTupleElement(element.label, value));
	}
	return new CTuple(constantElements);
}

CType* PTuple::getConstantType(Compiler* compiler) {
	std::vector<CTupleTypeElement> constantElements = {};
	for (const PTupleElement& element : elements) {
		CType* type = element.value->getConstantType(compiler);
		assert(element.hasLabel);
		constantElements.push_back(CTupleTypeElement(element.label, type));
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

void PTuple::expectedType(CType* type) {
	CTupleType* tupleType = dynamic_cast<CTupleType*>(type);
	assert(tupleType && "Incorrect use of tuple type.");
	assert(elements.size() == tupleType->elements.size());
	for (int i = 0; i < elements.size(); i += 1) {
		elements[i].value->expectedType(tupleType->elements[i].type);
		if (elements[i].hasLabel) {
			assert(elements[i].label == tupleType->elements[i].label);
		} else {
			elements[i].hasLabel = true;
			elements[i].label = tupleType->elements[i].label;
		}
	}
}
