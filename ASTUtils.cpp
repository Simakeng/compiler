#include "ASTUtils.h"
#include "Logger.h"
#include <string>
#include <numeric>

using namespace std;
using namespace Compiler::Parser;

namespace Compiler::AST
{
	IR::Operation* CreateConstOp(int value);

	IR::Stmt* AnalysisIfElseStmt(ASTNode* exp, IR::SymbolList* syms);

	void AnalysisCodeBlock(ASTNode* block, IR::CodeBlock& cb);

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
		if (ast->tokenList.size() == 1 && ast->type != TokenType::UnaryExp && ast->type != TokenType::UnaryOp)
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

	/*void StripUniformStructure(ASTNode* ast)
	{
		for (auto& sub : ast->tokenList)
			StripUniformStructure(sub);

		if (ast->type == TokenType::Stmt)
		{
			auto child = GetFirstChild(ast);
			if (child->type == TokenType::If)
			{
				auto& stmt = ast->tokenList[4];

				if (GetFirstChild(stmt)->type != TokenType::CodeBlock)
				{
					auto cb = CreateNode(TokenType::CodeBlock, stmt);
					cb->tokenList.push_back(stmt->tokenList.front());
					stmt->tokenList.front() = cb;
					stmt = cb;
				}
			}


		}
		if (ast->type == TokenType::ElseStmt)
		{
			auto elseStmt = GetChild<TokenType::Stmt>(ast);
			if (elseStmt == nullptr)
				return;

			auto& stmt = elseStmt->tokenList[1];

			if (GetFirstChild(stmt)->type == TokenType::CodeBlock)
				return;

			auto cb = CreateNode(TokenType::CodeBlock, ast);
			cb->tokenList.push_back(stmt);
			stmt->tokenList.front() = cb;
			stmt = cb;
		}
	}*/

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

