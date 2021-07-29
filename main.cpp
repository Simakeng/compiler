#include <cstdio>
#include "Logger.h"
#include "LexParser.h"
using namespace Compiler;
int main()
{

	//Console::Log("Hello World!");
	//Console::Log("Template is",1,2,3,"ɵ��Ф����");
	//Console::Log("Test Info Log", Level::Info);
	//Console::Log("Test Warning Log",Level::Warning);
	//Console::Log("Test Error Log",Level::Error);
	//Console::Log("Test Fatal Log",Level::Fatal);

	LexParser lexer("test/hello_world.c");
	auto tokens = lexer.GetTokens();
}