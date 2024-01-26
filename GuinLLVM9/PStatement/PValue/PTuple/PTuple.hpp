//
//  PTuple.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#ifndef PTuple_hpp
#define PTuple_hpp

#include "PValue.hpp"

struct PTupleElement {
	
	bool hasLabel;
	std::string label;
	PValue* value;
	
	PTupleElement(bool hasLabel, std::string label, PValue* value)
	 : hasLabel(hasLabel), label(label), value(value) { }
};

class PTuple: public PValue {
	
public:
	
	std::vector<PTupleElement> elements;
	
	PTuple(std::vector<PTupleElement> elements): elements(elements) { }
	
	Value* asLLVMValue(Compiler* compiler) override;
	
	CValue* asConstantValue(Compiler* compiler) override;
	CType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
	void expectedType(CType* type) override;
	
};

#endif /* PTuple_hpp */
