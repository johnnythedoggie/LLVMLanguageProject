//
//  GInt.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GInt_h
#define GInt_h

#include "GValue.h"

class GInt: public GValue {
	
public:
	
	int64_t value;
	
	GInt(int64_t value, Variance variance) : GValue(variance), value(value) { }
	
	static GInt* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	std::string description() const override {
		return std::to_string(value);
	}
	
	virtual Value* generateIR(IRGenerator* generator) const override;
	
	GType* typeOf() const override;
	
	~GInt() override = default;
	
};

#endif /* GInt_h */
