//
//  CSumFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/25/24.
//

#ifndef CSumFunction_hpp
#define CSumFunction_hpp

#include "CPureFunction.hpp"
#include "CIntType.hpp"
#include "CTupleType.hpp"

class CSumFunction: public CPureFunction {
	
public:
	
	CSumFunction()
	: CPureFunction(new CTupleType({
		{ "a", new CIntType() },
		{ "b", new CIntType() }
	}), new CIntType()) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* CSumFunction_hpp */
