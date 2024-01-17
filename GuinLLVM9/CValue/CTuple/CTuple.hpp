//
//  CTuple.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#ifndef CTuple_hpp
#define CTuple_hpp

#include "CValue.hpp"
#include "CType.hpp"
#include "CTupleType.hpp"

struct CTupleElement {
	std::string label;
	CValue* value;
};

class CTuple: public CValue {
	
public:
	
	std::vector<CTupleElement> elements;
	
	CTuple(std::vector<CTupleElement> elements) : elements(elements) { }
	
	std::string identifierString() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
	CType* getConstantType() override;
	
};

#endif /* CTuple_hpp */
