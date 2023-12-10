//
//  GType.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GType_h
#define GType_h

#include "GValue.h"

class GType: public GValue {
	
public:
	
	static GType* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	GType* typeOf() const override;
	
	Value* generateIR(IRGenerator* generator) const override {
		return nullptr;
	}
	
	GType(Variance variance) : GValue(variance) { }
	
};

#endif /* GType_h */