	int AnalysisArrayInitializationList(ASTNode* init_list, vector<int>& init_vals, deque<int> arr_size, IR::SymbolList* syms = nullptr, int start_addr = 0,int it_off = 0)
	{
		int dim_cnt = arr_size.front();
		int offset = reduce(arr_size.begin() + 1, arr_size.end(), 1, multiplies<>());
		int i = 0;
		auto it = init_list->tokenList.begin() + it_off;
		for (int i = 0; i < dim_cnt; i++)
		{
			deque<int> drr_size = arr_size;
			drr_size.pop_front();

			if (it == init_list->tokenList.end())
			{
				return it - init_list->tokenList.begin() - it_off;
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
					auto readcnt = AnalysisArrayInitializationList(init_list, init_vals, drr_size, syms, i * offset + start_addr,
						it - init_list->tokenList.begin());
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

		return it - init_list->tokenList.begin() - it_off;
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
		res->dtype = IR::Decl::Type::Const;
		return res;
	}

	IR::VarDecl* AnalysisFuncParam(ASTNode* param)
	{
		auto res = new IR::VarDecl();
		res->dtype = IR::Decl::Type::Param;

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

	IR::Stmt* AnalysisStmt(ASTNode* stmt, IR::SymbolList* symtable)
	{
		auto child = GetFirstChild(stmt);
		if (child->type == TokenType::Decl)
		{
			IR::Decl* d = nullptr;
			switch (AST::GetDeclType(child))
			{
			case IR::Decl::Type::Const: d = AST::AnalysisConstDecl(child, symtable); break;
			case IR::Decl::Type::Function: d = AST::AnalysisFunction(child, symtable); break;
			case IR::Decl::Type::Var:  d = AST::AnalysisVarDecl(child, symtable); break;
			}
			d->stype = IR::Stmt::Type::Decl;
			return d;
		}
		else if (child->type == TokenType::Exp)
		{
			return AnalysisExprStmt(child, symtable);
		}
		else if (child->type == TokenType::If)
		{
			return AnalysisIfElseStmt(stmt, symtable);
		}
		else if (child->type == TokenType::While)
		{

		}
		else if (child->type == TokenType::CodeBlock)
		{
			auto codeBlock = new IR::CodeBlock();

			codeBlock->parentSymtable = symtable;
			codeBlock->symbs.parentSymList = symtable;
			AnalysisCodeBlock(child, *codeBlock);
			return codeBlock;
		}
	}

	void AnalysisCodeBlock(ASTNode* block, IR::CodeBlock& cb)
	{
		auto& symtable = cb.symbs;
		auto& stmts = cb.stmts;
		for (auto& stmt : GetChilds<TokenType::Stmt>(block))
		{
			auto s = AnalysisStmt(stmt, &symtable);
			if (s->stype == IR::Stmt::Type::Decl)
			{
				auto d = static_cast<IR::Decl*>(s);
				symtable.AppendDecl(d);
			}
			cb.stmts.push_back(s);
		}
	}


	IR::FunctionDecl* AnalysisFunction(ASTNode* var, IR::SymbolList* syms)
	{
		auto res = new IR::FunctionDecl();
		res->params.parentSymList = syms;

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

		auto& codeBlock = res->procedures;

		auto codes = GetChild<TokenType::CodeBlock>(body);

		codeBlock.parentSymtable = syms;
		codeBlock.symbs.parentSymList = syms;

		AnalysisCodeBlock(codes, codeBlock);

		return res;
	}

	IR::Operation* SolveExprToList(ASTNode* exp, IR::Expr* rexpr);

	IR::Operation* SolveExprIdentArrayAccess(ASTNode* exp, IR::Expr* rexpr, IR::ConstDecl* ident)
	{
		std::deque<IR::Operation*> accessOps;
		for (auto& child : exp->tokenList)
		{
			if (child->type == TokenType::Sbs || child->type == TokenType::Sbe)
				continue;

			auto accop = SolveExprToList(child, rexpr);
			accessOps.push_back(accop);
		}
		auto& sizes = ident->size;

		if (sizes.size() != accessOps.size())
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}

		std::deque<IR::Operation*> offOps;

		for (int i = 0; i < sizes.size(); i++)
		{
			int off = reduce(sizes.begin() + i + 1, sizes.end(), 1, multiplies<>());
			if (off == 1)
			{
				offOps.push_back(accessOps[i]);
			}
			else
			{
				auto const_val = CreateConstOp(off);
				rexpr->ops.push_back(const_val);

				auto mul_op = new IR::Operation();
				mul_op->optype = IR::Operation::Type::MUL;
				mul_op->Opend1 = accessOps[i];
				mul_op->Opend2 = const_val;
				rexpr->ops.push_back(mul_op);

				offOps.push_back(mul_op);
			}

		}

		for (auto it = offOps.begin() + 1; it != offOps.end();)
		{
			auto add_op = new IR::Operation();
			add_op->optype = IR::Operation::Type::ADD;
			add_op->Opend1 = *(it - 1);
			add_op->Opend2 = *(it);
			rexpr->ops.push_back(add_op);

			*(it - 1) = add_op;
			it = offOps.erase(it);
		}

		return offOps.front();
	}

	IR::Operation* CreateConstOp(int value)
	{
		auto const_val = new IR::ConstValueOperation();
		const_val->optype = IR::Operation::Type::CONST_VALUE;
		const_val->val = 0;
		return const_val;
	}

	IR::Operation* SolveExprAssignExpOpend(ASTNode* exp, IR::Expr* rexpr)
	{
		auto res = new IR::AssignOperation();
		res->optype = IR::Operation::Type::ASSIGN_VALUE;

		auto& lval = exp->tokenList[0];

		res->targetIdent = std::any_cast<string>(
			lval->tokenList.front()->value);

		auto ident = rexpr->parentSymtable->Index(res->targetIdent);
		if (ident->dtype == IR::Decl::Type::Function)
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::Terminate(-14);
		}

		auto v_ident = static_cast<IR::ConstDecl*>(ident);
		auto offOp = static_cast<IR::Operation*>(nullptr);
		if (lval->tokenList.size() == 1)
		{
			auto const_val = CreateConstOp(0);
			rexpr->ops.push_back(const_val);
			offOp = const_val;
		}
		else
		{
			offOp = SolveExprIdentArrayAccess(lval->tokenList[1], rexpr, v_ident);
		}

		auto& rval = exp->tokenList[2];

		auto rvalOp = SolveExprToList(rval, rexpr);

		res->offop = offOp;
		res->valop = rvalOp;

		return res;
	}
	IR::Operation* SolveExprMul(ASTNode* exp, IR::Expr* rexpr) 
	{
		auto& lval = exp->tokenList[0];
		auto& op = exp->tokenList[1];
		auto& rval = exp->tokenList[2];

		auto lval_op = SolveExprToList(lval, rexpr);
		auto rval_op = SolveExprToList(rval, rexpr);

		auto rop = new IR::Operation();

		rop->Opend1 = lval_op;
		rop->Opend2 = rval_op;

		if (op->type == TokenType::Multi)
			rop->optype = IR::Operation::Type::MUL;
		else if (op->type == TokenType::Divid)
			rop->optype = IR::Operation::Type::DIV;
		else if (op->type == TokenType::Remain)
			rop->optype = IR::Operation::Type::MOD;
		else
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}

		rexpr->ops.push_back(rop);
		return rop;
	}

