//
//  CInt.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CInt_hpp
#define CInt_hpp

#include "CValue.hpp"

class CIntValue: public CValue {
	
public:
	
	int value;
	
	CIntValue(int value): value(value) { }
	
	CType* getConstantType() override;
	
	std::string id() override;
	
	Value* getLLVMValue(Compiler* compiler) override;
	
};

#endif /* CInt_hpp */
