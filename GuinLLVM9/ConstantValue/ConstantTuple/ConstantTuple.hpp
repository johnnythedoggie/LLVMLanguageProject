//
//  ConstantTuple.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#ifndef ConstantTuple_hpp
#define ConstantTuple_hpp

#include "ConstantValue.hpp"
#include "ConstantType.hpp"
#include "ConstantTupleType.hpp"

struct ConstantTupleElement {
	std::string label;
	ConstantValue* value;
};

class ConstantTuple: public ConstantValue {
	
public:
	
	std::vector<ConstantTupleElement> elements;
	
	ConstantTuple(std::vector<ConstantTupleElement> elements) : elements(elements) { }
	
	std::string identifierString() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
	ConstantType* getConstantType() override;
	
};

#endif /* ConstantTuple_hpp */
