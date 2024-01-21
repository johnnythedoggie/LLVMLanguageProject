//
//  PSelect.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/21/24.
//

#ifndef PSelect_hpp
#define PSelect_hpp

#include "PValue.hpp"

class PSelect: public PValue {
	
public:
	
	PValue* condition;
	PValue* caseTrue;
	PValue* caseFalse;
	
	PSelect(PValue* condition, PValue* caseTrue, PValue* caseFalse)
	: condition(condition), caseTrue(caseTrue), caseFalse(caseFalse) { }
	
	Value* asLLVMValue(Compiler* compiler) override;
	
	CValue* asConstantValue(Compiler* compiler) override;
	CType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PSelect_hpp */
