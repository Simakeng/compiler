#pragma once
#include <fstream>
#include <deque>
#include "Lex.h"
namespace Compiler 
{
	class LexParser
	{
	public:
		LexParser(const char* fileName);
		~LexParser() = default;
	private:
		std::ifstream byteStream;
		std::string fileName;
	public:
		std::deque<Lex::Token> GetTokens();
	};


	
}
