#include "Logger.h"

#ifdef WIN32 // Windows Platform
#include <Windows.h>
#endif

namespace Compiler
{
	int __maigc = []() {
		std::wcout.imbue(std::locale("chs"));
		return 0;
	}();

	void Console::SetColor(Color color)
	{
		switch (color)
		{
		case Compiler::Color::Red:
#ifdef WIN32 // Windows Platform
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
#endif
			break;
		case Compiler::Color::White:
#ifdef WIN32 // Windows Platform
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
			break;
		case Compiler::Color::Gray:
#ifdef WIN32 // Windows Platform
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
			break;
		case Compiler::Color::Yellow:
#ifdef WIN32 // Windows Platform
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
#endif
			break;
		case Compiler::Color::Orange:
#ifdef WIN32 // Windows Platform
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
#endif
			break;
		default:
			break;
		}
	}
	static int exitCode = 0;
	void Console::SetExitCode(int code)
	{
		exitCode = code;
	}

	int Console::GetExitCode()
	{
		return exitCode;
	}

	void Console::Terminate [[ noreturn ]] (int exit_code)
	{
		std::exit(exit_code);
	}

}
