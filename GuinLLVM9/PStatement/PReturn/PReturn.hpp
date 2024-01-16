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
 
 The vision is for a return to behave like a function call, not a statement
 
 It's too much work, leave it as a statement
 
 Of course this isn't how LLVM IR works, so the value I pass around for a function would have to have a flag indicating if it is a return or not.  If not, it would just have a function pointer as normal.  If so, I'm not sure... how could it remember what function is to return from?  And then how would it return from it?
  
 let outer = Void -> Int {
	var variable = return   # this is outer's return
	let inner = Void -> Int {
		variable = return   # now it's inner's return
		return 5
	}
	variable 5   # how does this return from inner?
 }
 
 */

class PReturn: public PStatement {
	
public:
	
	PValue* value;
	
	PReturn(PValue* value) : value(value) { }
	
	void compile(Compiler* compiler) override;
	
};

#endif /* ConstantReturnFunction_hpp */
