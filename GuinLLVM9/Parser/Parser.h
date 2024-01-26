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
#include "PFunctionDefinition.hpp"
#include "PArgument.hpp"
#include "PReturn.hpp"
#include "PTuple.hpp"
#include "PTupleType.hpp"
#include "PTupleElementAccess.hpp"
#include "PSelect.hpp"

/**
 
 This is a temporary Parser for Guin.  It takes a queue of tokens as an input and parses them into a queue of PStatements.
 
 The end goal is to have a parser that can handle a more generic grammar that is then given the Guin grammer as input.
 
 */
class Parser {
	
	std::queue<Token> tokens;
	
	/// Removes excess newlines, ensures tokens ends with a newline
	void formatTokens();
	
	/// Checks if `tokens` is at the end of a line
	bool atEndOfLine() const;
	
	// These parse a specific pattern
	PReturn* parseReturn();
	PArgument* parseArgument();
	PStatement* parseStatement();
	PDeclaration* parseDeclaration();
	PValue* parseProtectedValue();
	PValue* parseValue();
	PValue* parseParenedValue();
	PInt* parseInt();
	PIdentifier* parseIdentifier();
	PFunctionType* parseFunctionType();
	PSelect* parseSelect();
	PFunctionDefinition* parseFunctionLiteral();
	
	// Continuations are additonal tokens that may follow a value
	// Such as an assignment, where the '=' token signals a continuation
	PStatement* parseOptionalAssignmentContinuation(PValue* value);
	PFunctionCall* parseOptionalFunctionCallContinuation(PValue* value);
	
	/// Temporary value storage for parsing tuples
	struct TElement {
		bool hasIdentifier;
		std::string identifier;
		bool isType;
		PValue* value;
	};
	
	/// Parse a TElement
	TElement* parseTElement();
	
public:
	
	Parser(const std::queue<Token>& tokens) : tokens(tokens) { }
	
	/// Returns the tokens parsed as statements.
	std::queue<PStatement*> parse();
	
};


#endif /* Parser_h */
