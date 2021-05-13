#pragma once
#include <fstream>
namespace Compiler 
{
	class LexParser
	{
	public:
		LexParser(const char* fileName);
		~LexParser();
	private:
		std::fstream byteStream;
	};
}
