#pragma once
#include <string>
#include <deque>
namespace Compiler::ASM
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
	
	struct Var
	{
		enum class Type
		{
			VOID,
			INT,
			INTPTR
		} type;
		std::string name;
		std::deque<int> size;
		int domain_id;
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


	class Function 
	{
		std::string name;
		std::deque<Var> params;
		Var::Type returnValueType;

		CodeBlock procedures;
	};


	class IR 
	{
	public:
		IR();
		~IR() = default;
	private:

	};
}