#pragma once
#include "Parser.h"
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
namespace Compiler::IR
{
	struct SymbolList;

	struct Stmt
	{
		enum class Type
		{
			Decl,
			Expr,
			If,
			While,
			Continue,
			Break,
			CodeBlock,
			UNDEFINED
		} stype = Type::UNDEFINED;

		SymbolList* parentSymtable;
	};

	struct Operation
	{
		enum class Type
		{
			ADD, // +
			SUB, // -
			MUL, // *
			DIV, // /
			MOD, // %

			EQ,  // ==
			NEQ, // !=
			GE,  // >
			GEQ, // >=
			LE,  // <
			LEQ, // <=
			NOT, // !

			NEG, // -a

			AND,
			OR,

			FUNC_CALL,
			PARAM_REF, // declare param import
			DECL_VALUE,	// declare expr value
			ASSIGN_VALUE, // assign value to variable
			CONST_VALUE, // constant

			UNDEFINED

		} optype = Type::UNDEFINED;

		Operation* Opend1 = nullptr;
		Operation* Opend2 = nullptr;
	};

	struct IdentRefOperation : public Operation
	{
		std::string targetIdentName;
		Operation*& offop = Opend1;
	};
	struct ConstValueOperation : public Operation
	{
		int val;
	};

	struct AssignOperation : public Operation
	{
		std::string targetIdent;
		Operation*& offop = Opend1;
		Operation*& valop = Opend2;
	};

	struct Decl : public Stmt
	{
		enum class Type
		{
			Const,
			Var,
			Param,
			Function,
			UNDEFINED
		} dtype = Type::UNDEFINED;
		std::string name;
		Decl(Type _type) : dtype(_type) {};
		~Decl() = default;
	};

	struct ConstDecl : public Decl
	{
		enum class VType
		{
			VOID,
			INT,
			INTPTR,
			UNDEFINED
		} vtype = VType::UNDEFINED;
		std::deque<int> size;
		std::vector<int> initValue;

		ConstDecl() : Decl(Type::Const) {}
		ConstDecl(Type _) : Decl(_) {}


	};

	struct CodeBlock;

	struct Expr : public Stmt
	{
		enum class EType
		{
			Expr,
			Cond
		} etype = EType::Expr;
		std::deque<Operation*> ops;
	};

	struct InitExprs
	{
		std::deque <int> addr;
		Expr expr;
	};

	struct VarDecl : public ConstDecl
	{
		std::deque<InitExprs> initExprs;
		VarDecl() : ConstDecl(Type::Var) {}
	};

	struct SymbolList
	{
		std::deque<Decl*> decls;
		std::unordered_map<std::string, Decl*> index;
		SymbolList* parentSymList = nullptr;

		Decl* Index(const std::string& name);
		void AppendDecl(Decl* decl);
	};

	struct CodeBlock : public Stmt
	{
		std::deque<Stmt*> stmts;
		SymbolList symbs;
	};

	struct LogicCondNode : public Expr
	{
		std::deque<Expr*> evalList;
		enum class CType 
		{
			OR,
			AND,
			UNDEFINED,
		} ctype = CType::UNDEFINED;
	};

	struct IfElseStmt : public Stmt
	{
		LogicCondNode* cond;
		Stmt* success;
		Stmt* fail;
	};

	struct While : public Stmt
	{
		Expr* cond;
		CodeBlock* success;
	};

	

	struct FunctionDecl : public Decl
	{
		SymbolList params;
		ConstDecl::VType returnValueType;

		CodeBlock procedures;

		FunctionDecl() :Decl(Decl::Type::Function) {};
		~FunctionDecl() = default;
	};





	class IRinfo
	{
	private:
		SymbolList syms;
		std::deque<FunctionDecl*> func;
		IRinfo() = default;
	public:
		~IRinfo() = default;
		friend IRinfo AnalysisFromAST(Parser::ASTNode* ast);
	};

	IRinfo AnalysisFromAST(Parser::ASTNode* ast);
}