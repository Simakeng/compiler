#pragma once
#include "Lex.h"
#include <deque>

namespace Compiler::Parser
{
	template<typename T>
	constexpr auto __cvt(const T& rhs)
	{
		return static_cast<const int>(rhs);
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
	
		Exp,
		ConstDecl,
		LvalAux,
		FuncRParamsNext,
		MulExpNext,
		AddExpNext,
		ConstExp,
		Decl,
		ArraySizeNum,
		MulExp,
		CompUnit,
		UnaryExp,
		VarOrFuncDeclBody,
		UnaryOp,
		FuncCall,
		FuncDeclBody,
		CodeBlock,
		Stmts,
		Stmt,
		FuncParamDecl,
		FuncParamDeclNext,
		ElseStmt,
		Cond,
		RelExpNext,
		VarInitValueNext,
		EqExp,
		ArraySizeDecl,
		LAndExp,
		ReturnVal,
		ConstInitVal,
		RelExp,
		Type,
		LOrExpNext,
		ArrayAcces,
		VarDeclbody,
		VarInitValue,
		PrimaryExp,
		VarOrFuncDecl,
		AddExp,
		EqExpNext,
		LvalAuxOrFuncCall,
		FuncRParams,
		AssignExpBody,
		VarDecl,
		LOrExp,
		LAndExpNext,
	
		Empty,
	};
	// ! Auto Generated Content end

	bool IsTerminalToken(TokenType type);
	
	struct ASTNode
	{
		TokenType type;
		std::any value;
		ASTNode* parent = nullptr;
		std::deque<ASTNode*> tokenList;
	};
	ASTNode* ParserTokens(const std::deque<Compiler::Lex::Token>& tokens);

	typedef void (*ProductionGenerationFunction)(ASTNode*, TokenType);
}