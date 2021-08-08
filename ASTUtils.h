#pragma once
#include "Parser.h"
#include <deque>
#include "IR.h"

namespace Compiler::AST
{
	using ASTNode = Parser::ASTNode;


	void StripEmptyNode(ASTNode* ast);

	void StripExprNode(ASTNode* ast);

	void StripHumanReadable(ASTNode* ast);

	void StripArrayInitValue(ASTNode* ast);

	void StripUniformStructure(ASTNode* ast);

	IR::Decl::Type GetDeclType(ASTNode* ast);

	std::deque<ASTNode*> SearchNodeDecls(ASTNode* ast);

	std::deque<ASTNode*> SearchGlobalVariables(ASTNode* ast);

	std::deque<ASTNode*> SearchGlobalConstants(ASTNode* ast);

	std::deque<ASTNode*> SearchGlobalFunctions(ASTNode* ast);

	std::deque<ASTNode*> SearchLocalVariables(ASTNode* ast);

	std::deque<ASTNode*> SearchLocalConstants(ASTNode* ast);

	std::deque<ASTNode*> SearchLocalStmts(ASTNode* ast);

	std::deque<int> GetVariableSize(ASTNode* var);

	IR::ConstDecl* AnalysisConstDecl(ASTNode* var, IR::SymbolList* syms);

	IR::FunctionDecl* AnalysisFunction(ASTNode* var, IR::SymbolList* syms);

	IR::Expr* AnalysisExprStmt(ASTNode* stmt, IR::SymbolList* syms);

	IR::VarDecl* AnalysisVarDecl(ASTNode* var, IR::SymbolList* syms);

	IR::ConstDecl::VType GetReturnValueType(ASTNode* var);

	int GetNumberValue(ASTNode* number);

	int EvalConstExpr(ASTNode* expr, IR::SymbolList* syms = nullptr);

	template<Parser::TokenType t>
	auto GetChild(ASTNode* ast)
	{
		for (auto& child : ast->tokenList)
			if (child->type == t)
				return child;
		return (ASTNode*) nullptr;
	}

	template<Parser::TokenType t>
	auto GetChilds(ASTNode* ast)
	{
		auto result = std::deque<ASTNode*>();
		for (auto& child : ast->tokenList)
			if (child->type == t)
				result.push_back(child);

		return result;
	}
}