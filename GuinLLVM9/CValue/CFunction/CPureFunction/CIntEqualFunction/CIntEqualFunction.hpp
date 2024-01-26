//
//  CIntEqualFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#ifndef CIntEqualFunction_hpp
#define CIntEqualFunction_hpp

#include "CPureFunction.hpp"
#include "CIntType.hpp"
#include "CTupleType.hpp"
#include "CBoolType.hpp"

class CIntEqualFunction: public CPureFunction {
	
public:
	
	CIntEqualFunction()
	: CPureFunction(new CTupleType({
		{ "a", new CIntType() },
		{ "b", new CIntType() }
	}), new CBoolType()) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* CIntEqualFunction_hpp */
