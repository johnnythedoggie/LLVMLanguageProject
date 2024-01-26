//
//  CFunction.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/17/24.
//

#ifndef CFunction_hpp
#define CFunction_hpp


#include "CValue.hpp"
#include "CType.hpp"

class CFunction: public CValue {
	
public:
	
	virtual void makeBody(Compiler* compiler) = 0;
	
	Function* function = nullptr;
	
	static int globalIdentifier;
	
	int identifier;
	
	CType* inputType;
	CType* outputType;
	
	CFunction(CType* inputType, CType* outputType)
	: identifier(globalIdentifier++), inputType(inputType), outputType(outputType) { }
	
	std::string id() override;
	
	virtual void makeFunction(Compiler* compiler) = 0;
	
};

#endif /* CFunction_hpp */
