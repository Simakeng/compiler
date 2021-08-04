#include <cstdio>
#include "Logger.h"
#include "Parser.h"
#include "LexParser.h"
#include "AssemblyGeneration.h"
using namespace Compiler;
using namespace ASM;

int main()
{

	//Console::Log("Hello World!");
	//Console::Log("Template is",1,2,3,"Éµ±ÆÐ¤·²Áú");
	//Console::Log("Test Info Log", Level::Info);
	//Console::Log("Test Warning Log",Level::Warning);
	//Console::Log("Test Error Log",Level::Error);
	//Console::Log("Test Fatal Log",Level::Fatal);

	LexParser lexer("test/a_plus_b.sy");
	auto tokens = lexer.GetTokens();

	auto ast = Parser::ParserTokens(tokens);

	return 0;
}