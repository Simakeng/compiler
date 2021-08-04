#include "Parser.h"
#include "Logger.h"
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
	ProductionGenerationFunction prodRules[95];
	int InitLL1()
	{
		for (auto i = 0; i < tokenCount; i++)
			for (auto j = 0; j < tokenCount; j++)
				LL1Table[i][j] = 0;

		prodRules[0] = [](ASTNode* Node, TokenType inputToken) {
			Console::Log("Expecting", "but get", Level::Error);
		};
		
		// CompUnit -> Decl CompUnit
		prodRules[1] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Decl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::CompUnit, parent));
		};

		// Select: 'const', 'int', 'void'
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::Const)] = 1;
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::Int)] = 1;
		LL1Table[__cvt(TokenType::CompUnit)][__cvt(TokenType::Void)] = 1;

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

		// Select: 'void', 'int'
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Void)] = 4;
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Int)] = 4;

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

		// Select: ';', '=', '['
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Sep)] = 9;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Assign)] = 9;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Sbs)] = 9;

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

		// Select: ';', '=', '['
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Sep)] = 11;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Assign)] = 11;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Sbs)] = 11;

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

		// Select: ';', Ident, '='
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Sep)] = 13;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Ident)] = 13;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Assign)] = 13;

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

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Ident)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Plus)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Pbs)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Interger)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Minus)] = 15;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Not)] = 15;

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

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Ident)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Plus)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Pbs)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Interger)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Minus)] = 18;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Not)] = 18;

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

		// Select: Ident, '+', '{', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Ident)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Plus)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Brs)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Pbs)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Interger)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Minus)] = 21;
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Not)] = 21;

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

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Ident)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Plus)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Pbs)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Interger)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Minus)] = 23;
		LL1Table[__cvt(TokenType::ConstInitVal)][__cvt(TokenType::Not)] = 23;

		// ConstExp -> Exp
		prodRules[24] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Ident)] = 24;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Plus)] = 24;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Pbs)] = 24;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Interger)] = 24;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Minus)] = 24;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Not)] = 24;

		// FuncDeclBody -> '(' FuncParamDecl FuncParamDeclNext ')' CodeBlock
		prodRules[25] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDeclNext, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::CodeBlock, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::FuncDeclBody)][__cvt(TokenType::Pbs)] = 25;

		// FuncParamDecl -> ε
		prodRules[26] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ',', 'int', ')'
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Comma)] = 26;
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Int)] = 26;
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Pbe)] = 26;

		// FuncParamDecl -> 'int' ArraySizeDecl Ident
		prodRules[27] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Int, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
		};

		// Select: 'int'
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Int)] = 27;

		// FuncParamDeclNext -> ε
		prodRules[28] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Pbe)] = 28;

		// FuncParamDeclNext -> ',' FuncParamDeclNext
		prodRules[29] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDeclNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Comma)] = 29;

		// FuncParamDeclNext -> FuncParamDecl
		prodRules[30] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDecl, parent));
		};

		// Select: 'int', ')'
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Int)] = 30;
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Pbe)] = 30;

		// CodeBlock -> '{' Stmts '}'
		prodRules[31] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Brs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmts, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Bre, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::CodeBlock)][__cvt(TokenType::Brs)] = 31;

		// Stmts -> Stmt Stmts
		prodRules[32] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmts, parent));
		};

		// Select: 'const', Ident, '+', '{', 'void', '(', 'if', 'break', Number, '-', 'continue', 'return', '!', 'int', 'while'
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Const)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Ident)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Plus)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Brs)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Void)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Pbs)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::If)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Break)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Interger)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Minus)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Continue)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Return)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Not)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Int)] = 32;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::While)] = 32;

		// Stmts -> ε
		prodRules[33] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '}'
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Bre)] = 33;

		// Stmt -> Decl
		prodRules[34] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Decl, parent));
		};

		// Select: 'const', 'int', 'void'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Const)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Int)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Void)] = 34;

		// Stmt -> Exp ';'
		prodRules[35] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Ident)] = 35;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Plus)] = 35;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Pbs)] = 35;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Interger)] = 35;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Minus)] = 35;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Not)] = 35;

		// Stmt -> CodeBlock
		prodRules[36] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::CodeBlock, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Brs)] = 36;

		// Stmt -> 'if' '(' Cond ')' Stmt ElseStmt
		prodRules[37] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::If, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Cond, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ElseStmt, parent));
		};

		// Select: 'if'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::If)] = 37;

		// Stmt -> 'while' '(' Cond ')' Stmt
		prodRules[38] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::While, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Cond, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
		};

		// Select: 'while'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::While)] = 38;

		// Stmt -> 'break' ';'
		prodRules[39] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Break, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'break'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Break)] = 39;

		// Stmt -> 'continue' ';'
		prodRules[40] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Continue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'continue'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Continue)] = 40;

		// Stmt -> 'return' ReturnVal ';'
		prodRules[41] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Return, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ReturnVal, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'return'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Return)] = 41;

		// ReturnVal -> ε
		prodRules[42] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ';'
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Sep)] = 42;

		// ReturnVal -> Exp
		prodRules[43] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Ident)] = 43;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Plus)] = 43;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Pbs)] = 43;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Interger)] = 43;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Minus)] = 43;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Not)] = 43;

		// ElseStmt -> 'else' Stmt
		prodRules[44] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Else, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
		};

		// Select: 'else'
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Else)] = 44;

		// ElseStmt -> ε
		prodRules[45] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: 'const', Ident, 'else', '+', 'void', '{', '(', 'if', 'break', Number, '-', 'continue', 'return', '!', 'int', 'while'
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Const)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Ident)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Else)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Plus)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Void)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Brs)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Pbs)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::If)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Break)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Interger)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Minus)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Continue)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Return)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Not)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Int)] = 45;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::While)] = 45;

		// Exp -> AddExp AssignExpBody
		prodRules[46] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AssignExpBody, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Ident)] = 46;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Plus)] = 46;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Pbs)] = 46;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Interger)] = 46;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Minus)] = 46;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Not)] = 46;

		// ConstExp -> AddExp
		prodRules[47] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Ident)] = 47;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Plus)] = 47;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Pbs)] = 47;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Interger)] = 47;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Minus)] = 47;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Not)] = 47;

		// AssignExpBody -> '=' AddExp
		prodRules[48] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Assign, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
		};

		// Select: '='
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Assign)] = 48;

		// AssignExpBody -> ε
		prodRules[49] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ',', Ident, '+', '{', '(', Number, '-', '!', ']', ';', '}', ')'
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Comma)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Ident)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Plus)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Brs)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Pbs)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Interger)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Minus)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Not)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Sbe)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Sep)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Bre)] = 49;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Pbe)] = 49;

		// Cond -> LOrExp
		prodRules[50] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LOrExp, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Ident)] = 50;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Plus)] = 50;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Pbs)] = 50;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Interger)] = 50;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Minus)] = 50;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Not)] = 50;

		// ArrayAcces -> '[' Exp ']' ArrayAcces
		prodRules[51] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Sbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArrayAcces, parent));
		};

		// Select: '['
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sbs)] = 51;

		// ArrayAcces -> ε
		prodRules[52] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '-', '=', '==', ']', '}', '!=', '+', '{', '>=', '(', '/', '&&', '||', '*', ')', Ident, Number, '!', '>', ',', '<=', '<', '%', ';'
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Minus)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Assign)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Eq)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sbe)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Bre)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Neq)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Plus)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Brs)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Geq)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Pbs)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Divid)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::And)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Or)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Multi)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Pbe)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Ident)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Interger)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Not)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Ge)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Comma)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Leq)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Le)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Remain)] = 52;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sep)] = 52;

		// PrimaryExp -> '(' Exp ')'
		prodRules[53] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::PrimaryExp)][__cvt(TokenType::Pbs)] = 53;

		// PrimaryExp -> Number
		prodRules[54] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Interger, parent));
		};

		// Select: Number
		LL1Table[__cvt(TokenType::PrimaryExp)][__cvt(TokenType::Interger)] = 54;

		// LvalAux -> ArrayAcces
		prodRules[55] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ArrayAcces, parent));
		};

		// Select: '-', '=', '==', ']', '}', '!=', '+', '{', '>=', '(', '/', '&&', '||', '*', '[', ')', Ident, Number, '!', '>', ',', '<=', '<', '%', ';'
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Minus)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Assign)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Eq)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sbe)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Bre)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Neq)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Plus)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Brs)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Geq)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Pbs)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Divid)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::And)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Or)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Multi)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sbs)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Pbe)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Ident)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Interger)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Not)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Ge)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Comma)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Leq)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Le)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Remain)] = 55;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sep)] = 55;

		// FuncCall -> '(' FuncRParams FuncRParamsNext ')'
		prodRules[56] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParams, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParamsNext, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::FuncCall)][__cvt(TokenType::Pbs)] = 56;

		// LvalAuxOrFuncCall -> LvalAux
		prodRules[57] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LvalAux, parent));
		};

		// Select: '-', '=', '==', ']', '}', '!=', '+', '{', '>=', '(', '/', '&&', '||', '*', '[', ')', Ident, Number, '!', '>', ',', '<=', '<', '%', ';'
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Minus)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Assign)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Eq)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sbe)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Bre)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Neq)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Plus)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Brs)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Geq)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbs)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Divid)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::And)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Or)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Multi)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sbs)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbe)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Ident)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Interger)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Not)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Ge)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Comma)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Leq)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Le)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Remain)] = 57;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sep)] = 57;

		// LvalAuxOrFuncCall -> FuncCall
		prodRules[58] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::FuncCall, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbs)] = 58;

		// UnaryExp -> PrimaryExp
		prodRules[59] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::PrimaryExp, parent));
		};

		// Select: '(', Number
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Pbs)] = 59;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Interger)] = 59;

		// UnaryExp -> Ident LvalAuxOrFuncCall
		prodRules[60] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LvalAuxOrFuncCall, parent));
		};

		// Select: Ident
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Ident)] = 60;

		// UnaryExp -> UnaryOp UnaryExp
		prodRules[61] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::UnaryOp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
		};

		// Select: '!', '+', '-'
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Not)] = 61;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Plus)] = 61;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Minus)] = 61;

		// FuncRParams -> ε
		prodRules[62] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ',', Ident, '+', '(', Number, '-', '!', ')'
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Comma)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Ident)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Plus)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbs)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Interger)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Minus)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Not)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbe)] = 62;

		// FuncRParams -> Exp
		prodRules[63] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Ident)] = 63;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Plus)] = 63;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbs)] = 63;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Interger)] = 63;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Minus)] = 63;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Not)] = 63;

		// FuncRParamsNext -> ε
		prodRules[64] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Pbe)] = 64;

		// FuncRParamsNext -> ',' FuncRParamsNext
		prodRules[65] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParamsNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Comma)] = 65;

		// FuncRParamsNext -> Exp
		prodRules[66] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Ident)] = 66;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Plus)] = 66;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Pbs)] = 66;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Interger)] = 66;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Minus)] = 66;
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Not)] = 66;

		// UnaryOp -> '+'
		prodRules[67] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Plus, parent));
		};

		// Select: '+'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Plus)] = 67;

		// UnaryOp -> '-'
		prodRules[68] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Minus, parent));
		};

		// Select: '-'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Minus)] = 68;

		// UnaryOp -> '!'
		prodRules[69] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Not, parent));
		};

		// Select: '!'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Not)] = 69;

		// MulExp -> UnaryExp MulExpNext
		prodRules[70] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Ident)] = 70;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Plus)] = 70;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Pbs)] = 70;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Interger)] = 70;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Minus)] = 70;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Not)] = 70;

		// MulExpNext -> ε
		prodRules[71] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '-', '=', '==', ']', '}', '!=', '+', '{', '>=', '(', '/', '&&', '||', '*', ')', Ident, Number, '!', '>', ',', '<=', '<', '%', ';'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Minus)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Assign)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Eq)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Sbe)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Bre)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Neq)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Plus)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Brs)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Geq)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Pbs)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Divid)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::And)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Or)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Multi)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Pbe)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Ident)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Interger)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Not)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Ge)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Comma)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Leq)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Le)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Remain)] = 71;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Sep)] = 71;

		// MulExpNext -> '*' MulExp MulExpNext
		prodRules[72] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Multi, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '*'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Multi)] = 72;

		// MulExpNext -> '/' MulExp MulExpNext
		prodRules[73] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Divid, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '/'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Divid)] = 73;

		// MulExpNext -> '%' MulExp MulExpNext
		prodRules[74] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Remain, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '%'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Remain)] = 74;

		// AddExp -> MulExp AddExpNext
		prodRules[75] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Ident)] = 75;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Plus)] = 75;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Pbs)] = 75;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Interger)] = 75;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Minus)] = 75;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Not)] = 75;

		// AddExpNext -> ε
		prodRules[76] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '-', '=', '==', ']', '}', '!=', '+', '{', '>=', '(', '&&', '||', ')', Ident, Number, '!', '>', ',', '<=', '<', ';'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Minus)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Assign)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Eq)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Sbe)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Bre)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Neq)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Plus)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Brs)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Geq)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Pbs)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::And)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Or)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Pbe)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Ident)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Interger)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Not)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Ge)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Comma)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Leq)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Le)] = 76;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Sep)] = 76;

		// AddExpNext -> '+' AddExp AddExpNext
		prodRules[77] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Plus, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '+'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Plus)] = 77;

		// AddExpNext -> '-' AddExp AddExpNext
		prodRules[78] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Minus, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '-'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Minus)] = 78;

		// RelExp -> AddExp RelExpNext
		prodRules[79] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Ident)] = 79;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Plus)] = 79;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Pbs)] = 79;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Interger)] = 79;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Minus)] = 79;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Not)] = 79;

		// RelExpNext -> ε
		prodRules[80] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '<=', '<', '>=', '&&', '||', '==', '!=', '>', ')'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Leq)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Le)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Geq)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::And)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Or)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Eq)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Neq)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Ge)] = 80;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Pbe)] = 80;

		// RelExpNext -> '<' RelExp RelExpNext
		prodRules[81] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Le, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '<'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Le)] = 81;

		// RelExpNext -> '>' RelExp RelExpNext
		prodRules[82] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Ge, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '>'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Ge)] = 82;

		// RelExpNext -> '<=' RelExp RelExpNext
		prodRules[83] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Leq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '<='
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Leq)] = 83;

		// RelExpNext -> '>=' RelExp RelExpNext
		prodRules[84] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Geq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '>='
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Geq)] = 84;

		// EqExp -> RelExp EqExpNext
		prodRules[85] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Ident)] = 85;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Plus)] = 85;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Pbs)] = 85;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Interger)] = 85;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Minus)] = 85;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Not)] = 85;

		// EqExpNext -> ε
		prodRules[86] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '&&', '||', '==', '!=', ')'
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::And)] = 86;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Or)] = 86;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Eq)] = 86;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Neq)] = 86;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Pbe)] = 86;

		// EqExpNext -> '==' EqExp EqExpNext
		prodRules[87] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Eq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '=='
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Eq)] = 87;

		// EqExpNext -> '!=' EqExp EqExpNext
		prodRules[88] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Neq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '!='
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Neq)] = 88;

		// LAndExp -> EqExp LAndExpNext
		prodRules[89] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExpNext, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Ident)] = 89;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Plus)] = 89;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Pbs)] = 89;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Interger)] = 89;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Minus)] = 89;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Not)] = 89;

		// LAndExpNext -> ε
		prodRules[90] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: 

		// LAndExpNext -> '&&' EqExp LAndExpNext
		prodRules[91] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::And, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExpNext, parent));
		};

		// Select: '&&'
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::And)] = 91;

		// LOrExp -> EqExp LOrExpNext
		prodRules[92] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LOrExpNext, parent));
		};

		// Select: Ident, '+', '(', Number, '-', '!'
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Ident)] = 92;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Plus)] = 92;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Pbs)] = 92;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Interger)] = 92;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Minus)] = 92;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Not)] = 92;

		// LOrExpNext -> '||' EqExp LOrExpNext
		prodRules[93] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Or, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LOrExpNext, parent));
		};

		// Select: '||'
		LL1Table[__cvt(TokenType::LOrExpNext)][__cvt(TokenType::Or)] = 93;

		// LOrExpNext -> ε
		prodRules[94] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::LOrExpNext)][__cvt(TokenType::Pbe)] = 94;
		
		return -1;
	}
	int _ = InitLL1();

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

	void MatchTokensForNode(deque<Lex::Token>& tokenList,Lex::Token& inputToken, ASTNode* node)
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


}
