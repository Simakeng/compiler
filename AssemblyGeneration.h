#pragma once
#include <string>
#include <deque>
namespace Compiler
{
	namespace ARM
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
			private:
				Section(const char* name);
				std::string _name;
			public:
				friend class AssemblyGenerator;

				void AddCode(std::string Code);
				std::string Summary();
			};
		private:
			std::deque<Section> section_list;
		public:
			std::string Summary();
		};

		class BasicOperation
		{
		};

		enum class Register
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

		enum class OpCode
		{
			ADC,
			ADD,
			ADR,
			ADRL,
			AND,
			ASR,
			B,
			BFC,
			BFI,
			BIC,
			BKPT,
			BL,
			BLX,
			BX,
			BXJ,
			CBZ,
			CBNZ,
			CDP,
			CDP2,
			CLREX,
			CLZ,
			CMP,
			CMN,
			DBG,
			DMB,
			DSB,
			EOR,
			ERET,
			HVC,
			ISB,
			IT,
			LDC,
			LDC2,
			LDM,
			LDR,
			LDREX,
			LSL,
			LSR,
			MCR,
			MCR2,
			MCRR,
			MCRR2,
			MLA,
			MLS,
			MOV,
			MOVT,
			MRC,
			MRC2,
			MRRC,
			MRRC2,
			MRS,
			MUL, MVN, NOP, ORN, ORR, PKHBT, PLD, PLI, POP, PUSH, QADD,
			QADD8, QADD16, QASX, QDADD, QDSUB, QSAX, QSUB, QSUB8, QSUB16,
			RBIT, REV, REV16, REVSH, RFE, ROR, RRX, RSB, RSC, SADD8, SADD16, SASX, SBC,
			SBFX, SDIV, SEL, SETEND, SEV, SHADD7, SHADD16, SHASX, SHSAX, SHSUB8, SHSUB16,
			SMC, SMLAxy, SMLAD, SMLAL, SMLALD, SMLALxy, SMLAWy, SMLSD, SMLSLD, SMMLA, SMMLS, SMMUL, SMUAD,
			SMULxy,
			SMULL, SMULWy, SMUSD, SRS, SSAT, SSAT16, SSAX, SSAT16, SSAX, SSUB8, SSUB16, STC, STC2, STM, STR,
			STREX, SUB, SUBS, SVC, SWP, SWPB,
			SXTAB,
			SXTAB16,
			SXTAH,
			SYS,
			TBB, TBH, TEQ, TST, UADD8, UADD16,
			UASX, UBFX, UDIV, UHADD8, UHADD16,
			UHASX, UHSAX, UHSUB8, UHSUB16,
			UMAAL,
			UMLAL,
			UMULL,
			UQADD8,
			UQADD16,
			UQASX,
			UQSAX,
			UQSUB8,
			UQSUB16,
			USAD8,
			USADA8,
			USAT,
			USAT16,
			USAX,
			USUB8,
			USUB16,
			UXTAB,
			UXTAB16,
			UXTAH,
			UXTB,
			UXTB16,
			UXTH, WFE, WFI, YIELD
		};

		std::string MakeAsm(const char* code, Register rd, Register rn, int imm);
		std::string MakeAsm(const char* code, Register rd, Register rn);
		std::string MakeAsm(const char* code, Register rd, int imm);
	}
}