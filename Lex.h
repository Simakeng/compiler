#pragma once
#include <any>
namespace Compiler::Lex
{
	enum class TokenType
	{
		Plus,		// +
		Minus,		// -
		Multi,		// *
		Divid,		// /
		Remain,		// %
		Eq,			// ==
		Neq,		// !=
		Geq,		// >=
		Leq,		// <=
		And,		// &&
		Or,			// ||
		Assign,		// =
		Ge,			// >
		Le,			// <
		Not,		// !
		Comma,		// ,

		If,			// if
		Else,		// else
		While,		// while
		Break,		// break
		Return,		// return
		Const,		// const
		Continue,	// continue

		Void,		// void
		Int,		// int

		Pbs,		// (
		Pbe,		// )
		Sbs,		// [
		Sbe,		// ]
		Brs,		// {
		Bre,		// }

		Sep,		// ;

		End,

		Ident,
		Interger,
		String,
		blank,
		comment_h,
		comment_l_b,
		comment_l_e
	};
	
	
	

	struct Token
	{
		TokenType type;
		std::any value;

		int _line;
		int _start;
	};
}