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

			JMP,
		} type;
		int Op1ID, Op2ID;
		int id;
	};

	struct Decl
	{
		enum class Type
		{
			Const,
			Var,
			Function
		} type;
		std::string name;
		Decl(Type _type) : type(_type) {};
		~Decl() = default;
	};

	struct Var : public Decl
	{
		enum class VType
		{
			VOID,
			INT,
			INTPTR
		} vtype;
		std::string name;
		std::deque<int> size;
		std::vector<int> initValue;

		Var() : Decl(Type::Var) {}
		Var(Type _) : Decl(_) {}
	};


	struct ConstDecl : public Var
	{
		ConstDecl() : Var(Type::Const) {}
	};


	class CodeBlock : public Stmt
	{
		std::deque<Var> localVariables;
		std::deque<Var> localConstants;
		CodeBlock* parentBlock = nullptr;
	};

	class Expr : public Stmt
	{
		std::deque<Operation> ops;
		CodeBlock* parentCB;
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
	};

	class Function : public Decl
	{
		std::string name;
		std::deque<Var> params;
		Var::Type returnValueType;

		CodeBlock procedures;
	};



	

	class IRinfo
	{
	private:
		SymbolList syms;
		std::deque<Function*> func;
		IRinfo() = default;
	public:
		~IRinfo() = default;
		friend IRinfo AnalysisFromAST(Parser::ASTNode* ast);
	};

	IRinfo AnalysisFromAST(Parser::ASTNode* ast);
}