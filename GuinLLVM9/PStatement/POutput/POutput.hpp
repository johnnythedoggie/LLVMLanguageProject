//
//  POutput.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/10/24.
//

#ifndef POutput_hpp
#define POutput_hpp

#include "PStatement.hpp"
#include "PIdentifier.hpp"

class POutput: public PStatement {
	
	static Value* format;
	static Function* printf;
	
	void setup(Compiler* compiler);
	
public:
	
	PValue* argument;
	
	void compile(Compiler* compiler) override;
	
	POutput(PValue* argument) : argument(argument) { }
	
};

#endif /* POutput_hpp */
