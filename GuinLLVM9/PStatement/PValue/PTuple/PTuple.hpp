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
	std::string label;
	PValue* value;
	
	PTupleElement(std::string label, PValue* value): label(label), value(value) { }
};

class PTuple: public PValue {
	
public:
	
	std::vector<PTupleElement> elements;
	
	PTuple(std::vector<PTupleElement> elements): elements(elements) { }
	
	Value* getLLVMValue(Compiler* compiler) override;
	
	ConstantValue* getConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
};

#endif /* PTuple_hpp */
