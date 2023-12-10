//
//  GTypeType.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GTypeType_h
#define GTypeType_h

#include "GType.h"

class GBuiltInType: public GType {
	
public:
	
	enum class BuiltIn {
		Type, Int, Bool
	};
	
	
	BuiltIn builtInType;
	
	std::string description() const override {
		switch (builtInType) {
			case BuiltIn::Type:
				return "Type";
			case BuiltIn::Int:
				return "Int";
			case BuiltIn::Bool:
				return "Bool";
		}
	}
	
	GBuiltInType(BuiltIn builtIn, Variance variance) : builtInType(builtIn), GType(variance) { }
	
	~GBuiltInType() override = default;
	
};

#endif /* GTypeType_h */
