//
//  ConstantValue.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef ConstantValue_hpp
#define ConstantValue_hpp

#include "Compiler.hpp"
#include <string>

class ConstantType;

class ConstantValue {
	
public:
	
	virtual std::string identifierString() = 0;
	
	virtual ConstantType* getConstantType() = 0;
	virtual Value* getLLVMValue(Compiler* compiler) = 0;
	
};

#endif /* ConstantValue_hpp */
