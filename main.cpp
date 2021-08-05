#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "Logger.h"
#include "Parser.h"
#include "LexParser.h"
#include "AssemblyGeneration.h"
#include "ASTUtils.h"
using namespace Compiler;

int main(int argc, const char* argv[])
{

	//Console::Log("Hello World!");
	//Console::Log("Template is",1,2,3,"ɵ��Ф����");
	//Console::Log("Test Info Log", Level::Info);
	//Console::Log("Test Warning Log",Level::Warning);
	//Console::Log("Test Error Log",Level::Error);
	//Console::Log("Test Fatal Log",Level::Fatal);
	auto sy_in = argv[1];
	auto ast_out = argv[2];

	LexParser lexer("test/a_plus_b.sy");
	auto tokens = lexer.GetTokens();
	auto ast = Parser::ParserTokens(tokens);
	auto r1 = VisualizeAST(ast);
	AST::StripEmptyNode(ast);
	auto r2 = VisualizeAST(ast);
	AST::StripExprNode(ast);
	auto r3 = VisualizeAST(ast);

	FILE* fp = fopen("out.ast","wb");
	fwrite(r1.c_str(), 1, r1.size(), fp);
	fclose(fp);

	fp = fopen("out_strip.ast", "wb");
	fwrite(r2.c_str(), 1, r2.size(), fp);
	fclose(fp);

	fp = fopen("out_expr.ast", "wb");
	fwrite(r3.c_str(), 1, r3.size(), fp);
	fclose(fp);
	return 0;
}