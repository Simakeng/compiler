#include "ASTUtils.h"
#include "Logger.h"
#include <string>
#include <numeric>

using namespace std;
using namespace Compiler::Parser;

namespace Compiler::AST
{

	auto GetFirstChild(ASTNode* ast)
	{
		if (ast->tokenList.size() == 0)
		{
			Console::Log("Trying to access empty node", __tstr(ast->type), Level::Fatal);
			Console::Terminate(-12);
		}
		return ast->tokenList.front();
	}

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

		if (all_empty && ast->type != TokenType::ArrayPtrEmpty)
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

	void StripArrayInitValue(ASTNode* ast)
	{
		for (auto& sub : ast->tokenList)
			StripArrayInitValue(sub);

		if (ast->type == TokenType::VarInitValue)
		{
			for (auto it = ast->tokenList.begin(); it != ast->tokenList.end();)
			{
				auto type = (*it)->type;
				auto ptype = ast->type;
				if ((*it)->type == TokenType::Brs ||
					(*it)->type == TokenType::Bre ||
					(*it)->type == TokenType::Comma)
				{
					auto ptr = (*it);
					it = ast->tokenList.erase(it);
					decltype(ast->tokenList) _;
					std::swap(_, ptr->tokenList);
					FreeNode(ptr);
				}
				else
				{
					++it;
				}
			}
		}
	}

