#include "Parser.h"
#include "Logger.h"
#include <string>
#include <sstream>
using namespace std;

namespace Compiler::Parser
{
	ASTNode* CreateNode(TokenType type, ASTNode* parent = nullptr, std::any value = NULL)
	{
		auto r = new ASTNode;
		r->parent = parent;
		r->type = type;
		r->value = value;
		return r;
	}

	// ! Auto Generated Content Start
	const auto tokenCount = 82 ;
	int LL1Table[tokenCount][tokenCount];
	ProductionGenerationFunction prodRules[94];
	int InitLL1()
	{
		for (auto i = 0; i < tokenCount; i++)
			for (auto j = 0; j < tokenCount; j++)
				LL1Table[i][j] = 0;

		prodRules[0] = [](ASTNode* Node, TokenType inputToken) {
			Console::Log("Parser Token error when parsing Node",
				__tstr(Node->type),
				", get",__tstr(inputToken)
				, Level::Error);
			Console::SetExitCode(-1);
		};
		
		// CompUnit -> Decl CompUnit
		prodRules[1] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Decl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::CompUnit, parent));
		};

		// Select: 'int', 'void', 'const'
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::Int)] = 1;
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::Void)] = 1;
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::Const)] = 1;

		// CompUnit -> '$'
		prodRules[2] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::End, parent));
		};

		// Select: '$'
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::End)] = 2;

		// Decl -> ConstDecl
		prodRules[3] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ConstDecl, parent));
		};

		// Select: 'const'
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Const)] = 3;

		// Decl -> VarOrFuncDecl
		prodRules[4] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::VarOrFuncDecl, parent));
		};

		// Select: 'int', 'void'
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Int)] = 4;
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Void)] = 4;

		// ConstDecl -> 'const' Type Ident VarDeclbody
		prodRules[5] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Const, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Type, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclbody, parent));
		};

		// Select: 'const'
		LL1Table[__cvt(TokenType::ConstDecl)][__cvt(TokenType::Const)] = 5;

		// VarOrFuncDecl -> Type Ident VarOrFuncDeclBody
		prodRules[6] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Type, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarOrFuncDeclBody, parent));
		};

		// Select: 'int', 'void'
		LL1Table[__cvt(TokenType::VarOrFuncDecl)][__cvt(TokenType::Int)] = 6;
		LL1Table[__cvt(TokenType::VarOrFuncDecl)][__cvt(TokenType::Void)] = 6;

		// Type -> 'int'
		prodRules[7] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Int, parent));
		};

		// Select: 'int'
		LL1Table[__cvt(TokenType::Type)][__cvt(TokenType::Int)] = 7;

		// Type -> 'void'
		prodRules[8] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Void, parent));
		};

		// Select: 'void'
		LL1Table[__cvt(TokenType::Type)][__cvt(TokenType::Void)] = 8;

		// VarOrFuncDeclBody -> VarDeclbody
		prodRules[9] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclbody, parent));
		};

		// Select: '=', '[', ';'
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Assign)] = 9;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Sbs)] = 9;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Sep)] = 9;

		// VarOrFuncDeclBody -> FuncDeclBody
		prodRules[10] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::FuncDeclBody, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Pbs)] = 10;

		// VarDeclbody -> ArraySizeDecl VarDecl
		prodRules[11] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDecl, parent));
		};

		// Select: '=', '[', ';'
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Assign)] = 11;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Sbs)] = 11;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Sep)] = 11;

		// ArraySizeDecl -> '[' ArraySizeNum ']' ArraySizeDecl
		prodRules[12] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Sbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeNum, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
		};

		// Select: '['
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Sbs)] = 12;

		// ArraySizeDecl -> ε
		prodRules[13] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '=', Ident, ';'
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Assign)] = 13;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Ident)] = 13;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Sep)] = 13;

		// ArraySizeNum -> ε
		prodRules[14] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ']'
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Sbe)] = 14;

		// ArraySizeNum -> ConstExp
		prodRules[15] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ConstExp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Minus)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Pbs)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Not)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Plus)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Interger)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Ident)] = 15;

		// VarDecl -> ';'
		prodRules[16] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: ';'
		LL1Table[__cvt(TokenType::VarDecl)][__cvt(TokenType::Sep)] = 16;

		// VarDecl -> '=' VarInitValue ';'
		prodRules[17] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Assign, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: '='
		LL1Table[__cvt(TokenType::VarDecl)][__cvt(TokenType::Assign)] = 17;

		// VarInitValue -> ConstInitVal
		prodRules[18] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ConstInitVal, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Minus)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Pbs)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Not)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Plus)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Interger)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Ident)] = 18;

		// VarInitValue -> '{' VarInitValue VarInitValueNext '}'
		prodRules[19] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Brs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValueNext, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Bre, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Brs)] = 19;

		// VarInitValueNext -> ',' VarInitValueNext
		prodRules[20] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValueNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Comma)] = 20;

		// VarInitValueNext -> VarInitValue
		prodRules[21] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValue, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident, '{'
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Minus)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Pbs)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Not)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Plus)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Interger)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Ident)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Brs)] = 21;

		// VarInitValueNext -> ε
		prodRules[22] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '}'
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Bre)] = 22;

		// ConstInitVal -> ConstExp
		prodRules[23] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ConstExp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Minus)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Pbs)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Not)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Plus)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Interger)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Ident)] = 23;

		// FuncDeclBody -> '(' FuncParamDecl FuncParamDeclNext ')' CodeBlock
		prodRules[24] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDeclNext, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::CodeBlock, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::FuncDeclBody)][__cvt(TokenType::Pbs)] = 24;

		// FuncParamDecl -> ε
		prodRules[25] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: 'int', ',', ')'
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Int)] = 25;
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Comma)] = 25;
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Pbe)] = 25;

		// FuncParamDecl -> 'int' ArraySizeDecl Ident
		prodRules[26] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Int, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
		};

		// Select: 'int'
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Int)] = 26;

		// FuncParamDeclNext -> ε
		prodRules[27] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Pbe)] = 27;

		// FuncParamDeclNext -> ',' FuncParamDeclNext
		prodRules[28] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDeclNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Comma)] = 28;

		// FuncParamDeclNext -> FuncParamDecl
		prodRules[29] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDecl, parent));
		};

		// Select: 'int', ')'
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Int)] = 29;
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Pbe)] = 29;

		// CodeBlock -> '{' Stmts '}'
		prodRules[30] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Brs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmts, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Bre, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::CodeBlock)][__cvt(TokenType::Brs)] = 30;

		// Stmts -> Stmt Stmts
		prodRules[31] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmts, parent));
		};

		// Select: 'continue', 'break', '-', 'if', '(', '!', '+', 'int', Number, Ident, 'void', 'const', '{', 'while', 'return'
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Continue)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Break)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Minus)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::If)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Pbs)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Not)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Plus)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Int)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Interger)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Ident)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Void)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Const)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Brs)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::While)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Return)] = 31;

		// Stmts -> ε
		prodRules[32] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '}'
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Bre)] = 32;

		// Stmt -> Decl
		prodRules[33] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Decl, parent));
		};

		// Select: 'int', 'void', 'const'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Int)] = 33;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Void)] = 33;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Const)] = 33;

		// Stmt -> Exp ';'
		prodRules[34] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Minus)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Pbs)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Not)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Plus)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Interger)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Ident)] = 34;

		// Stmt -> CodeBlock
		prodRules[35] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::CodeBlock, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Brs)] = 35;

		// Stmt -> 'if' '(' Cond ')' Stmt ElseStmt
		prodRules[36] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::If, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Cond, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ElseStmt, parent));
		};

		// Select: 'if'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::If)] = 36;

		// Stmt -> 'while' '(' Cond ')' Stmt
		prodRules[37] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::While, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Cond, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
		};

		// Select: 'while'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::While)] = 37;

		// Stmt -> 'break' ';'
		prodRules[38] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Break, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'break'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Break)] = 38;

		// Stmt -> 'continue' ';'
		prodRules[39] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Continue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'continue'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Continue)] = 39;

		// Stmt -> 'return' ReturnVal ';'
		prodRules[40] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Return, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ReturnVal, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'return'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Return)] = 40;

		// ReturnVal -> ε
		prodRules[41] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ';'
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Sep)] = 41;

		// ReturnVal -> Exp
		prodRules[42] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Minus)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Pbs)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Not)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Plus)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Interger)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Ident)] = 42;

		// ElseStmt -> 'else' Stmt
		prodRules[43] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Else, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
		};

		// Select: 'else'
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Else)] = 43;

		// ElseStmt -> ε
		prodRules[44] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: 'continue', 'break', Number, '-', 'if', '(', '!', '+', 'else', 'int', Ident, 'void', 'const', '{', 'while', 'return'
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Continue)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Break)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Interger)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Minus)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::If)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Pbs)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Not)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Plus)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Else)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Int)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Ident)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Void)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Const)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Brs)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::While)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Return)] = 44;

		// Exp -> AddExp AssignExpBody
		prodRules[45] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AssignExpBody, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Minus)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Pbs)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Not)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Plus)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Interger)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Ident)] = 45;

		// ConstExp -> AddExp
		prodRules[46] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Minus)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Pbs)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Not)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Plus)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Interger)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Ident)] = 46;

		// AssignExpBody -> '=' AddExp
		prodRules[47] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Assign, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
		};

		// Select: '='
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Assign)] = 47;

		// AssignExpBody -> ε
		prodRules[48] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ']', '-', ',', '(', '!', '+', Number, Ident, ')', ';'
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Sbe)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Minus)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Comma)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Pbs)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Not)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Plus)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Interger)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Ident)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Pbe)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Sep)] = 48;

		// Cond -> LOrExp
		prodRules[49] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LOrExp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Minus)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Pbs)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Not)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Plus)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Interger)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Ident)] = 49;

		// ArrayAcces -> '[' Exp ']' ArrayAcces
		prodRules[50] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Sbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArrayAcces, parent));
		};

		// Select: '['
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sbs)] = 50;

		// ArrayAcces -> ε
		prodRules[51] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '=', '!=', '-', '<', '==', '(', '>', '{', '%', ',', '!', '+', Number, '}', Ident, ')', ']', '>=', '/', '&&', '||', '<=', '*', ';'
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Assign)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Neq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Minus)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Le)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Eq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Pbs)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Ge)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Brs)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Remain)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Comma)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Not)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Plus)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Interger)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Bre)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Ident)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Pbe)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sbe)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Geq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Divid)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::And)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Or)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Leq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Multi)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sep)] = 51;

		// PrimaryExp -> '(' Exp ')'
		prodRules[52] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::PrimaryExp)][__cvt(TokenType::Pbs)] = 52;

		// PrimaryExp -> Number
		prodRules[53] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Interger, parent));
		};

		// Select: Number
		LL1Table[__cvt(TokenType::PrimaryExp)][__cvt(TokenType::Interger)] = 53;

		// LvalAux -> ArrayAcces
		prodRules[54] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ArrayAcces, parent));
		};

		// Select: '=', '!=', '-', '<', '==', '(', '*', '>', '{', '%', ',', '!', '+', Number, Ident, '}', ')', ']', '>=', '/', '&&', '||', '<=', '[', ';'
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Assign)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Neq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Minus)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Le)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Eq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Pbs)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Multi)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Ge)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Brs)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Remain)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Comma)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Not)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Plus)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Interger)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Ident)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Bre)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Pbe)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sbe)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Geq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Divid)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::And)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Or)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Leq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sbs)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sep)] = 54;

		// FuncCall -> '(' FuncRParams FuncRParamsNext ')'
		prodRules[55] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParams, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParamsNext, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::FuncCall)][__cvt(TokenType::Pbs)] = 55;

		// LvalAuxOrFuncCall -> LvalAux
		prodRules[56] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LvalAux, parent));
		};

		// Select: '=', '!=', '-', '<', '==', '(', '*', '>', '{', '%', ',', '!', '+', Number, '}', Ident, ')', ']', '>=', '/', '&&', '||', '<=', '[', ';'
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Assign)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Neq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Minus)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Le)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Eq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbs)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Multi)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Ge)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Brs)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Remain)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Comma)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Not)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Plus)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Interger)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Bre)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Ident)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbe)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sbe)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Geq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Divid)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::And)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Or)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Leq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sbs)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sep)] = 56;

		// LvalAuxOrFuncCall -> FuncCall
		prodRules[57] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::FuncCall, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbs)] = 57;

		// UnaryExp -> PrimaryExp
		prodRules[58] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::PrimaryExp, parent));
		};

		// Select: Number, '('
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Interger)] = 58;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Pbs)] = 58;

		// UnaryExp -> Ident LvalAuxOrFuncCall
		prodRules[59] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LvalAuxOrFuncCall, parent));
		};

		// Select: Ident
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Ident)] = 59;

		// UnaryExp -> UnaryOp UnaryExp
		prodRules[60] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::UnaryOp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
		};

		// Select: '+', '!', '-'
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Plus)] = 60;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Not)] = 60;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Minus)] = 60;

		// FuncRParams -> ε
		prodRules[61] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '-', ',', '(', '!', '+', Number, Ident, ')'
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Minus)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Comma)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbs)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Not)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Plus)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Interger)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Ident)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbe)] = 61;

		// FuncRParams -> Exp
		prodRules[62] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Minus)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbs)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Not)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Plus)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Interger)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Ident)] = 62;

		// FuncRParamsNext -> ε
		prodRules[63] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Pbe)] = 63;

		// FuncRParamsNext -> ',' FuncRParamsNext
		prodRules[64] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParamsNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Comma)] = 64;

		// FuncRParamsNext -> Exp
		prodRules[65] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Minus)] = 65;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Pbs)] = 65;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Not)] = 65;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Plus)] = 65;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Interger)] = 65;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Ident)] = 65;

		// UnaryOp -> '+'
		prodRules[66] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Plus, parent));
		};

		// Select: '+'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Plus)] = 66;

		// UnaryOp -> '-'
		prodRules[67] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Minus, parent));
		};

		// Select: '-'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Minus)] = 67;

		// UnaryOp -> '!'
		prodRules[68] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Not, parent));
		};

		// Select: '!'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Not)] = 68;

		// MulExp -> UnaryExp MulExpNext
		prodRules[69] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Minus)] = 69;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Pbs)] = 69;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Not)] = 69;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Plus)] = 69;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Interger)] = 69;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Ident)] = 69;

		// MulExpNext -> ε
		prodRules[70] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '=', '!=', '-', '<', '==', '(', '>', '{', '%', ',', '!', '+', Number, Ident, '}', ')', ']', '>=', '/', '&&', '||', '<=', '*', ';'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Assign)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Neq)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Minus)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Le)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Eq)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Pbs)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Ge)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Brs)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Remain)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Comma)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Not)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Plus)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Interger)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Ident)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Bre)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Pbe)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Sbe)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Geq)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Divid)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::And)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Or)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Leq)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Multi)] = 70;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Sep)] = 70;

		// MulExpNext -> '*' MulExp MulExpNext
		prodRules[71] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Multi, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '*'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Multi)] = 71;

		// MulExpNext -> '/' MulExp MulExpNext
		prodRules[72] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Divid, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '/'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Divid)] = 72;

		// MulExpNext -> '%' MulExp MulExpNext
		prodRules[73] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Remain, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '%'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Remain)] = 73;

		// AddExp -> MulExp AddExpNext
		prodRules[74] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Minus)] = 74;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Pbs)] = 74;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Not)] = 74;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Plus)] = 74;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Interger)] = 74;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Ident)] = 74;

		// AddExpNext -> ε
		prodRules[75] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '=', '!=', '-', '<', '==', '(', '>', '{', ',', '!', '+', Number, '}', Ident, ')', ']', '>=', '&&', '||', '<=', ';'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Assign)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Neq)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Minus)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Le)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Eq)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Pbs)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Ge)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Brs)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Comma)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Not)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Plus)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Interger)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Bre)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Ident)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Pbe)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Sbe)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Geq)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::And)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Or)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Leq)] = 75;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Sep)] = 75;

		// AddExpNext -> '+' AddExp AddExpNext
		prodRules[76] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Plus, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '+'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Plus)] = 76;

		// AddExpNext -> '-' AddExp AddExpNext
		prodRules[77] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Minus, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '-'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Minus)] = 77;

		// RelExp -> AddExp RelExpNext
		prodRules[78] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Minus)] = 78;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Pbs)] = 78;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Not)] = 78;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Plus)] = 78;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Interger)] = 78;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Ident)] = 78;

		// RelExpNext -> ε
		prodRules[79] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '||', '>=', '!=', '<=', '<', '==', '>', ')', '&&'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Or)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Geq)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Neq)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Leq)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Le)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Eq)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Ge)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Pbe)] = 79;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::And)] = 79;

		// RelExpNext -> '<' RelExp RelExpNext
		prodRules[80] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Le, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '<'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Le)] = 80;

		// RelExpNext -> '>' RelExp RelExpNext
		prodRules[81] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Ge, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '>'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Ge)] = 81;

		// RelExpNext -> '<=' RelExp RelExpNext
		prodRules[82] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Leq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '<='
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Leq)] = 82;

		// RelExpNext -> '>=' RelExp RelExpNext
		prodRules[83] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Geq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '>='
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Geq)] = 83;

		// EqExp -> RelExp EqExpNext
		prodRules[84] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Minus)] = 84;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Pbs)] = 84;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Not)] = 84;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Plus)] = 84;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Interger)] = 84;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Ident)] = 84;

		// EqExpNext -> ε
		prodRules[85] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '||', '!=', '==', ')', '&&'
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Or)] = 85;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Neq)] = 85;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Eq)] = 85;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Pbe)] = 85;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::And)] = 85;

		// EqExpNext -> '==' EqExp EqExpNext
		prodRules[86] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Eq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '=='
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Eq)] = 86;

		// EqExpNext -> '!=' EqExp EqExpNext
		prodRules[87] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Neq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '!='
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Neq)] = 87;

		// LAndExp -> EqExp LAndExpNext
		prodRules[88] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExpNext, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Minus)] = 88;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Pbs)] = 88;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Not)] = 88;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Plus)] = 88;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Interger)] = 88;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Ident)] = 88;

		// LAndExpNext -> ε
		prodRules[89] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '||', ')'
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::Or)] = 89;
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::Pbe)] = 89;

		// LAndExpNext -> '&&' EqExp LAndExpNext
		prodRules[90] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::And, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExpNext, parent));
		};

		// Select: '&&'
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::And)] = 90;

		// LOrExp -> LAndExp LOrExpNext
		prodRules[91] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LAndExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LOrExpNext, parent));
		};

		// Select: '-', '(', '!', '+', Number, Ident
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Minus)] = 91;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Pbs)] = 91;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Not)] = 91;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Plus)] = 91;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Interger)] = 91;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Ident)] = 91;

		// LOrExpNext -> '||' LAndExp LOrExpNext
		prodRules[92] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Or, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LOrExpNext, parent));
		};

		// Select: '||'
		LL1Table[__cvt(TokenType::LOrExpNext)][__cvt(TokenType::Or)] = 92;

		// LOrExpNext -> ε
		prodRules[93] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::LOrExpNext)][__cvt(TokenType::Pbe)] = 93;
		
		return -1;
	}
	int _ = InitLL1();
	
	const char* const __tstr(int rhs)
	{
		switch(rhs)
		{
		case __cvt(TokenType::Plus): return "['+']";
		case __cvt(TokenType::Minus): return "['-']";
		case __cvt(TokenType::Multi): return "['*']";
		case __cvt(TokenType::Divid): return "['/']";
		case __cvt(TokenType::Remain): return "['%']";
		case __cvt(TokenType::Eq): return "['==']";
		case __cvt(TokenType::Neq): return "['!=']";
		case __cvt(TokenType::Geq): return "['>=']";
		case __cvt(TokenType::Leq): return "['<=']";
		case __cvt(TokenType::And): return "['&&']";
		case __cvt(TokenType::Or): return "['||']";
		case __cvt(TokenType::Assign): return "['=']";
		case __cvt(TokenType::Ge): return "['>']";
		case __cvt(TokenType::Le): return "['<']";
		case __cvt(TokenType::Not): return "['!']";
		case __cvt(TokenType::Comma): return "[',']";
		case __cvt(TokenType::If): return "['if']";
		case __cvt(TokenType::Else): return "['else']";
		case __cvt(TokenType::While): return "['while']";
		case __cvt(TokenType::Break): return "['break']";
		case __cvt(TokenType::Return): return "['return']";
		case __cvt(TokenType::Const): return "['const']";
		case __cvt(TokenType::Continue): return "['continue']";
		case __cvt(TokenType::Void): return "['void']";
		case __cvt(TokenType::Int): return "['int']";
		case __cvt(TokenType::Pbs): return "['(']";
		case __cvt(TokenType::Pbe): return "[')']";
		case __cvt(TokenType::Sbs): return "['[']";
		case __cvt(TokenType::Sbe): return "[']']";
		case __cvt(TokenType::Brs): return "['{']";
		case __cvt(TokenType::Bre): return "['}']";
		case __cvt(TokenType::Sep): return "[';']";
		case __cvt(TokenType::End): return "['$']";
		case __cvt(TokenType::Ident): return "[Ident]";
		case __cvt(TokenType::Interger): return "[Number]";
		
		case __cvt(TokenType::FuncRParams): return "[FuncRParams]";
		case __cvt(TokenType::LOrExpNext): return "[LOrExpNext]";
		case __cvt(TokenType::ConstExp): return "[ConstExp]";
		case __cvt(TokenType::VarDeclbody): return "[VarDeclbody]";
		case __cvt(TokenType::VarInitValue): return "[VarInitValue]";
		case __cvt(TokenType::RelExp): return "[RelExp]";
		case __cvt(TokenType::FuncParamDecl): return "[FuncParamDecl]";
		case __cvt(TokenType::RelExpNext): return "[RelExpNext]";
		case __cvt(TokenType::ElseStmt): return "[ElseStmt]";
		case __cvt(TokenType::AddExpNext): return "[AddExpNext]";
		case __cvt(TokenType::EqExpNext): return "[EqExpNext]";
		case __cvt(TokenType::FuncDeclBody): return "[FuncDeclBody]";
		case __cvt(TokenType::ArrayAcces): return "[ArrayAcces]";
		case __cvt(TokenType::FuncParamDeclNext): return "[FuncParamDeclNext]";
		case __cvt(TokenType::LvalAuxOrFuncCall): return "[LvalAuxOrFuncCall]";
		case __cvt(TokenType::ConstInitVal): return "[ConstInitVal]";
		case __cvt(TokenType::CodeBlock): return "[CodeBlock]";
		case __cvt(TokenType::Exp): return "[Exp]";
		case __cvt(TokenType::UnaryExp): return "[UnaryExp]";
		case __cvt(TokenType::FuncRParamsNext): return "[FuncRParamsNext]";
		case __cvt(TokenType::UnaryOp): return "[UnaryOp]";
		case __cvt(TokenType::VarDecl): return "[VarDecl]";
		case __cvt(TokenType::MulExpNext): return "[MulExpNext]";
		case __cvt(TokenType::Stmts): return "[Stmts]";
		case __cvt(TokenType::CompUnit): return "[CompUnit]";
		case __cvt(TokenType::Type): return "[Type]";
		case __cvt(TokenType::LAndExpNext): return "[LAndExpNext]";
		case __cvt(TokenType::LOrExp): return "[LOrExp]";
		case __cvt(TokenType::VarOrFuncDeclBody): return "[VarOrFuncDeclBody]";
		case __cvt(TokenType::ConstDecl): return "[ConstDecl]";
		case __cvt(TokenType::VarOrFuncDecl): return "[VarOrFuncDecl]";
		case __cvt(TokenType::ArraySizeDecl): return "[ArraySizeDecl]";
		case __cvt(TokenType::FuncCall): return "[FuncCall]";
		case __cvt(TokenType::PrimaryExp): return "[PrimaryExp]";
		case __cvt(TokenType::ArraySizeNum): return "[ArraySizeNum]";
		case __cvt(TokenType::LAndExp): return "[LAndExp]";
		case __cvt(TokenType::Stmt): return "[Stmt]";
		case __cvt(TokenType::VarInitValueNext): return "[VarInitValueNext]";
		case __cvt(TokenType::LvalAux): return "[LvalAux]";
		case __cvt(TokenType::AssignExpBody): return "[AssignExpBody]";
		case __cvt(TokenType::MulExp): return "[MulExp]";
		case __cvt(TokenType::ReturnVal): return "[ReturnVal]";
		case __cvt(TokenType::EqExp): return "[EqExp]";
		case __cvt(TokenType::Decl): return "[Decl]";
		case __cvt(TokenType::AddExp): return "[AddExp]";
		case __cvt(TokenType::Cond): return "[Cond]";
		case __cvt(TokenType::Empty): return u8"[ε]";
		default:
			return "[Unknown]";
		}
	}
    

	// ! Auto Generated Content end


	void FreeNode(ASTNode* node)
	{
		for (auto& child : node->tokenList)
			FreeNode(child);
		delete node;
	}
	// VarOrFuncDecl -> Type Ident VarOrFuncDeclBody

	void Magic(ASTNode* targit_node)
	{
		targit_node->tokenList.push_back(CreateNode(TokenType::Type, targit_node));
		targit_node->tokenList.push_back(CreateNode(TokenType::Ident, targit_node));
		targit_node->tokenList.push_back(CreateNode(TokenType::VarOrFuncDeclBody, targit_node));

	}

	void MatchTokensForNode(deque<Lex::Token>& tokenList, Lex::Token& inputToken, ASTNode* node)
	{
		auto nodeType = node->type;

		prodRules[LL1Table[__cvt(nodeType)][__cvt(inputToken.type)]](node, static_cast<TokenType>(inputToken.type));

		for (auto& subnode : node->tokenList)
		{
			// 匹配到终结符
			if (subnode->type == static_cast<TokenType>(inputToken.type))
			{
				subnode->value = inputToken.value;
				tokenList.pop_front();
				if (not tokenList.empty())
					inputToken = tokenList.front();
			}
			else
			{
				if (subnode->type != TokenType::Empty)
					MatchTokensForNode(tokenList, inputToken, subnode);
			}
		}
	}

	ASTNode* ParserTokens(const std::deque<Compiler::Lex::Token>& tokens)
	{
		auto inputTokens = tokens;

		ASTNode* compUnit = CreateNode(TokenType::CompUnit);
		auto inputToken = inputTokens.front();

		MatchTokensForNode(inputTokens, inputToken, compUnit);

		return compUnit;
	}
	/*
	* ├─bin
	* │ └─x86
	* │   └─Debug
	* ├─grammar
	* ├─obj
	* │  └─x86
	* │      └─Debug
	* │          └─compiler.tlog
	* └─test
	*/
	string VisualizeAST(ASTNode* ast, string prefix, stringstream* ss)
	{
		stringstream* mss = ss;
		if (mss == nullptr)
		{
			mss = new stringstream();

			*mss << __tstr(ast->type) << "\n";
		}

		for (auto it = ast->tokenList.begin(); it != ast->tokenList.end(); ++it)
		{
			const char* brs = it + 1 == ast->tokenList.end() ? u8"└─\0" : u8"├─\0";
			string npf = prefix + (it + 1 == ast->tokenList.end() ? "  " : u8"│ \0");
			*mss << prefix << brs << __tstr((*it)->type) << "\n";
			VisualizeAST(*it, npf, mss);
		}




		if (ss == nullptr)
		{
			string res = mss->str();
			delete mss;
			return res;
		}

		return "";
	}


}
