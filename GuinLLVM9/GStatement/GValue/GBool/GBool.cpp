//
//  GBool.cpp
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#include "GBool.h"
#include "GBuiltInType.h"
#include "IRGenerator.h"

Value* GBool::generateIR(IRGenerator* generator) const {
	IntegerType* intType = Type::getInt1Ty(*generator->llvmContext);
	Value* irValue = ConstantInt::get(intType, value);
	return irValue;
}

GType* GBool::typeOf() const {
	return new GBuiltInType(GBuiltInType::BuiltIn::Bool, Variance::Const);
}
