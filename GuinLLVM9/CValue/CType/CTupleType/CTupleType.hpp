//
//  CTupleType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/15/24.
//

#ifndef CTupleType_hpp
#define CTupleType_hpp

#include "CType.hpp"

struct CTupleTypeElement {
	std::string label;
	CType* type;
};

class CTupleType: public CType {
	
public:
	
	std::vector<CTupleTypeElement> elements;
	
	CTupleType(std::vector<CTupleTypeElement> elements) : elements(elements) { }
	
	std::string identifierString() override;
	
	Type* asLLVMType(Compiler* compiler) override;
	
};

#endif /* CTupleType_hpp */