	IR::Decl::Type GetDeclType(ASTNode* ast)
	{
		if (ast->tokenList.front()->type == TokenType::ConstDecl)
			return IR::Decl::Type::Const;
		if (ast->tokenList.front()->type == TokenType::VarOrFuncDecl)
		{
			if (GetChild<TokenType::FuncDeclBody>
				(ast->tokenList.front()) != nullptr)
				return IR::Decl::Type::Function;
			else 
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

	std::deque<int> GetVariableSize(ASTNode* var)
	{
		return std::deque<int>();
	}
	void AnalysisVarInitializationList(ASTNode* init_list, vector<int>& init_vals, IR::SymbolList* syms = nullptr)
	{
		init_vals.push_back(EvalConstExpr(init_list, syms));
	}

	int AnalysisArrayInitializationList(ASTNode* init_list, vector<int>& init_vals, deque<int> arr_size, IR::SymbolList* syms = nullptr, int start_addr = 0)
	{
		int dim_cnt = arr_size.front();
		int offset = reduce(arr_size.begin() + 1, arr_size.end(), 1, multiplies<>());
		int i = 0;
		auto it = init_list->tokenList.begin();
		for (int i = 0; i < dim_cnt; i++)
		{
			deque<int> drr_size = arr_size;
			drr_size.pop_front();

			if (it == init_list->tokenList.end())
			{
				return it - init_list->tokenList.begin();
			}

			if ((*it)->type == TokenType::ConstExp)
			{
				if (drr_size.size() == 0)
				{
					init_vals[i * offset + start_addr] = EvalConstExpr((*it), syms);
					++it;
				}
				else
				{
					auto readcnt = AnalysisArrayInitializationList(init_list, init_vals, drr_size, syms, i * offset + start_addr);
					it += readcnt;
				}
			}
			else if ((*it)->type == TokenType::VarInitValue)
			{
				if (drr_size.empty())
					drr_size.push_back(1);
				AnalysisArrayInitializationList((*it), init_vals, drr_size, syms, i * offset + start_addr);
				++it;
			}
		}


		//for (auto& it : init_list->tokenList)
		//{
		//	if (i >= dim_cnt)
		//		return;

		//	if (it->type == TokenType::ConstExp)
		//	{
		//		init_vals[start_addr + offset * i] = EvalConstExpr(it);
		//		i++;
		//	}
		//	else if (it->type == TokenType::VarInitValue)
		//	{

		//	}
		//	else
		//	{
		//		Console::Log("Malformed Multidimensional Array Initialization!", Level::Error);
		//		Console::SetExitCode(-7);
		//	}
		//}
		return it - init_list->tokenList.begin();
	}

	std::deque<int> GetArrayAccessValue(ASTNode* array_access)
	{
		auto arr_size = std::deque<int>();
		for (auto& se : AST::GetChilds<TokenType::ArraySizeNum>(array_access))
		{
			arr_size.push_back(EvalConstExpr(se->tokenList.front()));
		}
		return arr_size;
	}

	IR::VarDecl* AnalysisVar(ASTNode* name, ASTNode* body, IR::SymbolList* syms)
	{
		auto res = new IR::VarDecl();

		auto& arr_size = res->size;
		auto& init_val = res->initValue;

		res->name = std::any_cast<std::string>(name->value);

		if (body == nullptr) 
		{
			arr_size.push_back(0);
			init_val.push_back(0);
			return res;
		}

		auto varInit = GetChild<TokenType::VarInit>(body);
		auto varArray = GetChild<TokenType::ArraySizeDecl>(body);

		

		if (varArray == nullptr)
		{
			arr_size.push_back(0);

		}
		else  for (auto& se : AST::GetChilds<TokenType::ArraySizeNum>(varArray))
		{
			arr_size.push_back(EvalConstExpr(se->tokenList.front()));
		}

		auto size = std::reduce(arr_size.begin(), arr_size.end(), 1, std::multiplies<>());
		init_val.resize(size);

		if (size == 0)
			AnalysisVarInitializationList(varInit->tokenList[1], init_val, syms);
		else AnalysisArrayInitializationList(varInit->tokenList[1], init_val, arr_size, syms);

		
		return res;
	}

	IR::VarDecl* AnalysisVarDecl(ASTNode* var, IR::SymbolList* syms)
	{
		
		auto varDecl = var->tokenList.front(); 

		auto name = GetChild<TokenType::Ident>(varDecl);
		auto body = GetChild<TokenType::VarDeclbody>(varDecl);

		return AnalysisVar(name, body, syms);
		
	}

	IR::ConstDecl::VType GetReturnValueType(ASTNode* var)
	{
		for (auto& sub : var->tokenList)
		{
			if (sub->type == TokenType::Void)
				return IR::ConstDecl::VType::VOID;
			else if (sub->type == TokenType::Int)
				return IR::ConstDecl::VType::INT;
			else
			{
				Console::Log("Unknow return valuetype", __tstr(sub->type), Level::Info);
				return IR::ConstDecl::VType::VOID;
			}
		}
		Console::Log("Node", __tstr(var->type), "has no child", Level::Info);
		return IR::ConstDecl::VType::VOID;
	}

	IR::ConstDecl* AnalysisConstDecl(ASTNode* var, IR::SymbolList* syms)
	{
		auto res = AnalysisVarDecl(var, syms);
		res->type = IR::Decl::Type::Const;
		return res;
	}

	IR::VarDecl* AnalysisFuncParam(ASTNode* param) 
	{
		auto res = new IR::VarDecl();
		auto& nodeName = param->tokenList[1];
		
		res->vtype = GetReturnValueType(param);
		res->name = std::any_cast<std::string>(nodeName->value);

		if (param->tokenList.size() == 3) 
		{
			auto& arr_sizes = param->tokenList[2];
			for (auto sizes : GetChilds<TokenType::ArraySizeNum>(arr_sizes)) 
			{
				auto value = GetFirstChild(sizes);
				if (value->type == TokenType::ArrayPtrEmpty)
				{
					if (res->size.size() != 0) 
					{
						Console::Log("Array size declaration can't be null", Level::Info);
						Console::SetExitCode(-11);
					}
					else res->size.push_back(-1);
				}
				else if (value->type == TokenType::ConstExp)
				{
					res->size.push_back(EvalConstExpr(value));
				}
				else 
				{
					Console::Log("Unknow array size declare node:", __tstr(value->type), Level::Info);
				}
			}
		}
		else 
		{
			res->size.push_back(0);
		}
		return res;
	}

	IR::FunctionDecl* AnalysisFunction(ASTNode* var, IR::SymbolList* syms)
	{
		auto res = new IR::FunctionDecl();
		res->params.parentList = syms;

		auto funcDecl = var->tokenList.front();

		auto rvtype = funcDecl->tokenList[0];
		res->returnValueType = GetReturnValueType(rvtype);

		auto name = funcDecl->tokenList[1];
		res->name = std::any_cast<std::string>(name->value);

		auto body = funcDecl->tokenList[2];

		auto params = GetChilds<TokenType::FuncParamDecl>(body);
		for (auto& param : params)
		{
			auto dpar = AnalysisFuncParam(param);
			res->params.AppendDecl(dpar);
		}
		auto codes = body->tokenList.back();
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

	int EvalConstMulExpr(ASTNode* expr, IR::SymbolList* syms = nullptr)
	{
		int result = EvalConstExpr(expr->tokenList.front(), syms);
		for (auto it = expr->tokenList.begin() + 1; it != expr->tokenList.end(); ++it)
		{
			if ((*it)->type == TokenType::Multi)
			{
				result *= EvalConstExpr(*(++it), syms);
			}
			else if ((*it)->type == TokenType::Divid)
			{
				result /= EvalConstExpr(*(++it), syms);
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

	int EvalConstAddExpr(ASTNode* expr, IR::SymbolList* syms = nullptr)
	{
		int result = EvalConstExpr(expr->tokenList.front(), syms);
		for (auto it = expr->tokenList.begin() + 1; it != expr->tokenList.end(); ++it)
		{
			if ((*it)->type == TokenType::Plus)
				result += EvalConstExpr(*(++it), syms);
			else if ((*it)->type == TokenType::Minus)
				result -= EvalConstExpr(*(++it), syms);
			else
			{
				Console::Log("Unexpected Operation in AddExpr Tree:", __tstr((*it)->type), Level::Warning);
				Console::SetExitCode(-4);
				return result;
			}
		}
		return result;

	}

	int EvalConstIdentSymTableIndexing(ASTNode* expr, ASTNode* array_access = nullptr, IR::SymbolList* syms = nullptr)
	{
		auto name = any_cast<string>(expr->value);
		if (syms == nullptr)
		{
			Console::Log("EvalConstIdentSymTableIndexing was called, "
				"but symbolist is noe specified", Level::Fatal);
			Console::Terminate(-114514);
			return 0;
		}
		auto ref = syms->Index(name);

		if (ref == nullptr)
		{
			Console::Log("bad refrence for '", name, "', item not found", Level::Info);
			return 0;
		}

		if (ref->type != IR::Decl::Type::Const)
		{
			Console::Log("bad refrence for '", name, "'", Level::Info);
			return 0;
		}

		auto constDecl = (IR::ConstDecl*)ref;

		auto off = 0;

		if (array_access != nullptr)
		{
			auto vals = GetArrayAccessValue(array_access);
			auto& sizes = constDecl->size;

			if (sizes.front() == 0)
			{
				Console::Log("bad array access, '", name, "' is not a array", Level::Info);
				return 0;
			}

			if (vals.size() != sizes.size())
			{
				Console::Log("bad array access for '", name, "'", Level::Info);
				return 0;
			}

			for (int i = 0; i < vals.size(); i++)
			{
				int arr_off = reduce(sizes.begin() + i + 1, sizes.end(), 1, multiplies<>());
				off += vals[i] * arr_off;
			}
		}


		return constDecl->initValue[off];
	}

	int EvalConstUnaryExpr(ASTNode* expr, IR::SymbolList* syms = nullptr)
	{
		if (expr->tokenList.size() != 2)
		{
			Console::Log("Unexpected AST Structure in UnaryExpr Tree, Node count:",
				expr->tokenList.size(), Level::Warning);
			Console::SetExitCode(-5);
			return 1;
		}

		auto& op = expr->tokenList[0];
		auto& sube = expr->tokenList[1];

		if (op->type == TokenType::Minus)
			return -EvalConstExpr(sube, syms);
		else if (op->type == TokenType::Plus)
			return EvalConstExpr(sube, syms);
		else if (op->type == TokenType::Not)
			return !EvalConstExpr(sube, syms);
		else if (op->type == TokenType::Ident)
		{
			return EvalConstIdentSymTableIndexing(op, sube, syms);
		}
		else
		{
			Console::Log("Unexpected Operation in UnaryExpr Tree:", __tstr(op->type), Level::Warning);
			Console::SetExitCode(-6);
			return 1;

		}

	}

	int EvalConstPrimaryExp(ASTNode* expr, IR::SymbolList* syms = nullptr)
	{
		if (expr->tokenList.size() != 3)
		{
			Console::Log("Unexpected Operation in PrimaryExp Tree:", __tstr(expr->type), Level::Warning);
			Console::SetExitCode(-5);
			return 0;
		}
		else
			return EvalConstExpr(expr->tokenList[1], syms);
	}



	int EvalConstExpr(ASTNode* expr, IR::SymbolList* syms)
	{
		switch (expr->type)
		{
		case TokenType::Interger:
			return GetNumberValue(expr);

		case TokenType::ConstExp:
			return EvalConstExpr(expr->tokenList.front(), syms);

		case TokenType::MulExp:
			return EvalConstMulExpr(expr, syms);

		case TokenType::AddExp:
			return EvalConstAddExpr(expr, syms);

		case TokenType::PrimaryExp:
			return EvalConstPrimaryExp(expr, syms);

		case TokenType::UnaryExp:
			return EvalConstUnaryExpr(expr, syms);

		case TokenType::Ident:
			return EvalConstIdentSymTableIndexing(expr, nullptr, syms);
		default:
			Console::Log("Unexpected Node in ConstExpr Tree:", __tstr(expr->type), Level::Warning);
			Console::SetExitCode(-3);
			return 1;


		}
		return 0;
	}



}
