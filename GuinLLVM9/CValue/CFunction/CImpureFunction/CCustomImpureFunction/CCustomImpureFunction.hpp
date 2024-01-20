//
//  CCustomImpureFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#ifndef CCustomImpureFunction_hpp
#define CCustomImpureFunction_hpp

#include "CImpureFunction.hpp"
#include "PValue.hpp"
#include <queue>

class CCustomImpureFunction: public CImpureFunction {
	
public:
	
	std::queue<PStatement*> statements;
	
	CCustomImpureFunction(
		std::queue<PStatement*> statements,
		CType* inputType,
		CType* outputType
	): statements(statements), CImpureFunction(inputType, outputType) { }
	
	void makeBody(Compiler* compiler) override;
	
};

#endif /* CCustomImpureFunction_hpp */
