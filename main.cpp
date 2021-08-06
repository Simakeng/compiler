#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "Logger.h"
#include "Parser.h"
#include "LexParser.h"
#include "AssemblyGeneration.h"
#include "ASTUtils.h"
#include "IR.h"

using namespace Compiler;

int main(int argc, const char* argv[])
{
	auto sy_in = argv[1];
	auto ast_out = argv[2];

	LexParser lexer("test/vars.sy");
	auto tokens = lexer.GetTokens();
	auto ast = Parser::ParserTokens(tokens);

	AST::StripEmptyNode(ast);
	AST::StripExprNode(ast);
	AST::StripHumanReadable(ast);

	auto ast_txt = VisualizeAST(ast);

	FILE* fp = fopen("out.ast", "wb");
	fwrite(ast_txt.c_str(), 1, ast_txt.size(), fp);
	fclose(fp);

	auto ir = IR::AnalysisFromAST(ast);

	return 0;
}