//
//  Parser.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef Parser_h
#define Parser_h

#include "Tokenizer.h"
#include "GStatement.h"
#include <optional>
#include <string>

#include "GBool.h"
#include "GBuiltInType.h"

class Parser {
	
public:
	
	std::map<std::string, GValue*> identifierToGValueMap = {};
	
	Parser() {
		
		const Variance constant = Variance::Const;
		
		identifierToGValueMap["true"] = new GBool(true, constant);
		identifierToGValueMap["false"] = new GBool(false, constant);
		identifierToGValueMap["Bool"] = new GBuiltInType(GBuiltInType::BuiltIn::Bool, constant);
		identifierToGValueMap["Int"] = new GBuiltInType(GBuiltInType::BuiltIn::Int, constant);
		identifierToGValueMap["Type"] = new GBuiltInType(GBuiltInType::BuiltIn::Type, constant);
		identifierToGValueMap["Void"] = new GBuiltInType(GBuiltInType::BuiltIn::Void, constant);
		identifierToGValueMap["Never"] = new GBuiltInType(GBuiltInType::BuiltIn::Never, constant);
	}
	
	std::queue<GStatement*> getStatementsFrom(std::queue<Token> tokens);
	
};


#endif /* Parser_h */
