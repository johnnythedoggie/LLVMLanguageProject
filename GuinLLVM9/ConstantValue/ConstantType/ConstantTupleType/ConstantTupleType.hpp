//
//  ConstantTupleType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#ifndef ConstantTupleType_hpp
#define ConstantTupleType_hpp

#include "ConstantType.hpp"

struct ConstantTupleTypeElement {
	std::string label;
	ConstantType* type;
};

class ConstantTupleType: public ConstantType {
	
public:
	
	std::vector<ConstantTupleTypeElement> elements;
	
	ConstantTupleType(std::vector<ConstantTupleTypeElement> elements) : elements(elements) { }
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
};

#endif /* ConstantTupleType_hpp */
