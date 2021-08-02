#include "AssemblyGeneration.h"

#include <unordered_map>
#include <sstream>

using namespace std;


namespace Compiler::ASM
{
	unordered_map<Reg, const char*> register_map = {
		{Reg::R0,"R0"},
		{Reg::R1,"R1"},
		{Reg::R2,"R2"},
		{Reg::R3,"R3"},
		{Reg::R4,"R4"},
		{Reg::R5,"R5"},
		{Reg::R6,"R6"},
		{Reg::R7,"R7"},
		{Reg::R8,"R8"},
		{Reg::R9,"R9"},
		{Reg::R10,"R10"},
		{Reg::R11,"R11"},
		{Reg::R12,"R12"},
		{Reg::SP,"SP"},
		{Reg::LR,"LR"},
		{Reg::PC,"PC"}
	};

	std::string Make(const char* code, std::initializer_list<Reg> reglist)
	{
		stringstream ss;
		ss << code << "\t{";
		auto beg = reglist.begin();
		for (int i = reglist.size(); i > 0; i--)
		{
			ss << register_map[*beg++];
			if (i != 1)
				ss << ", ";
		}
		ss << "}";
		return ss.str();
	}
	string Make(const char* code, const char* operation)
	{
		//"code rd, rn"
		return string(code) + "\t" + operation;
	}

	string Make(const char* code, Reg rd, Reg rn, int imm)
	{
		//"code rd, rn"
		return string(code) + "\t" + register_map[rd] + ", " + register_map[rn] + ", #" + to_string(imm);
	}
	string Make(const char* code, Reg rd, Reg rn)
	{
		return string(code) + "\t" + register_map[rd] + ", " + register_map[rn];
	}
	std::string Make(const char* code, Reg rd, int imm)
	{
		return string(code) + "\t" + register_map[rd] + ", " + to_string(imm);
	}

	void AssemblyGenerator::AddPrologue(std::string text)
	{
		this->prologue_list.push_back(text);
	}

	void AssemblyGenerator::AddEpilogue(std::string text)
	{
		this->epilogue_list.push_back(text);
	}

	AssemblyGenerator::Section& AssemblyGenerator::CreateSection(const char* section_name)
	{
		section_list.emplace_back(move(Section(section_name)));
		return section_list.back();
	}

	std::string AssemblyGenerator::Summary()
	{
		stringstream ss;

		for (auto& prologues : prologue_list)
			ss << prologues;

		for (auto& sec : section_list)
		{
			ss << sec.Summary();
			ss << "\n";
		}

		for (auto& epilogues : epilogue_list)
			ss << epilogues;

		return ss.str();
	}
	AssemblyGenerator::Section::Section(const char* name)
	{
		this->_name = string(name);
	}

	AssemblyGenerator::Section::Section(Section&& rhs) noexcept
	{
		this->code_list = std::move(rhs.code_list);
		this->_name = std::move(rhs._name);
	}

	void AssemblyGenerator::Section::AddCode(std::string Code)
	{
		this->code_list.push_back(Code);
	}

	std::string AssemblyGenerator::Section::Summary()
	{
		stringstream ss;
		ss << _name << ":\n";
		for (auto& code_ : code_list)
			ss << "\t" << code_ << "\n";
		return ss.str();

	}




	
}


