//
//  PAssignment.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/11/24.
//

#ifndef PAssignment_hpp
#define PAssignment_hpp

#include "PValue.hpp"

class PAssignment: public PStatement {
	
public:
	
	PValue* left;
	PValue* right;
	
	PAssignment(PValue* left, PValue* right)
		: left(left), right(right) { }
	
	void compile(Compiler* compiler) override;
	
};

#endif /* PAssignment_hpp */
