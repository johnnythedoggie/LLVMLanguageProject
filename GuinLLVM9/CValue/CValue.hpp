//
//  CValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef CValue_hpp
#define CValue_hpp

#include "Compiler.hpp"
#include <string>

class CType;

class CValue {
	
public:
	
	virtual std::string id() = 0;
	
	virtual CType* getConstantType() = 0;
	virtual Value* getLLVMValue(Compiler* compiler) = 0;
	
};

#endif /* CValue_hpp */
