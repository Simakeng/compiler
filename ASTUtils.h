#pragma once
#include "Parser.h"
namespace Compiler::AST 
{
	using ASTNode = Parser::ASTNode;


	void StripEmptyNode(ASTNode* ast);

	void StripExprNode(ASTNode* ast);
}