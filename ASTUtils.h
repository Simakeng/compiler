#pragma once
#include "Parser.h"
#include <deque>
namespace Compiler::AST 
{
	using ASTNode = Parser::ASTNode;


	void StripEmptyNode(ASTNode* ast);

	void StripExprNode(ASTNode* ast);

	std::deque<ASTNode*> SearchGlobalVariables(ASTNode* ast);

	std::deque<ASTNode*> SearchGlobalConstants(ASTNode* ast);

	std::deque<ASTNode*> SearchGlobalFunctions(ASTNode* ast);

	std::deque<ASTNode*> SearchLocalVariables(ASTNode* ast);

	std::deque<ASTNode*> SearchLocalConstants(ASTNode* ast);

	std::deque<ASTNode*> SearchLocalStmts(ASTNode* ast);


}