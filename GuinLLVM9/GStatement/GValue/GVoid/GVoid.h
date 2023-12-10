//
//  GVoid.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/10/23.
//

#ifndef GVoid_h
#define GVoid_h

#include "GValue.h"

class GVoid: public GValue {
	
public:
	
	GVoid(Variance variance) : GValue(variance) { }
	
	std::string description() const override {
		return "()";
	}
	
	static GVoid* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	Value* generateIR(IRGenerator* generator) const override;
	
	GType* typeOf() const override;
	
	~GVoid() override = default;
	
};


#endif /* GVoid_h */
