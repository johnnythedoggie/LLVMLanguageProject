//
//  PTupleElementAccess.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#include "PTupleElementAccess.hpp"
#include "CTupleType.hpp"
#include "CTuple.hpp"

int PTupleElementAccess::indexOfLabel(Compiler* compiler) const {
	CType* type = tuple->getConstantType(compiler);
	CTupleType* tupleType = dynamic_cast<CTupleType*>(type);
	assert(tupleType && "Element access is only valid on tuples.");
	int index = -1;
	for (int i = 0; i < tupleType->elements.size(); i += 1) {
		if (tupleType->elements[i].label == label) {
			assert(index == -1 && "Tuple cannot have repeated labels.");
			index = i;
		}
	}
	assert(index != -1 && "Tuple does not contain requested label.");
	return index;
}

Value* PTupleElementAccess::asLLVMValue(Compiler* compiler) {
	int index = indexOfLabel(compiler);
	Value* tupleValue = tuple->asLLVMValue(compiler);
	return compiler->llvmBuilder->CreateExtractValue(tupleValue, index);
}

CValue* PTupleElementAccess::asConstantValue(Compiler* compiler) {
	CValue* constantValue = tuple->asConstantValue(compiler);
	if (!constantValue) return nullptr;
	CTuple* constantTuple = dynamic_cast<CTuple*>(constantValue);
	assert(constantTuple && "Element access is only valid on tuples.");
	int index = indexOfLabel(compiler);
	return constantTuple->elements[index].value;
}

CType* PTupleElementAccess::getConstantType(Compiler* compiler) {
	CType* type = tuple->getConstantType(compiler);
	CTupleType* tupleType = dynamic_cast<CTupleType*>(type);
	assert(tupleType && "Element access is only valid on tuples.");
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
