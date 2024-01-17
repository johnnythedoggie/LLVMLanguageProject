//
//  PTupleElementAccess.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#include "PTupleElementAccess.hpp"
#include "ConstantTupleType.hpp"
#include "ConstantTuple.hpp"

int PTupleElementAccess::indexOfLabel(Compiler* compiler) const {
	ConstantType* type = tuple->getConstantType(compiler);
	ConstantTupleType* tupleType = dynamic_cast<ConstantTupleType*>(type);
	std::string errorMessage = "Invalid use of tuple element access.";
	if (!tupleType) throw errorMessage;
	int index = -1;
	for (int i = 0; i < tupleType->elements.size(); i += 1) {
		if (tupleType->elements[i].label == label) {
			if (index != -1) throw errorMessage;
			index = i;
		}
	}
	if (index == -1) throw errorMessage;
	return index;
}

Value* PTupleElementAccess::asLLVMValue(Compiler* compiler) {
	int index = indexOfLabel(compiler);
	Value* tupleValue = tuple->asLLVMValue(compiler);
	return compiler->llvmBuilder->CreateExtractValue(tupleValue, index);
}

ConstantValue* PTupleElementAccess::asConstantValue(Compiler* compiler) {
	ConstantValue* constantValue = tuple->asConstantValue(compiler);
	if (!constantValue) return nullptr;
	ConstantTuple* constantTuple = dynamic_cast<ConstantTuple*>(constantValue);
	std::string errorMessage = "Invalid use of tuple element access.";
	if (!constantTuple) throw errorMessage;
	int index = indexOfLabel(compiler);
	return constantTuple->elements[index].value;
}

ConstantType* PTupleElementAccess::getConstantType(Compiler* compiler) {
	ConstantType* type = tuple->getConstantType(compiler);
	ConstantTupleType* tupleType = dynamic_cast<ConstantTupleType*>(type);
	std::string errorMessage = "Invalid use of tuple element access.";
	if (!tupleType) throw errorMessage;
	int index = indexOfLabel(compiler);
	return tupleType->elements[index].type;
}

PVariance PTupleElementAccess::getVariance(Compiler* compiler) {
	return tuple->getVariance(compiler);
}

Value* PTupleElementAccess::getMemoryLocation(Compiler* compiler) {
	if (tuple->getVariance(compiler) != PVariance::VAR) return nullptr;
	Value* zero = ConstantInt::get(compiler->llvmBuilder->getInt32Ty(), 0);
	Value* index = ConstantInt::get(compiler->llvmBuilder->getInt32Ty(), indexOfLabel(compiler));
	return compiler->llvmBuilder->CreateGEP(tuple->getMemoryLocation(compiler), { zero, index });
}
