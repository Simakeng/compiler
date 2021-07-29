#include "AssemblyGeneration.h"

#include <unordered_map>

using namespace std;


namespace Compiler::ARM
{
	unordered_map<Register, const char*> register_map = {
		{Register::R1,"R1"},
		{Register::R2,"R2"},
		{Register::R3,"R3"},
		{Register::R4,"R4"},
		{Register::R5,"R5"},
		{Register::R6,"R6"},
		{Register::R7,"R7"},
		{Register::R8,"R8"},
		{Register::R9,"R9"},
		{Register::R10,"R10"},
		{Register::R11,"R11"},
		{Register::R12,"R12"},
		{Register::SP,"SP"},
		{Register::LR,"LR"},
		{Register::PC,"PC"}
	};

	string MakeAsm(const char* code, Register rd, Register rn, int imm)
	{
		//"code rd, rn"
		return string(code) + "\t" + register_map[rd] + ", " + register_map[rn] + ", " + to_string(imm);
	}
	string MakeAsm(const char* code, Register rd, Register rn)
	{
		return string(code) + "\t" + register_map[rd] + ", " + register_map[rn];
	}
	std::string MakeAsm(const char* code, Register rd, int imm)
	{
		return string(code) + "\t" + register_map[rd] + ", " + to_string(imm);
	}

}


