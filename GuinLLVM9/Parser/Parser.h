//
//  Parser.h
//  GuinLLVM9
//
//  Created by Jason Turner on 12/9/23.
//

#ifndef Parser_h
#define Parser_h

#include "Tokenizer.h"
#include <string>
#include <queue>

#include "PStatement.hpp"
#include "PDeclaration.hpp"
#include "PValue.hpp"
#include "PInt.hpp"
#include "PIdentifier.hpp"
#include "PAssignment.hpp"
#include "PFunctionType.hpp"
#include "PFunctionCall.hpp"

class Parser {
	
	void formatTokens(std::queue<Token>& tokens) const;
	
	PStatement* parseStatement(std::queue<Token>& tokens);
	PDeclaration* parseDeclaration(std::queue<Token>& tokens);
	PValue* parseProtectedValue(std::queue<Token>& tokens);
	PValue* parseValue(std::queue<Token>& tokens);
	PValue* parseParenedValue(std::queue<Token>& tokens);
	PInt* parseInt(std::queue<Token>& tokens);
	PIdentifier* parseIdentifier(std::queue<Token>& tokens);
	
	PFunctionType* parseOptionalFunctionTypeContinuation(PValue* value, std::queue<Token>& tokens);
	PStatement* parseOptionalAssignmentContinuation(PValue* value, std::queue<Token>& tokens);
	PFunctionCall* parseOptionalFunctionCallContinuation(PValue* value, std::queue<Token>& tokens);
	
	bool atEndOfLine(const std::queue<Token>& tokens) const;
	
public:
	
	std::map<std::string, PValue*> constIdentifierAlias = {};
	
	std::queue<PStatement*> parse(std::queue<Token>& tokens);
	
};


#endif /* Parser_h */
