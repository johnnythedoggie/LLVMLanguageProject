//
//  GDeclaration.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef GDeclaration_h
#define GDeclaration_h

#include "GStatement.h"
#include "GValue.h"

class GDeclaration: public GStatement {
	
	std::string identifier;
	GValue* type;
	GValue* value;
	
public:
	
	GDeclaration(std::string id, GValue* type, GValue* value) : identifier(id), type(type), value(value) { }
	
	static GDeclaration* fromTokens(std::queue<Token>& tokens, std::map<std::string, GValue*>& identifierToGValueMap);
	
	std::string description() const override;
	
	Value* generateIR(IRGenerator* generator) const override;
	
	~GDeclaration() override {
		delete type;
		delete value;
	}
	
};

#endif /* GDeclaration_h */
