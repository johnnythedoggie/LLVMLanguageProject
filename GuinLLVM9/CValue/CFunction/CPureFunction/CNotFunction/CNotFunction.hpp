//
//  CNotFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#ifndef CNotFunction_hpp
#define CNotFunction_hpp

#include "CPureFunction.hpp"
#include "CBoolType.hpp"

class CNotFunction: public CPureFunction {
	
public:
	
	CNotFunction()
	: CPureFunction(new CBoolType(), new CBoolType()) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* CNotFunction_hpp */
