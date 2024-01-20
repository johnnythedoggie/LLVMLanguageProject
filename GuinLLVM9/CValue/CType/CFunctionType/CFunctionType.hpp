//
//  CFunctionType.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/18/24.
//

#ifndef CFunctionType_hpp
#define CFunctionType_hpp

#include "CType.hpp"

class CFunctionType: public CType {
	
public:
	
	bool isPure;
	CType* inputType;
	CType* outputType;
	
	CFunctionType(bool isPure, CType* inputType, CType* outputType)
	: isPure(isPure), inputType(inputType), outputType(outputType) { }
	
};

#endif /* CFunctionType_hpp */
