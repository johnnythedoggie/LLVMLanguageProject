//
//  PReturn.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef PReturn_hpp
#define PReturn_hpp

#include "PValue.hpp"
#include "ConstantNeverType.hpp"

/*
 
 how to get return to be a function
 
 
 If i change the llvm::Type that a ConstantFunctionType gives, maybe i could store both.
 { is return flag, normal function pointer,  }
 
 I would have to make a function "call" that takes in that monstrocity
 
 */

class PReturn: public PStatement {
	
public:
	
	PValue* value;
	
	PReturn(PValue* value) : value(value) { }
	
	void compile(Compiler* compiler) override;
	
};

#endif /* ConstantReturnFunction_hpp */
