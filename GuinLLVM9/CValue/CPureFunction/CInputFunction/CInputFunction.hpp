//
//  CInputFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef CInputFunction_hpp
#define CInputFunction_hpp

#include "CPureFunction.hpp"
#include "CTupleType.hpp"
#include "CIntType.hpp"

class CInputFunction: public CPureFunction {
	
public:
	
	Value* scanfFormat = nullptr;
	
	CInputFunction()
	: CPureFunction(new CTupleType({}), new CIntType()) { }
	
	void makeFunction(Compiler* compiler) override;
	
	void makeBody(Compiler* compiler, Value* argument) override;
	
};

#endif /* CInputFunction_hpp */
