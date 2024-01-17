//
//  PTupleElementAccess.hpp
//  GuinLLVM9
//
//  Created by Jason Turner on 1/16/24.
//

#ifndef PTupleElementAccess_hpp
#define PTupleElementAccess_hpp

#include "PValue.hpp"

class PTupleElementAccess: public PValue {
	
public:
	
	PValue* tuple;
	std::string label;
	
	PTupleElementAccess(PValue* tuple, std::string label): tuple(tuple), label(label) { }
	
	Value* asLLVMValue(Compiler* compiler) override;
	
	CValue* asConstantValue(Compiler* compiler) override;
	CType* getConstantType(Compiler* compiler) override;
	
	PVariance getVariance(Compiler* compiler) override;
	
	Value* getMemoryLocation(Compiler* compiler) override;
	
	int indexOfLabel(Compiler* compiler) const;
	
};

#endif /* PTupleElementAccess_hpp */
