#include "IR.h"
#include "ASTUtils.h"
namespace Compiler::IR
{
	IRinfo Compiler::IR::AnalysisFromAST(Parser::ASTNode* ast)
	{
		auto info = IRinfo();
		auto& symList = info.syms;

		auto decls = AST::SearchNodeDecls(ast);
		for (auto& decl : decls)
		{
			switch (AST::GetDeclType(decl))
			{
			case Decl::Type::Const:
			{
				auto d = AST::AnalysisVar(decl);
				symList.decls.push_back(d);
				symList.index[d->name] = d;
			}
			break;
			case Decl::Type::Function:
				break;
			case Decl::Type::Var:
				break;
			}
		}

		auto funcs = AST::SearchGlobalFunctions(ast);
		auto consts = AST::SearchGlobalConstants(ast);
		return info;
	}
}
