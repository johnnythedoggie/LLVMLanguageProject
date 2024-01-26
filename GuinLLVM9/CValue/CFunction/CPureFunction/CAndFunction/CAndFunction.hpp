//
//  CAndFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#ifndef CAndFunction_hpp
#define CAndFunction_hpp

#include "CPureFunction.hpp"
#include "CBoolType.hpp"
#include "CTupleType.hpp"

class CAndFunction: public CPureFunction {
	
public:
	
	CAndFunction()
	: CPureFunction(new CTupleType({
		{ "a", new CBoolType() },
		{ "b", new CBoolType() }
	}), new CBoolType()) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* CAndFunction_hpp */