	IR::Operation* SolveExprAdd(ASTNode* exp, IR::Expr* rexpr)
	{
		auto& lval = exp->tokenList[0];
		auto& op = exp->tokenList[1];
		auto& rval = exp->tokenList[2];

		auto lval_op = SolveExprToList(lval, rexpr);
		auto rval_op = SolveExprToList(rval, rexpr);

		auto rop = new IR::Operation();


		rop->Opend1 = lval_op;
		rop->Opend2 = rval_op;

		if (op->type == TokenType::Plus)
			rop->optype = IR::Operation::Type::ADD;
		else if (op->type == TokenType::Minus)
			rop->optype = IR::Operation::Type::SUB;
		else
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}

		rexpr->ops.push_back(rop);
		return rop;
	}
	IR::Operation* SolveExprUnary(ASTNode* exp, IR::Expr* rexpr)
	{
		auto s = GetFirstChild(exp);

		if (s->type == TokenType::Pbs)
		{
			if (exp->tokenList.size() != 3)
			{
				Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
				Console::SetExitCode(-14);
			}
			return SolveExprToList(s->tokenList[1], rexpr);
		}
		else if (s->type == TokenType::Ident)
		{
			if (exp->tokenList.size() == 1)
			{
				auto refop = new IR::IdentRefOperation();
				refop->optype = IR::Operation::Type::PARAM_REF;
				refop->targetIdentName = any_cast<string>(s->value);
				auto off_op = static_cast<IR::Operation*>(nullptr);

				off_op = CreateConstOp(0);
				rexpr->ops.push_back(off_op);

				refop->offop = off_op;
				rexpr->ops.push_back(refop);
				return refop;
			}
			else
			{
				if (exp->tokenList[1]->type == TokenType::ArrayAcces)
				{
					auto refop = new IR::IdentRefOperation();
					refop->optype = IR::Operation::Type::PARAM_REF;
					refop->targetIdentName = any_cast<string>(s->value);
					auto off_op = static_cast<IR::Operation*>(nullptr);

					auto ident_name = rexpr->parentSymtable->Index(refop->targetIdentName);
					if (ident_name->dtype == IR::Decl::Type::Function)
					{
						Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
						Console::Terminate(-14);
					}
					off_op = SolveExprIdentArrayAccess(exp->tokenList[1], rexpr, static_cast<IR::ConstDecl*>(ident_name));

					refop->offop = off_op;
					rexpr->ops.push_back(refop);
					return refop;
				}
				else if (exp->tokenList[1]->type == TokenType::FuncCall)
				{
					return nullptr;
				}
				else
				{
					Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
					Console::SetExitCode(-14);
				}
			}
		}
		else if (s->type == TokenType::UnaryOp)
		{
			auto ops = GetFirstChild(s);
			auto opand = SolveExprToList(exp->tokenList.back(), rexpr);
			if (ops->type == TokenType::Plus)
			{
				return opand;
			}
			else if (ops->type == TokenType::Minus) 
			{
				auto not_op = new IR::Operation();
				not_op->optype = IR::Operation::Type::NEG;
				not_op->Opend1 = opand;

				rexpr->ops.push_back(not_op);
				return not_op;
			}
			else if (ops->type == TokenType::Not)
			{
				auto not_op = new IR::Operation();
				not_op->optype = IR::Operation::Type::NOT;
				not_op->Opend1 = opand;

				rexpr->ops.push_back(not_op);
				return not_op;
			}
		}
		else if (s->type == TokenType::Interger)
		{
			auto val_op = CreateConstOp(GetNumberValue(s));
			rexpr->ops.push_back(val_op);
			return val_op;
		}
		else
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}
		return nullptr;
	}

	IR::Operation* SolveExprToList(ASTNode* exp, IR::Expr* rexpr)
	{
		switch (exp->type)
		{
		case TokenType::Exp: return SolveExprToList(GetFirstChild(exp), rexpr);
		case TokenType::AssignExp:return SolveExprAssignExpOpend(exp, rexpr);
		case TokenType::AddExp:return SolveExprAdd(exp, rexpr);
		case TokenType::MulExp:return SolveExprMul(exp, rexpr);
		case TokenType::UnaryExp:return SolveExprUnary(exp, rexpr);
		}
		return nullptr;
	}

	IR::Expr* AnalysisExprStmt(ASTNode* exp, IR::SymbolList* syms)
	{
		auto res = new IR::Expr();
		res->stype = IR::Stmt::Type::Expr;
		res->parentSymtable = syms;
		auto rvop = SolveExprToList(exp, res);
		res->ops.push_back(rvop);
		return res;
	}

	IR::Expr* AnalysisCondTree(ASTNode* exp, IR::SymbolList* syms, IR::IfElseStmt* rif);


	IR::LogicCondNode* AnalysisCondOrExp(
		ASTNode* exp, IR::SymbolList* syms, 
		IR::IfElseStmt* rif, 
		IR::LogicCondNode* successNode = nullptr,
		IR::LogicCondNode* failNode = nullptr)
	{
		auto node = new IR::LogicCondNode();
		node->ctype = IR::LogicCondNode::CType::OR;
		node->etype = IR::Expr::EType::Cond;
		auto& nodes = node->evalList;

		for (auto& sube : exp->tokenList)
		{
			if (sube->type == TokenType::Or)
				continue;
			auto orres = AnalysisCondTree(sube, syms, rif);
			nodes.push_back(orres);
		}

		return node;
	}

	IR::LogicCondNode* AnalysisCondAndExp(
		ASTNode* exp, IR::SymbolList* syms,
		IR::IfElseStmt* rif) 
	{
		auto node = new IR::LogicCondNode();
		node->ctype = IR::LogicCondNode::CType::AND;
		node->etype = IR::Expr::EType::Cond;
		auto& nodes = node->evalList;

		for (auto& sube : exp->tokenList)
		{
			if (sube->type == TokenType::And)
				continue;
			auto orres = AnalysisCondTree(sube, syms, rif);
			nodes.push_back(orres);
		}

		return node;
	}
	
	IR::Expr* AnalysisCondEqExp(ASTNode* exp, IR::SymbolList* syms, IR::IfElseStmt* rif)
	{
		auto& lval = exp->tokenList[0];
		auto& op = exp->tokenList[1];
		auto& rval = exp->tokenList[2];

		auto expr = new IR::Expr();
		expr->parentSymtable = syms;
		expr->stype = IR::Stmt::Type::Expr;

		auto r1 = SolveExprToList(lval, expr);
		auto r2 = SolveExprToList(rval, expr);

		auto rel_op = new IR::Operation();
		rel_op->Opend1 = r1;
		rel_op->Opend2 = r2;

		if (op->type == TokenType::Eq)
			rel_op->optype = IR::Operation::Type::EQ;
		else if (op->type == TokenType::Neq)
			rel_op->optype = IR::Operation::Type::NEQ;
		else
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}

		expr->ops.push_back(rel_op);

		return expr;

	}
	IR::Expr* AnalysisCondRelExp(
		ASTNode* exp, IR::SymbolList* syms,
		IR::IfElseStmt* rif)
	{
		auto opand1 = exp->tokenList[0];
		auto op = exp->tokenList[1];
		auto opand2 = exp->tokenList[2];

		auto expr = new IR::Expr();
		expr->parentSymtable = syms;
		expr->stype = IR::Stmt::Type::Expr;

		auto r1 = SolveExprToList(opand1, expr);
		auto r2 = SolveExprToList(opand2, expr);

		auto rel_op = new IR::Operation();
		rel_op->Opend1 = r1;
		rel_op->Opend2 = r2;

		if (op->type == TokenType::Eq)
			rel_op->optype = IR::Operation::Type::EQ;
		else if (op->type == TokenType::Neq)
			rel_op->optype = IR::Operation::Type::NEQ;
		else if(op->type == TokenType::Le)
			rel_op->optype = IR::Operation::Type::LE;
		else if(op->type == TokenType::Leq)
			rel_op->optype = IR::Operation::Type::LEQ;
		else if(op->type == TokenType::Ge)
			rel_op->optype = IR::Operation::Type::GE;
		else if(op->type == TokenType::Geq)
			rel_op->optype = IR::Operation::Type::GEQ;
		else 
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}

		expr->ops.push_back(rel_op);
		
		return expr;

	}

	IR::Expr* AnalysisCondTree(ASTNode* exp, IR::SymbolList* syms, IR::IfElseStmt* rif)
	{
		if (exp->type == TokenType::Cond)
			return AnalysisCondOrExp(GetFirstChild(exp), syms, rif);
		else if (exp->type == TokenType::LOrExp)
			return AnalysisCondOrExp(exp, syms, rif);
		else if (exp->type == TokenType::LAndExp)
			return AnalysisCondAndExp(exp, syms, rif);
		else if (exp->type == TokenType::EqExp)
			return AnalysisCondEqExp(exp, syms, rif);
		else if (exp->type == TokenType::RelExp)
			return AnalysisCondRelExp(exp, syms, rif);

		Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
		Console::SetExitCode(-14);
		return nullptr;
	}

	IR::Stmt* AnalysisIfElseStmt(ASTNode* exp, IR::SymbolList* syms)
	{
		auto res = new IR::IfElseStmt();
		res->parentSymtable = syms;

		auto cond = AnalysisCondTree(GetChild<TokenType::Cond>(exp), syms, res);
		if (cond->etype != IR::Expr::EType::Cond) 
		{
			Console::Log("Unexpected Error in File:" __FILE__ "line:", __LINE__, Level::Fatal);
			Console::SetExitCode(-14);
		}

		res->cond = (IR::LogicCondNode*)cond;

		res->success = AnalysisStmt(GetChild<TokenType::Stmt>(exp), syms);

		auto elseStmt = GetChild<TokenType::ElseStmt>(exp);
		if (elseStmt == nullptr)
			res->fail = nullptr;
		else
			res->fail = AnalysisStmt(GetChild<TokenType::Stmt>(elseStmt), syms);
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

		if (ref->dtype != IR::Decl::Type::Const)
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
		if (expr->tokenList.size() == 2)
		{

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
		if (expr->tokenList.size() == 1)
		{
			auto& val = expr->tokenList[0];

			if (val->type == TokenType::Ident)
				return EvalConstIdentSymTableIndexing(val, nullptr, syms);
			else if (val->type == TokenType::Interger)
				return GetNumberValue(val);
			else
			{
				Console::Log("Unexpected AST Structure in UnaryExpr Tree,node ",
					__tstr(val->type), "Was found!", Level::Warning);
				Console::SetExitCode(-5);
				return 1;
			}
		}
		Console::Log("Unexpected AST Structure in UnaryExpr Tree, Node count:",
			expr->tokenList.size(), Level::Warning);
		Console::SetExitCode(-5);
		return 1;
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
