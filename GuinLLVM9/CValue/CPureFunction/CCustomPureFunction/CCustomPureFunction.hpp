//
//  CCustomPureFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/12/24.
//

#ifndef CCustomPureFunction_hpp
#define CCustomPureFunction_hpp

#include "CPureFunction.hpp"
#include "PValue.hpp"
#include <queue>

class CCustomPureFunction: public CPureFunction {
	
public:
	
	std::queue<PStatement*> statements;
	
	CCustomPureFunction(
		std::queue<PStatement*> statements,
		CType* inputType,
		CType* outputType
	): statements(statements), CPureFunction(inputType, outputType) { }
	
	void makeBody(Compiler* compiler, Value* argument) override;
	
};

#endif /* CCustomPureFunction_hpp */
