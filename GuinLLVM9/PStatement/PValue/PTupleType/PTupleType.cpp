//
//  PTupleType.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#include "PTupleType.hpp"
#include "ConstantTupleType.hpp"
#include "ConstantTypeType.hpp"

Value* PTupleType::getLLVMValue(Compiler* compiler) {
	StructType* type = StructType::get(*compiler->llvmContext, { });
	return ConstantStruct::get(type, { });
}

ConstantValue* PTupleType::getConstantValue(Compiler* compiler) {
	std::vector<ConstantTupleTypeElement> constantElements = {};
	for (const PTupleTypeElement& element : elements) {
		ConstantValue* typeValue = element.type->getConstantValue(compiler);
		if (!typeValue) return nullptr;
		ConstantType* type = dynamic_cast<ConstantType*>(typeValue);
		if (!type) return nullptr;
		constantElements.push_back({ element.label, type });
	}
	return new ConstantTupleType(constantElements);
}

ConstantType* PTupleType::getConstantType(Compiler* compiler) {
	return new ConstantTypeType();
}

PVariance PTupleType::getVariance(Compiler* compiler) {
	for (PTupleTypeElement element : elements) {
		if (element.type->getVariance(compiler) != PVariance::CONST) {
			return PVariance::LET;
		}
	}
	return PVariance::CONST;
}
