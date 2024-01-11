//
//  Parser.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef Parser_h
#define Parser_h

#include "Tokenizer.h"
#include <optional>
#include <string>


#include "PStatement.hpp"
#include "PDeclaration.hpp"
#include "PValue.hpp"
#include "PInt.hpp"
#include "PIdentifier.hpp"

#include <queue>

class Parser {
	
	void formatTokens(std::queue<Token>& tokens) const;
	
	PStatement* parseStatement(std::queue<Token>& tokens);
	PDeclaration* parseDeclaration(std::queue<Token>& tokens);
	PValue* parseValue(std::queue<Token>& tokens);
	PValue* parseParenedValue(std::queue<Token>& tokens);
	PInt* parseInt(std::queue<Token>& tokens);
	PIdentifier* parseIdentifier(std::queue<Token>& tokens);
	
	bool atEndOfLine(const std::queue<Token>& tokens) const;
	
public:
	
	std::map<std::string, PValue*> constIdentifierAlias = {};
	
	std::queue<PStatement*> parse(std::queue<Token>& tokens);
	
};


#endif /* Parser_h */
