//
//  CDifferenceFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#ifndef CDifferenceFunction_hpp
#define CDifferenceFunction_hpp

#include "CPureFunction.hpp"
#include "CIntType.hpp"
#include "CTupleType.hpp"

class CDifferenceFunction: public CPureFunction {
	
public:
	
	CDifferenceFunction()
	: CPureFunction(new CTupleType({
		{ "a", new CIntType() },
		{ "b", new CIntType() }
	}), new CIntType()) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* CDifferenceFunction_hpp */
