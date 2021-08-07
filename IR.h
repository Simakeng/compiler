#pragma once
#include "Parser.h"
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
namespace Compiler::IR
{
	class IR;

	struct Stmt
	{
		enum class Type
		{
			Expr,
			If,
			While,
			Continue,
			Break,
			CodeBlock
		} type;

		IR* parentIR;
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

			AND,
			OR,

			FUNC_CALL,
			DECL_IMPORT, // declare param import
			DECL_VALUE,	// declare expr value
			SET_VALUE, // assign value to variable

		} type;
		Operation* Opend1 = nullptr;
		Operation* Opend2 = nullptr;
	};

	struct Decl
	{
		enum class Type
		{
			Const,
			Var,
			Param,
			Function
		} type;
		std::string name;
		Decl(Type _type) : type(_type) {};
		~Decl() = default;
	};
	struct ConstDecl : public Decl
	{
		enum class VType
		{
			VOID,
			INT,
			INTPTR
		} vtype;
		std::deque<int> size;
		std::vector<int> initValue;

		ConstDecl() : Decl(Type::Const) {}
		ConstDecl(Type _) : Decl(_) {}


	};

	class CodeBlock;

	class Expr : public Stmt
	{
		
		std::deque<Operation> ops;
		CodeBlock* parentCB;
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

	class CodeBlock : public Stmt
	{
		std::deque<VarDecl> localVariables;
		std::deque<VarDecl> localConstants;
		CodeBlock* parentBlock = nullptr;
	};


	class If : public Stmt
	{
		Expr* cond;
		CodeBlock* success;
		CodeBlock* fail;
	};

	class While : public Stmt
	{
		Expr* cond;
		CodeBlock* success;
	};

	struct SymbolList
	{
		std::deque<Decl*> decls;
		std::unordered_map<std::string, Decl*> index;
		SymbolList* parentList = nullptr;

		Decl* Index(const std::string& name);
		void AppendDecl(Decl* decl);
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