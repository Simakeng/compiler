#pragma once
#include "Lex.h"
#include <deque>
#include <sstream>

namespace Compiler::Parser
{
	template<typename T>
	constexpr auto __cvt(const T& rhs)
	{
		return static_cast<const int>(rhs);
	}

	const char* const __tstr(int rhs);

	template<typename T>
	constexpr auto __tstr(const T& rhs)
	{
		return __tstr(static_cast<const int>(rhs));
	}


	// ! Auto Generated Content Start
	enum class TokenType
	{
		Plus = __cvt(Compiler::Lex::TokenType::Plus),
		Minus = __cvt(Compiler::Lex::TokenType::Minus),
		Multi = __cvt(Compiler::Lex::TokenType::Multi),
		Divid = __cvt(Compiler::Lex::TokenType::Divid),
		Remain = __cvt(Compiler::Lex::TokenType::Remain),
		Eq = __cvt(Compiler::Lex::TokenType::Eq),
		Neq = __cvt(Compiler::Lex::TokenType::Neq),
		Geq = __cvt(Compiler::Lex::TokenType::Geq),
		Leq = __cvt(Compiler::Lex::TokenType::Leq),
		And = __cvt(Compiler::Lex::TokenType::And),
		Or = __cvt(Compiler::Lex::TokenType::Or),
		Assign = __cvt(Compiler::Lex::TokenType::Assign),
		Ge = __cvt(Compiler::Lex::TokenType::Ge),
		Le = __cvt(Compiler::Lex::TokenType::Le),
		Not = __cvt(Compiler::Lex::TokenType::Not),
		Comma = __cvt(Compiler::Lex::TokenType::Comma),
		If = __cvt(Compiler::Lex::TokenType::If),
		Else = __cvt(Compiler::Lex::TokenType::Else),
		While = __cvt(Compiler::Lex::TokenType::While),
		Break = __cvt(Compiler::Lex::TokenType::Break),
		Return = __cvt(Compiler::Lex::TokenType::Return),
		Const = __cvt(Compiler::Lex::TokenType::Const),
		Continue = __cvt(Compiler::Lex::TokenType::Continue),
		Void = __cvt(Compiler::Lex::TokenType::Void),
		Int = __cvt(Compiler::Lex::TokenType::Int),
		Pbs = __cvt(Compiler::Lex::TokenType::Pbs),
		Pbe = __cvt(Compiler::Lex::TokenType::Pbe),
		Sbs = __cvt(Compiler::Lex::TokenType::Sbs),
		Sbe = __cvt(Compiler::Lex::TokenType::Sbe),
		Brs = __cvt(Compiler::Lex::TokenType::Brs),
		Bre = __cvt(Compiler::Lex::TokenType::Bre),
		Sep = __cvt(Compiler::Lex::TokenType::Sep),
		End = __cvt(Compiler::Lex::TokenType::End),
		Ident = __cvt(Compiler::Lex::TokenType::Ident),
		Interger = __cvt(Compiler::Lex::TokenType::Interger),
	
		FuncRParams,
		LOrExpNext,
		ConstExp,
		VarDeclbody,
		VarInitValue,
		RelExp,
		FuncParamDecl,
		RelExpNext,
		ElseStmt,
		AddExpNext,
		EqExpNext,
		FuncDeclBody,
		ArrayAcces,
		FuncParamDeclNext,
		LvalAuxOrFuncCall,
		ConstInitVal,
		CodeBlock,
		Exp,
		UnaryExp,
		FuncRParamsNext,
		UnaryOp,
		VarDecl,
		MulExpNext,
		Stmts,
		CompUnit,
		Type,
		LAndExpNext,
		LOrExp,
		VarOrFuncDeclBody,
		ConstDecl,
		VarOrFuncDecl,
		ArraySizeDecl,
		FuncCall,
		PrimaryExp,
		ArraySizeNum,
		LAndExp,
		Stmt,
		VarInitValueNext,
		LvalAux,
		AssignExpBody,
		MulExp,
		ReturnVal,
		EqExp,
		Decl,
		AddExp,
		Cond,
	
		Empty,
	};
	// ! Auto Generated Content end

	
	struct ASTNode
	{
		TokenType type;
		std::any value;
		ASTNode* parent = nullptr;
		std::deque<ASTNode*> tokenList;
	};
	ASTNode* ParserTokens(const std::deque<Compiler::Lex::Token>& tokens);

	typedef void (*ProductionGenerationFunction)(ASTNode*, TokenType);

	std::string VisualizeAST(ASTNode* ast, std::string prefix = "", std::stringstream* ss = nullptr);

	void FreeNode(ASTNode* node);
}