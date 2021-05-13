#include "LexParser.h"
#include "Logger.h"
#include <fstream>

using namespace std;
Compiler::LexParser::LexParser(const char* fileName):
	byteStream(fstream(fileName, ios::in))
{
	//if(!byteStream.is_open())
				
}

Compiler::LexParser::~LexParser()
{
}
