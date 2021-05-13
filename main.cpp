#include <cstdio>
#include "Logger.h"
using namespace Compiler;

int main()
{
	Console::Log("Hello World!");
	Console::Log("Template is",1,2,3,"Éµ±ÆÐ¤·²Áú");
	Console::Log("Test Info Log", Level::Info);
	Console::Log("Test Warning Log",Level::Warning);
	Console::Log("Test Error Log",Level::Error);
	Console::Log("Test Fatal Log",Level::Fatal);
}