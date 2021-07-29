#pragma once
#include <string>
#include <deque>
namespace Compiler
{
	namespace ASM
	{
		class AssemblyGenerator
		{
		public:
			AssemblyGenerator() = default;
			~AssemblyGenerator() = default;
		public:
			class Section
			{
			public:
				~Section() = default;
				Section(const Section&) = delete; // no copy
				Section(Section&& rhs) noexcept; // can move
			private:
				Section(const char* name);
				std::string _name;
				std::deque<std::string> code_list;
			public:
				friend class AssemblyGenerator;
				void AddCode(std::string Code);
				std::string Summary();
			};
		public:
			void AddPrologue(std::string text);
			void AddEpilogue(std::string text);
			Section& CreateSection(const char* section_name);
		private:
			std::deque<Section> section_list;
			std::deque<std::string> prologue_list;
			std::deque<std::string> epilogue_list;
		public:
			std::string Summary();
		};

		enum class Reg
		{
			R0 = 0,
			R1,
			R2,
			R3,
			R4,
			R5,
			R6,
			R7,
			R8,
			R9,
			R10,
			R11,
			R12,
			R13,
			R14,
			R15,
			SP = R13,
			LR = R14,
			PC = R15,
		};

		std::string Make(const char* code, const char* operation);
		std::string Make(const char* code, std::initializer_list<Reg> reglist);
		std::string Make(const char* code, Reg  rd, Reg rn, int imm);
		std::string Make(const char* code, Reg  rd, Reg rn);
		std::string Make(const char* code, Reg  rd, int imm);
	}
}