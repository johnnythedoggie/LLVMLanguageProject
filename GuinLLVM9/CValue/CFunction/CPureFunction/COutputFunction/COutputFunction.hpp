//
//  COutputFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef COutputFunction_hpp
#define COutputFunction_hpp

#include "CPureFunction.hpp"
#include "CTupleType.hpp"
#include "CIntType.hpp"

class COutputFunction: public CPureFunction {
	
public:
	
	COutputFunction()
	: CPureFunction(new CIntType(), new CTupleType({})) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* COutputFunction_hpp */
