//
//  PTupleType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#ifndef PTupleType_hpp
#define PTupleType_hpp

#include "PValue.hpp"

struct PTupleTypeElement {
	std::string label;
	PValue* type;
	
	PTupleTypeElement(std::string label, PValue* type): label(label), type(type) { }
};

class PTupleType: public PValue {
	
public:
	
	std::vector<PTupleTypeElement> elements;
	
	PTupleType(std::vector<PTupleTypeElement> elements): elements(elements) { }
	
	
	Value* getLLVMValue(Compiler* compiler) override;
	
	ConstantValue* getConstantValue(Compiler* compiler) override;
	ConstantType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
	
};

#endif /* PTupleType_hpp */
