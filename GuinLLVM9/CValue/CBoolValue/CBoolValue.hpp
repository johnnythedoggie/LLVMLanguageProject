//
//  CBoolValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CBoolValue_hpp
#define CBoolValue_hpp

#include "CValue.hpp"

class CBoolValue: public CValue {
	
public:
	
	bool value;
	
	CBoolValue(bool value) : value(value) { }
	
	CType* getConstantType() override;
	
	std::string identifierString() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* CBoolValue_hpp */
