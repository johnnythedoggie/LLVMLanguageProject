//
//  GBool.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GBool_h
#define GBool_h

#include "GValue.h"

class GBool: public GValue {
	
public:
	
	bool value;
	
	GBool(bool value, Variance variance) : GValue(variance), value(value) { }
	
	std::string description() const override {
		return value ? "true" : "false";
	}
	
	Value* generateIR(IRGenerator* generator) const override;
	
	GType* typeOf() const override;
	
	~GBool() override = default;
	
};

#endif /* GBool_h */
