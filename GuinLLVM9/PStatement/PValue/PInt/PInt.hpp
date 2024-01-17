//
//  PInt.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef PInt_hpp
#define PInt_hpp

#include "PValue.hpp"

class PInt: public PValue {
	
public:
	
	int value;
	
	PInt(int value) : value(value) { }
	
	Value* asLLVMValue(Compiler* compiler) override;
	
	CValue* asConstantValue(Compiler* compiler) override;
	CType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PInt_hpp */
