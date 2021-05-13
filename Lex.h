namespace Compiler::Lex
{
	enum class TokenType
	{
		Plus,		// +
		Minus,		// -
		Multi,		// *
		Divid,		// /
		Remain,		// %
		Assign,		// =
		Eq,			// ==
		Neq,		// !=
		Ge,			// >
		Le,			// <
		Geq,		// >=
		Leq,		// <=
		Not,		// !
		And,		// &&
		Or,			// ||
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

		Ident,
		Number, 
		
	};
}