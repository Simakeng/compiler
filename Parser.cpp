#include "Parser.h"
#include "Logger.h"
#include <string>
#include <sstream>
using namespace std;

namespace Compiler::Parser
{
	ASTNode* CreateNode(TokenType type, ASTNode* parent = nullptr)
	{
		auto r = new ASTNode;
		r->parent = parent;
		r->type = type;
		return r;
	}

	// ! Auto Generated Content Start
	const auto tokenCount = 82 ;
	int LL1Table[tokenCount][tokenCount];
	ProductionGenerationFunction prodRules[93];
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

		// Select: 'int', 'void'
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Int)] = 4;
		LL1Table[__cvt(TokenType::Decl)][__cvt(TokenType::Void)] = 4;

		// ConstDecl -> 'const' Type Ident VarDeclbody VarDeclNext
		prodRules[5] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Const, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Type, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclbody, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclNext, parent));
		};

		// Select: 'const'
		LL1Table[__cvt(TokenType::ConstDecl)][__cvt(TokenType::Const)] = 5;

		// VarOrFuncDecl -> Type Ident VarOrFuncDeclBody VarDeclNext
		prodRules[6] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Type, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarOrFuncDeclBody, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclNext, parent));
		};

		// Select: 'int', 'void'
		LL1Table[__cvt(TokenType::VarOrFuncDecl)][__cvt(TokenType::Int)] = 6;
		LL1Table[__cvt(TokenType::VarOrFuncDecl)][__cvt(TokenType::Void)] = 6;

		// VarDeclNext -> ',' Ident VarDeclbody VarDeclNext
		prodRules[7] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclbody, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Comma)] = 7;

		// VarDeclNext -> ';'
		prodRules[8] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: ';'
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Sep)] = 8;

		// VarDeclNext -> ε
		prodRules[9] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: 'while', 'return', '(', '-', '!', '{', 'int', Number, '+', Ident, 'break', 'if', '$', 'else', 'continue', 'const', '}', 'void'
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::While)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Return)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Pbs)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Minus)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Not)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Brs)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Int)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Interger)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Plus)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Ident)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Break)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::If)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::End)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Else)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Continue)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Const)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Bre)] = 9;
		LL1Table[__cvt(TokenType::VarDeclNext)][__cvt(TokenType::Void)] = 9;

		// Type -> 'int'
		prodRules[10] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Int, parent));
		};

		// Select: 'int'
		LL1Table[__cvt(TokenType::Type)][__cvt(TokenType::Int)] = 10;

		// Type -> 'void'
		prodRules[11] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Void, parent));
		};

		// Select: 'void'
		LL1Table[__cvt(TokenType::Type)][__cvt(TokenType::Void)] = 11;

		// VarOrFuncDeclBody -> VarDeclbody
		prodRules[12] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::VarDeclbody, parent));
		};

		// Select: '(', ',', 'return', '+', Ident, 'const', 'void', '!', '$', 'else', 'continue', '}', '=', '{', 'int', ';', '[', 'while', '-', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Pbs)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Comma)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Return)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Plus)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Ident)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Const)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Void)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Not)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::End)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Else)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Continue)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Bre)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Assign)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Brs)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Int)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Sep)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Sbs)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::While)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Minus)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Interger)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Break)] = 12;
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::If)] = 12;

		// VarOrFuncDeclBody -> FuncDeclBody
		prodRules[13] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::FuncDeclBody, parent));
		};

		// Select: '('
		LL1Table[__cvt(TokenType::VarOrFuncDeclBody)][__cvt(TokenType::Pbs)] = 13;

		// VarDeclbody -> ArraySizeDecl VarInit
		prodRules[14] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInit, parent));
		};

		// Select: '(', ',', 'return', '+', Ident, 'const', 'void', '!', '$', 'else', 'continue', '}', '=', '{', 'int', ';', '[', 'while', '-', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Pbs)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Comma)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Return)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Plus)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Ident)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Const)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Void)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Not)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::End)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Else)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Continue)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Bre)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Assign)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Brs)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Int)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Sep)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Sbs)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::While)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Minus)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Interger)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::Break)] = 14;
		LL1Table[__cvt(TokenType::VarDeclbody)][__cvt(TokenType::If)] = 14;

		// ArraySizeDecl -> '[' ArraySizeNum ']' ArraySizeDecl
		prodRules[15] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Sbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeNum, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
		};

		// Select: '['
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Sbs)] = 15;

		// ArraySizeDecl -> ε
		prodRules[16] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '(', 'return', ',', '+', Ident, 'const', 'void', '!', '$', 'else', 'continue', '}', '=', '{', 'int', ';', 'while', ')', '-', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Pbs)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Return)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Comma)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Plus)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Ident)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Const)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Void)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Not)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::End)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Else)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Continue)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Bre)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Assign)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Brs)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Int)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Sep)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::While)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Pbe)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Minus)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Interger)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::Break)] = 16;
		LL1Table[__cvt(TokenType::ArraySizeDecl)][__cvt(TokenType::If)] = 16;

		// ArraySizeNum -> ConstExp
		prodRules[17] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ConstExp, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Pbs)] = 17;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Minus)] = 17;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Not)] = 17;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Interger)] = 17;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Plus)] = 17;
		LL1Table[__cvt(TokenType::ArraySizeNum)][__cvt(TokenType::Ident)] = 17;

		// VarInit -> ε
		prodRules[18] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '(', 'return', ',', '+', Ident, 'const', 'void', '!', '$', 'else', 'continue', '}', '{', 'int', ';', 'while', '-', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Pbs)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Return)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Comma)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Plus)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Ident)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Const)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Void)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Not)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::End)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Else)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Continue)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Bre)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Brs)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Int)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Sep)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::While)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Minus)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Interger)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Break)] = 18;
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::If)] = 18;

		// VarInit -> '=' VarInitValue
		prodRules[19] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Assign, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValue, parent));
		};

		// Select: '='
		LL1Table[__cvt(TokenType::VarInit)][__cvt(TokenType::Assign)] = 19;

		// VarInitValue -> ConstExp
		prodRules[20] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::ConstExp, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Pbs)] = 20;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Minus)] = 20;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Not)] = 20;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Interger)] = 20;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Plus)] = 20;
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Ident)] = 20;

		// VarInitValue -> '{' VarInitValue VarInitValueNext '}'
		prodRules[21] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Brs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValueNext, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Bre, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::VarInitValue)][__cvt(TokenType::Brs)] = 21;

		// VarInitValueNext -> ',' VarInitValue VarInitValueNext
		prodRules[22] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::VarInitValueNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Comma)] = 22;

		// VarInitValueNext -> ε
		prodRules[23] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '}'
		LL1Table[__cvt(TokenType::VarInitValueNext)][__cvt(TokenType::Bre)] = 23;

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

		// Select: ')', ','
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Pbe)] = 25;
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Comma)] = 25;

		// FuncParamDecl -> 'int' Ident ArraySizeDecl
		prodRules[26] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Int, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
		};

		// Select: 'int'
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Int)] = 26;

		// FuncParamDecl -> Ident ArraySizeDecl
		prodRules[27] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Ident, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ArraySizeDecl, parent));
		};

		// Select: Ident
		LL1Table[__cvt(TokenType::FuncParamDecl)][__cvt(TokenType::Ident)] = 27;

		// FuncParamDeclNext -> ε
		prodRules[28] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Pbe)] = 28;

		// FuncParamDeclNext -> ',' FuncParamDecl FuncParamDeclNext
		prodRules[29] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDecl, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncParamDeclNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::FuncParamDeclNext)][__cvt(TokenType::Comma)] = 29;

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

		// Select: 'while', 'return', '(', '-', '!', '{', 'int', Number, '+', Ident, 'break', 'if', 'continue', 'const', 'void'
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::While)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Return)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Pbs)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Minus)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Not)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Brs)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Int)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Interger)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Plus)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Ident)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Break)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::If)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Continue)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Const)] = 31;
		LL1Table[__cvt(TokenType::Stmts)][__cvt(TokenType::Void)] = 31;

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

		// Select: 'const', 'int', 'void'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Const)] = 33;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Int)] = 33;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Void)] = 33;

		// Stmt -> Exp ';'
		prodRules[34] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Pbs)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Minus)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Not)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Interger)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Plus)] = 34;
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Ident)] = 34;

		// Stmt -> CodeBlock
		prodRules[35] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::CodeBlock, parent));
		};

		// Select: '{'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Brs)] = 35;

		// Stmt -> 'while' '(' Cond ')' Stmt
		prodRules[36] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::While, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Cond, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
		};

		// Select: 'while'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::While)] = 36;

		// Stmt -> 'break' ';'
		prodRules[37] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Break, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'break'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Break)] = 37;

		// Stmt -> 'continue' ';'
		prodRules[38] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Continue, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'continue'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Continue)] = 38;

		// Stmt -> 'return' ReturnVal ';'
		prodRules[39] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Return, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ReturnVal, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Sep, parent));
		};

		// Select: 'return'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::Return)] = 39;

		// Stmt -> 'if' '(' Cond ')' Stmt ElseStmt
		prodRules[40] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::If, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbs, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Cond, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Pbe, parent));
			parent->tokenList.push_back(CreateNode(TokenType::Stmt, parent));
			parent->tokenList.push_back(CreateNode(TokenType::ElseStmt, parent));
		};

		// Select: 'if'
		LL1Table[__cvt(TokenType::Stmt)][__cvt(TokenType::If)] = 40;

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

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Pbs)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Minus)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Not)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Interger)] = 42;
		LL1Table[__cvt(TokenType::ReturnVal)][__cvt(TokenType::Plus)] = 42;
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

		// Select: '(', '-', 'while', 'return', '!', '{', 'int', Number, '+', Ident, 'break', 'if', 'continue', 'const', '}', 'void'
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Pbs)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Minus)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::While)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Return)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Not)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Brs)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Int)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Interger)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Plus)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Ident)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Break)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::If)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Continue)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Const)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Bre)] = 44;
		LL1Table[__cvt(TokenType::ElseStmt)][__cvt(TokenType::Void)] = 44;

		// Exp -> AddExp AssignExpBody
		prodRules[45] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AssignExpBody, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Pbs)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Minus)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Not)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Interger)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Plus)] = 45;
		LL1Table[__cvt(TokenType::Exp)][__cvt(TokenType::Ident)] = 45;

		// ConstExp -> AddExp
		prodRules[46] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Pbs)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Minus)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Not)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Interger)] = 46;
		LL1Table[__cvt(TokenType::ConstExp)][__cvt(TokenType::Plus)] = 46;
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

		// Select: ',', ')', ']', ';'
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Comma)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Pbe)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Sbe)] = 48;
		LL1Table[__cvt(TokenType::AssignExpBody)][__cvt(TokenType::Sep)] = 48;

		// Cond -> LOrExp
		prodRules[49] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LOrExp, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Pbs)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Minus)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Not)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Interger)] = 49;
		LL1Table[__cvt(TokenType::Cond)][__cvt(TokenType::Plus)] = 49;
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

		// Select: '(', 'return', '<', ',', '+', Ident, '%', '>', 'const', '*', 'void', ']', '==', '!', '>=', '&&', '$', '||', 'else', 'continue', '}', '=', '<=', '/', '!=', '{', 'int', ';', '-', ')', 'while', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Pbs)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Return)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Le)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Comma)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Plus)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Ident)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Remain)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Ge)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Const)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Multi)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Void)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sbe)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Eq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Not)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Geq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::And)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::End)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Or)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Else)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Continue)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Bre)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Assign)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Leq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Divid)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Neq)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Brs)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Int)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Sep)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Minus)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Pbe)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::While)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Interger)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::Break)] = 51;
		LL1Table[__cvt(TokenType::ArrayAcces)][__cvt(TokenType::If)] = 51;

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

		// Select: '(', ',', 'return', '<', '+', Ident, '%', '>', 'const', '*', 'void', ']', '==', '!', '>=', '&&', '$', '||', 'else', 'continue', '}', '=', '<=', '/', '!=', '{', 'int', ';', '[', '-', ')', 'while', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Pbs)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Comma)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Return)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Le)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Plus)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Ident)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Remain)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Ge)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Const)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Multi)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Void)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sbe)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Eq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Not)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Geq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::And)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::End)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Or)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Else)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Continue)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Bre)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Assign)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Leq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Divid)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Neq)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Brs)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Int)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sep)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Sbs)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Minus)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Pbe)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::While)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Interger)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::Break)] = 54;
		LL1Table[__cvt(TokenType::LvalAux)][__cvt(TokenType::If)] = 54;

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

		// Select: '(', 'return', '<', ',', '+', Ident, '%', '>', 'const', '*', 'void', ']', '==', '!', '>=', '&&', '$', 'else', '||', 'continue', '}', '=', '<=', '/', '!=', '{', 'int', ';', '[', '-', ')', 'while', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbs)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Return)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Le)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Comma)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Plus)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Ident)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Remain)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Ge)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Const)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Multi)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Void)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sbe)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Eq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Not)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Geq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::And)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::End)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Else)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Or)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Continue)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Bre)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Assign)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Leq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Divid)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Neq)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Brs)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Int)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sep)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Sbs)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Minus)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Pbe)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::While)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Interger)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::Break)] = 56;
		LL1Table[__cvt(TokenType::LvalAuxOrFuncCall)][__cvt(TokenType::If)] = 56;

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

		// Select: '+', '-', '!'
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Plus)] = 60;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Minus)] = 60;
		LL1Table[__cvt(TokenType::UnaryExp)][__cvt(TokenType::Not)] = 60;

		// FuncRParams -> ε
		prodRules[61] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')', ','
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbe)] = 61;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Comma)] = 61;

		// FuncRParams -> Exp
		prodRules[62] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Exp, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Pbs)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Minus)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Not)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Interger)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Plus)] = 62;
		LL1Table[__cvt(TokenType::FuncRParams)][__cvt(TokenType::Ident)] = 62;

		// FuncRParamsNext -> ε
		prodRules[63] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Pbe)] = 63;

		// FuncRParamsNext -> ',' FuncRParams FuncRParamsNext
		prodRules[64] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Comma, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParams, parent));
			parent->tokenList.push_back(CreateNode(TokenType::FuncRParamsNext, parent));
		};

		// Select: ','
		LL1Table[__cvt(TokenType::FuncRParamsNext)][__cvt(TokenType::Comma)] = 64;

		// UnaryOp -> '+'
		prodRules[65] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Plus, parent));
		};

		// Select: '+'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Plus)] = 65;

		// UnaryOp -> '-'
		prodRules[66] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Minus, parent));
		};

		// Select: '-'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Minus)] = 66;

		// UnaryOp -> '!'
		prodRules[67] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Not, parent));
		};

		// Select: '!'
		LL1Table[__cvt(TokenType::UnaryOp)][__cvt(TokenType::Not)] = 67;

		// MulExp -> UnaryExp MulExpNext
		prodRules[68] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Pbs)] = 68;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Minus)] = 68;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Not)] = 68;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Interger)] = 68;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Plus)] = 68;
		LL1Table[__cvt(TokenType::MulExp)][__cvt(TokenType::Ident)] = 68;

		// MulExpNext -> ε
		prodRules[69] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '(', 'return', '<', ',', '+', Ident, '>', 'const', 'void', ']', '==', '!', '>=', '&&', '$', '||', 'else', 'continue', '}', '=', '<=', '!=', '{', 'int', ';', '-', ')', 'while', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Pbs)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Return)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Le)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Comma)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Plus)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Ident)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Ge)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Const)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Void)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Sbe)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Eq)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Not)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Geq)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::And)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::End)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Or)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Else)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Continue)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Bre)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Assign)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Leq)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Neq)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Brs)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Int)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Sep)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Minus)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Pbe)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::While)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Interger)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Break)] = 69;
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::If)] = 69;

		// MulExpNext -> '*' UnaryExp MulExpNext
		prodRules[70] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Multi, parent));
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '*'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Multi)] = 70;

		// MulExpNext -> '/' UnaryExp MulExpNext
		prodRules[71] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Divid, parent));
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '/'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Divid)] = 71;

		// MulExpNext -> '%' UnaryExp MulExpNext
		prodRules[72] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Remain, parent));
			parent->tokenList.push_back(CreateNode(TokenType::UnaryExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExpNext, parent));
		};

		// Select: '%'
		LL1Table[__cvt(TokenType::MulExpNext)][__cvt(TokenType::Remain)] = 72;

		// AddExp -> MulExp AddExpNext
		prodRules[73] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Pbs)] = 73;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Minus)] = 73;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Not)] = 73;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Interger)] = 73;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Plus)] = 73;
		LL1Table[__cvt(TokenType::AddExp)][__cvt(TokenType::Ident)] = 73;

		// AddExpNext -> ε
		prodRules[74] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '(', ',', '<', 'return', '+', Ident, '>', 'const', 'void', ']', '==', '!', '>=', '&&', '$', 'else', '||', 'continue', '}', '=', '<=', '!=', '{', 'int', ';', ')', 'while', '-', Number, 'break', 'if'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Pbs)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Comma)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Le)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Return)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Plus)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Ident)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Ge)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Const)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Void)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Sbe)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Eq)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Not)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Geq)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::And)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::End)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Else)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Or)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Continue)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Bre)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Assign)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Leq)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Neq)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Brs)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Int)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Sep)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Pbe)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::While)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Minus)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Interger)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Break)] = 74;
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::If)] = 74;

		// AddExpNext -> '+' MulExp AddExpNext
		prodRules[75] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Plus, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '+'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Plus)] = 75;

		// AddExpNext -> '-' MulExp AddExpNext
		prodRules[76] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Minus, parent));
			parent->tokenList.push_back(CreateNode(TokenType::MulExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExpNext, parent));
		};

		// Select: '-'
		LL1Table[__cvt(TokenType::AddExpNext)][__cvt(TokenType::Minus)] = 76;

		// RelExp -> AddExp RelExpNext
		prodRules[77] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Pbs)] = 77;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Minus)] = 77;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Not)] = 77;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Interger)] = 77;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Plus)] = 77;
		LL1Table[__cvt(TokenType::RelExp)][__cvt(TokenType::Ident)] = 77;

		// RelExpNext -> ε
		prodRules[78] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '!=', ')', '==', '&&', '||'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Neq)] = 78;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Pbe)] = 78;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Eq)] = 78;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::And)] = 78;
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Or)] = 78;

		// RelExpNext -> '<' AddExp RelExpNext
		prodRules[79] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Le, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '<'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Le)] = 79;

		// RelExpNext -> '>' AddExp RelExpNext
		prodRules[80] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Ge, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '>'
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Ge)] = 80;

		// RelExpNext -> '<=' AddExp RelExpNext
		prodRules[81] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Leq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '<='
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Leq)] = 81;

		// RelExpNext -> '>=' AddExp RelExpNext
		prodRules[82] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Geq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::AddExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExpNext, parent));
		};

		// Select: '>='
		LL1Table[__cvt(TokenType::RelExpNext)][__cvt(TokenType::Geq)] = 82;

		// EqExp -> RelExp EqExpNext
		prodRules[83] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Pbs)] = 83;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Minus)] = 83;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Not)] = 83;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Interger)] = 83;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Plus)] = 83;
		LL1Table[__cvt(TokenType::EqExp)][__cvt(TokenType::Ident)] = 83;

		// EqExpNext -> ε
		prodRules[84] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '||', ')', '&&'
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Or)] = 84;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Pbe)] = 84;
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::And)] = 84;

		// EqExpNext -> '==' RelExp EqExpNext
		prodRules[85] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Eq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '=='
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Eq)] = 85;

		// EqExpNext -> '!=' RelExp EqExpNext
		prodRules[86] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Neq, parent));
			parent->tokenList.push_back(CreateNode(TokenType::RelExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExpNext, parent));
		};

		// Select: '!='
		LL1Table[__cvt(TokenType::EqExpNext)][__cvt(TokenType::Neq)] = 86;

		// LAndExp -> EqExp LAndExpNext
		prodRules[87] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExpNext, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Pbs)] = 87;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Minus)] = 87;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Not)] = 87;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Interger)] = 87;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Plus)] = 87;
		LL1Table[__cvt(TokenType::LAndExp)][__cvt(TokenType::Ident)] = 87;

		// LAndExpNext -> ε
		prodRules[88] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: '||', ')'
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::Or)] = 88;
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::Pbe)] = 88;

		// LAndExpNext -> '&&' EqExp LAndExpNext
		prodRules[89] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::And, parent));
			parent->tokenList.push_back(CreateNode(TokenType::EqExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExpNext, parent));
		};

		// Select: '&&'
		LL1Table[__cvt(TokenType::LAndExpNext)][__cvt(TokenType::And)] = 89;

		// LOrExp -> LAndExp LOrExpNext
		prodRules[90] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::LAndExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LOrExpNext, parent));
		};

		// Select: '(', '-', '!', Number, '+', Ident
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Pbs)] = 90;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Minus)] = 90;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Not)] = 90;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Interger)] = 90;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Plus)] = 90;
		LL1Table[__cvt(TokenType::LOrExp)][__cvt(TokenType::Ident)] = 90;

		// LOrExpNext -> '||' LAndExp LOrExpNext
		prodRules[91] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Or, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LAndExp, parent));
			parent->tokenList.push_back(CreateNode(TokenType::LOrExpNext, parent));
		};

		// Select: '||'
		LL1Table[__cvt(TokenType::LOrExpNext)][__cvt(TokenType::Or)] = 91;

		// LOrExpNext -> ε
		prodRules[92] = [](ASTNode* parent, TokenType inputToken){
			parent->tokenList.push_back(CreateNode(TokenType::Empty, parent));
		};

		// Select: ')'
		LL1Table[__cvt(TokenType::LOrExpNext)][__cvt(TokenType::Pbe)] = 92;
		
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
		
		case __cvt(TokenType::ArraySizeNum): return "[ArraySizeNum]";
		case __cvt(TokenType::VarInit): return "[VarInit]";
		case __cvt(TokenType::FuncParamDeclNext): return "[FuncParamDeclNext]";
		case __cvt(TokenType::FuncRParamsNext): return "[FuncRParamsNext]";
		case __cvt(TokenType::VarOrFuncDeclBody): return "[VarOrFuncDeclBody]";
		case __cvt(TokenType::Decl): return "[Decl]";
		case __cvt(TokenType::Exp): return "[Exp]";
		case __cvt(TokenType::ConstExp): return "[ConstExp]";
		case __cvt(TokenType::AssignExpBody): return "[AssignExpBody]";
		case __cvt(TokenType::VarInitValue): return "[VarInitValue]";
		case __cvt(TokenType::LOrExpNext): return "[LOrExpNext]";
		case __cvt(TokenType::Stmt): return "[Stmt]";
		case __cvt(TokenType::RelExp): return "[RelExp]";
		case __cvt(TokenType::Stmts): return "[Stmts]";
		case __cvt(TokenType::CompUnit): return "[CompUnit]";
		case __cvt(TokenType::ElseStmt): return "[ElseStmt]";
		case __cvt(TokenType::ArraySizeDecl): return "[ArraySizeDecl]";
		case __cvt(TokenType::AddExp): return "[AddExp]";
		case __cvt(TokenType::AddExpNext): return "[AddExpNext]";
		case __cvt(TokenType::VarDeclbody): return "[VarDeclbody]";
		case __cvt(TokenType::ReturnVal): return "[ReturnVal]";
		case __cvt(TokenType::EqExp): return "[EqExp]";
		case __cvt(TokenType::FuncParamDecl): return "[FuncParamDecl]";
		case __cvt(TokenType::UnaryOp): return "[UnaryOp]";
		case __cvt(TokenType::EqExpNext): return "[EqExpNext]";
		case __cvt(TokenType::CodeBlock): return "[CodeBlock]";
		case __cvt(TokenType::PrimaryExp): return "[PrimaryExp]";
		case __cvt(TokenType::UnaryExp): return "[UnaryExp]";
		case __cvt(TokenType::FuncRParams): return "[FuncRParams]";
		case __cvt(TokenType::LOrExp): return "[LOrExp]";
		case __cvt(TokenType::ArrayAcces): return "[ArrayAcces]";
		case __cvt(TokenType::FuncDeclBody): return "[FuncDeclBody]";
		case __cvt(TokenType::VarDeclNext): return "[VarDeclNext]";
		case __cvt(TokenType::Type): return "[Type]";
		case __cvt(TokenType::LAndExpNext): return "[LAndExpNext]";
		case __cvt(TokenType::RelExpNext): return "[RelExpNext]";
		case __cvt(TokenType::LvalAuxOrFuncCall): return "[LvalAuxOrFuncCall]";
		case __cvt(TokenType::LAndExp): return "[LAndExp]";
		case __cvt(TokenType::VarInitValueNext): return "[VarInitValueNext]";
		case __cvt(TokenType::Cond): return "[Cond]";
		case __cvt(TokenType::VarOrFuncDecl): return "[VarOrFuncDecl]";
		case __cvt(TokenType::MulExp): return "[MulExp]";
		case __cvt(TokenType::MulExpNext): return "[MulExpNext]";
		case __cvt(TokenType::LvalAux): return "[LvalAux]";
		case __cvt(TokenType::FuncCall): return "[FuncCall]";
		case __cvt(TokenType::ConstDecl): return "[ConstDecl]";
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

	void MatchTokensForNode(deque<Lex::Token>& tokenList, Lex::Token& inputToken, ASTNode* node)
	{
		auto nodeType = node->type;

		auto rule = prodRules[LL1Table[__cvt(nodeType)][__cvt(inputToken.type)]];
		rule(node, static_cast<TokenType>(inputToken.type));
		if (rule == prodRules[0])
			Console::Log("at line:", inputToken._line, ":", inputToken._start, Level::Error);
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
			*mss << prefix << brs << __tstr((*it)->type);
			if ((*it)->value.has_value())
			{
				*mss << " - " << any_cast<string>((*it)->value);
			}
			*mss << "\n";
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
