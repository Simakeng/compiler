#include "ASTUtils.h"
#include <string>
#include "Logger.h"
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

	void StripHumanReadable(ASTNode* ast)
	{
		for (auto& sub : ast->tokenList)
			StripHumanReadable(sub);

		for (auto it = ast->tokenList.begin(); it != ast->tokenList.end();)
		{
			auto type = (*it)->type;
			auto ptype = ast->type;
			if (type == TokenType::CompUnit ||
				type == TokenType::Stmts ||
				type == TokenType::VarOrFuncDeclBody ||
				(ptype == TokenType::ArraySizeDecl && type == TokenType::ArraySizeDecl) ||
				((*it)->tokenList.size() > 0 && type == TokenType::VarInitValue && (*it)->tokenList[0]->type == TokenType::ConstExp) ||
				strstr(__tstr(type), "Next") != nullptr)
			{
				auto ptr = (*it);
				it = ast->tokenList.erase(it);
				for (auto& sub : ptr->tokenList)
				{
					it = ast->tokenList.insert(it, sub);
					++it;
				}
				decltype(ast->tokenList) _;
				std::swap(_, ptr->tokenList);
				FreeNode(ptr);
			}
			else
				++it;
		}
	}

	IR::Decl::Type GetDeclType(ASTNode* ast)
	{
		if (ast->tokenList.front()->type == TokenType::ConstDecl)
			return IR::Decl::Type::Const;
		if (ast->tokenList.front()->type == TokenType::VarOrFuncDecl)
		{
			if (ast->tokenList.front()->tokenList.back()->type == TokenType::FuncDeclBody)
				return IR::Decl::Type::Function;
			else if (ast->tokenList.front()->tokenList.back()->type == TokenType::VarDeclbody)
				return IR::Decl::Type::Var;

		}
		Console::Log("Node not match when GetDeclType for node",
			__tstr(ast->type), Level::Warning);
		Console::SetExitCode(-2);
		return (IR::Decl::Type) - 2;
	}

	std::deque<ASTNode*> SearchNodeDecls(ASTNode* ast)
	{
		auto result = std::deque<ASTNode*>();
		for (auto& sub : ast->tokenList)
		{
			if (sub->type == TokenType::Decl)
				result.push_back(sub);
		}

		return result;
	}

	void __SearchNode(ASTNode* ast, TokenType type, std::deque<ASTNode*>* result)
	{
		if (ast->type == type)
			result->push_back(ast);
		for (auto& sub : ast->tokenList)
			__SearchNode(sub, type, result);
	}

	std::deque<ASTNode*> SearchGlobalConstants(ASTNode* ast)
	{
		auto result = std::deque<ASTNode*>();
		__SearchNode(ast, TokenType::ConstDecl, &result);
		for (auto it = result.begin(); it != result.end();)
		{
			if ((*it)->parent->type != TokenType::CompUnit)
				it = result.erase(it);
			else
			{
				*it = (*it)->parent;
				++it;
			}
		}

		return result;
	}

	std::deque<ASTNode*> SearchGlobalFunctions(ASTNode* ast)
	{
		auto result = std::deque<ASTNode*>();
		__SearchNode(ast, TokenType::FuncDeclBody, &result);
		for (auto& node : result)
			node = node->parent->parent;
		return result;
	}

	std::deque<int> GetVariableSize(ASTNode* var)
	{
		return std::deque<int>();
	}

	IR::ConstDecl* AnalysisVar(ASTNode* var)
	{
		auto res = new IR::ConstDecl();

		auto constDecl = var->tokenList.front();
		auto type = constDecl->tokenList[1];
		auto name = constDecl->tokenList[2];
		auto body = constDecl->tokenList[3];
		auto varInit = GetChild<TokenType::VarInit>(body);
		auto varArray = GetChild<TokenType::ArraySizeDecl>(body);

		auto& arr_size = res->size;

		if (varArray == nullptr)
			arr_size.push_back(0);
		else
			for (auto& se : AST::GetChilds<TokenType::ArraySizeNum>(varArray))
			{
				arr_size.push_back(EvalConstExpr(se->tokenList.front()));
			}

		res->name = std::any_cast<std::string>(name->value);
		return res;
	}

	int GetNumberValue(ASTNode* number)
	{
		auto size_val = std::atoll(
			std::any_cast<std::string>(number->value)
			.c_str());

		if (size_val > std::numeric_limits<int>::max())
		{
			Console::Log("Constant value exceeded numeric limit! Max:",
				std::numeric_limits<int>::max(),
				"but get",
				size_val,
				Level::Warning);
			Console::SetExitCode(-3);
		}
		else if (size_val < std::numeric_limits<int>::min())
		{
			Console::Log("Constant value exceeded numeric limit! Min:",
				std::numeric_limits<int>::min(),
				"but get",
				size_val,
				Level::Warning);
			Console::SetExitCode(-3);
		}

		auto orig = static_cast<uint64_t>(size_val);

		return static_cast<int>(orig & 0x0FFFFFFFF);
	}

	int EvalConstMulExpr(ASTNode* expr) 
	{
		int result = EvalConstExpr(expr->tokenList.front());
		for (auto it = expr->tokenList.begin() + 1; it != expr->tokenList.end(); ++it) 
		{
			if ((*it)->type == TokenType::Multi)
			{
				result *= EvalConstExpr(*(++it));
			}
			else if ((*it)->type == TokenType::Divid)
			{
				result /= EvalConstExpr(*(++it));
			}
			else 
			{
				Console::Log("Unexpected Operation in MulExpr Tree:", __tstr((*it)->type), Level::Warning);
				Console::SetExitCode(-4);
				return result;
			}
		}
		return result;
		
	}

	int EvalConstAddExpr(ASTNode* expr)
	{
		int result = EvalConstExpr(expr->tokenList.front());
		for (auto it = expr->tokenList.begin() + 1; it != expr->tokenList.end(); ++it)
		{
			if ((*it)->type == TokenType::Plus)
			{
				result += EvalConstExpr(*(++it));
			}
			else if ((*it)->type == TokenType::Minus)
			{
				result -= EvalConstExpr(*(++it));
			}
			else
			{
				Console::Log("Unexpected Operation in AddExpr Tree:", __tstr((*it)->type), Level::Warning);
				Console::SetExitCode(-4);
				return result;
			}
		}
		return result;

	}

	int EvalConstPrimaryExp(ASTNode* expr)
	{
		if (expr->tokenList.size() != 3) 
		{
			Console::Log("Unexpected Operation in PrimaryExp Tree:", __tstr(expr->type), Level::Warning);
			Console::SetExitCode(-5);
			return 0;
		}
		else
			return EvalConstExpr(expr->tokenList[1]);
	}

	int EvalConstExpr(ASTNode* expr)
	{
		switch (expr->type)
		{
		case TokenType::Interger:
			return GetNumberValue(expr);

		case TokenType::ConstExp:
			return EvalConstExpr(expr->tokenList.front());

		case TokenType::MulExp:
			return EvalConstMulExpr(expr);
		
		case TokenType::AddExp:
			return EvalConstAddExpr(expr);

		case TokenType::PrimaryExp:
			return EvalConstPrimaryExp(expr);

		default:
			Console::Log("Unexpected Node in ConstExpr Tree:", __tstr(expr->type), Level::Warning);
			Console::SetExitCode(-3);
			return 1;
		

		}
		return 0;
	}

	std::deque<ASTNode*> SearchGlobalVariables(ASTNode* ast)
	{
		auto result = std::deque<ASTNode*>();
		//__SearchNode(ast, TokenType::VarDeclbody, &result);
		//for (auto it = result.begin(); it != result.end();)
		//{
		//	if ((*it)->parent->type != TokenType::VarOrFuncDeclBody)
		//		it = result.erase(it);
		//	else if ((*it)->parent->parent->parent->parent->type != TokenType::CompUnit)
		//		it = result.erase(it);
		//	else
		//	{
		//		*it = (*it)->parent;
		//		++it;
		//	}
		//}

		return result;
	}
}
