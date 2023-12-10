//
//  GPureFunctionType.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/10/23.
//

#ifndef GPureFunctionType_h
#define GPureFunctionType_h

#include "GType.h"

class GPureFunctionType: public GType {
	
public:
	
	GValue* inputType;
	GValue* outputType;
	
	std::string description() const override {
		return "pure " + inputType->description() + " -> " + outputType->description();
	}
	
	static GPureFunctionType* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	GPureFunctionType(GValue* inputType, GValue* outputType, Variance variance) : inputType(inputType), outputType(outputType), GType(variance) { }
	
	~GPureFunctionType() override {
		delete inputType;
		delete outputType;
	};
	
};


#endif /* GPureFunctionType_h */
