#include <cstdio>
#include "Logger.h"
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

	//LexParser lexer("test/hello_world.c");
	//auto tokens = lexer.GetTokens();

	AssemblyGenerator gen;

	gen.AddPrologue("\t.arch armv7-a\n"
		"\t.eabi_attribute 28, 1\n"
		"\t.eabi_attribute 20, 1\n"
		"\t.eabi_attribute 21, 1\n"
		"\t.eabi_attribute 23, 3\n"
		"\t.eabi_attribute 24, 1\n"
		"\t.eabi_attribute 25, 1\n"
		"\t.eabi_attribute 26, 2\n"
		"\t.eabi_attribute 30, 6\n"
		"\t.eabi_attribute 34, 1\n"
		"\t.eabi_attribute 18, 4\n"
		"\t.file	\"io.c\"\n"
		"\t.text\n"
		"\t.comm	_sysy_start,8,4\n"
		"\t.comm	_sysy_end,8,4\n"
		"\t.comm	_sysy_l1,4096,4\n"
		"\t.comm	_sysy_l2,4096,4\n"
		"\t.comm	_sysy_h,4096,4\n"
		"\t.comm	_sysy_m,4096,4\n"
		"\t.comm	_sysy_s,4096,4\n"
		"\t.comm	_sysy_us,4096,4\n"
		"\t.comm	_sysy_idx,4,4\n"
		"\t.align	1\n"
		"\t.global	main\n"
		"\t.syntax unified\n"
		"\t.thumb\n"
		"\t.thumb_func\n"
		"\t.fpu vfpv3-d16\n"
		"\t.type	main, %function\n");

	auto& sec = gen.CreateSection("main");


	const auto str = "[In SYSY]Hello World!\n";
	auto len = strlen(str);
	sec.AddCode(Make("PUSH", { Reg::R7,Reg::LR }));
	sec.AddCode(Make("ADD", Reg::R7, Reg::SP, 0));

	for (int i = 0; i < len; i++)
	{
		int ch = str[i];
		sec.AddCode(Make("MOVS", Reg::R0, ch));
		sec.AddCode(Make("BL", "putch(PLT)"));
	}

	sec.AddCode(Make("MOVS", Reg::R3, 0));
	sec.AddCode(Make("MOV", Reg::R0, Reg::R3));
	sec.AddCode(Make("POP", { Reg::R7,Reg::PC }));

	gen.AddEpilogue(".size	main, .-main\n");
	gen.AddEpilogue(".ident	\"FH:(xiajibaxiede)\"\n");
	gen.AddEpilogue(".section	.note.GNU-stack,\"\",%progbits\n");

	std::fstream out("obj.s", std::ios::out);
	out << gen.Summary();


}