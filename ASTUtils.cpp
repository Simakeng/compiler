#include "ASTUtils.h"

using namespace Compiler::Parser;

namespace Compiler::AST
{
	void StripEmptyNode(ASTNode* ast)
	{

		bool all_empty = true;

		for (auto& subnode : ast->tokenList)
		{
			if (subnode->type != TokenType::Empty
				&&
				subnode->tokenList.size() != 0)
				StripEmptyNode(subnode);

			if (subnode->type != TokenType::Empty)
				all_empty = false;
		}

		if (all_empty)
		{
			for (auto& subnode : ast->tokenList)
				FreeNode(subnode);
			auto _ = std::deque<ASTNode*>();
			std::swap(_, ast->tokenList);
			ast->type = TokenType::Empty;
		}
		else
		{
			for (auto it = ast->tokenList.begin(); it != ast->tokenList.end();)
			{
				if ((*it)->type == TokenType::Empty)
				{
					FreeNode((*it));
					it = ast->tokenList.erase(it);
				}
				else
					++it;
			}
		}
	}
	void __StripExprNode(ASTNode* ast)
	{
		for (auto& subnode : ast->tokenList)
			if (subnode->tokenList.size() != 0)
				__StripExprNode(subnode);

		//if (ast->tokenList.size() == 1 && ast->tokenList.front()->tokenList.size() == 0)
		if (ast->tokenList.size() == 1)
		{
			auto child = ast->tokenList.front();
			ast->type = child->type;
			ast->value = child->value;
			auto _ = decltype(ast->tokenList)();
			std::swap(ast->tokenList, child->tokenList);
			std::swap(child->tokenList, _);
			FreeNode(child);
		}
	}
	void StripExprNode(ASTNode* ast)
	{
		if (ast->type == TokenType::ConstExp || ast->type == TokenType::Exp || ast->type == TokenType::Cond)
		{
			for (auto& subnode : ast->tokenList)
				__StripExprNode(subnode);
		}
		else for (auto& subnode : ast->tokenList)
		{
			StripExprNode(subnode);
		}
	}
	void __SearchGlobalFunctions(ASTNode* ast, std::deque<ASTNode*>* result)
	{
		if (ast->type == TokenType::FuncDeclBody)
			result->push_back(ast->parent);
		for (auto& sub : ast->tokenList)
			__SearchGlobalFunctions(sub, result);
	}

	std::deque<ASTNode*> SearchGlobalFunctions(ASTNode* ast)
	{
		auto result = std::deque<ASTNode*>();
		__SearchGlobalFunctions(ast, &result);
		return result;
	}
}
