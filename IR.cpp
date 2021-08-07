#include "IR.h"
#include "ASTUtils.h"
#include "Logger.h"
namespace Compiler::IR
{
	IRinfo Compiler::IR::AnalysisFromAST(Parser::ASTNode* ast)
	{
		auto info = IRinfo();
		auto& symList = info.syms;

		auto decls = AST::SearchNodeDecls(ast);
		for (auto& decl : decls)
		{
			Decl* d = nullptr;
			switch (AST::GetDeclType(decl))
			{
			case Decl::Type::Const: d = AST::AnalysisConstDecl(decl, &symList); break;
			case Decl::Type::Function: d = AST::AnalysisFunction(decl, &symList); break;
			case Decl::Type::Var:  d = AST::AnalysisVarDecl(decl, &symList); break;
			}
			symList.decls.push_back(d);
			symList.index[d->name] = d;
		}
		return info;
	}



	Decl* SymbolList::Index(const std::string& name)
	{
		auto search = this->index.find(name);
		if (search != this->index.end())
			return search->second;
		else if (this->parentList == nullptr)
			return nullptr;
		else return this->parentList->Index(name);
	}
	void SymbolList::AppendDecl(Decl* decl)
	{
		auto name = decl->name;
		auto search = this->index.find(name);
		if (search != this->index.end())
		{
			Console::Log("Variable redefinition of", name,Level::Info);
			return;
		}
		this->decls.push_back(decl);
		this->index[name] = decl;
	}
}
