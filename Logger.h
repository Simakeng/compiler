#pragma once
#include <cstdio>
#include <string>
#include <iostream>
#include <unordered_map>

namespace Compiler
{
	enum class Level
	{
		Info,
		Warning,
		Error,
		Fatal
	};

	enum class Color
	{
		Red,
		White,
		Gray,
		Yellow,
		Orange
	};

	static inline std::unordered_map<Level, Color> Level2Color =
	{
		{Level::Info,Color::Gray},
		{Level::Warning,Color::Yellow},
		{Level::Error,Color::Orange},
		{Level::Fatal,Color::Red},
	};
	static inline std::unordered_map<Level, const char*> Level2String =
	{
		{Level::Info,"[Info]"},
		{Level::Warning,"[Warning]"},
		{Level::Error,"[Error]"},
		{Level::Fatal,"[Fatal]"},
	};

	class Console
	{
	public:
		template<typename T, class ... Args>
		static inline void Log(T head, Args... args)
		{
			Level logLevel = GetLogLevel(args...);
			SetColor(Level2Color[logLevel]);
			std::cout << Level2String[logLevel] << ' ' << head;
			ContinueLog(args...);
		};

		template<class ... Args>
		static inline void Log(wchar_t head, Args... args)
		{
			Level logLevel = GetLogLevel(args...);
			SetColor(Level2Color[logLevel]);
			std::cout << Level2String[logLevel] << ' ';
			std::wcout << head;
			ContinueLog(args...);
		};

	private:
		static void SetColor(Color color);

	private:
		template<typename T, class ... Args>
		static inline void ContinueLog(T head, Args ... args)
		{
			std::cout << ' ' << head;
			ContinueLog(args...);
		}
		template<typename T>
		static inline void ContinueLog(T tail)
		{
			std::cout << ' ' << tail << std::endl;
		}
		template<class ... Args>
		static inline void ContinueLog(wchar_t head, Args ... args)
		{
			std::wcout << L' ' << head;
			ContinueLog(args...);
		}
		template<>
		static inline void ContinueLog(wchar_t tail)
		{
			std::wcout << L' ' << tail << std::endl;
		}
		template<>
		static inline void ContinueLog(Level level) { std::cout << std::endl; }
		static inline void ContinueLog() { std::cout << std::endl; }
	private:
		template<typename T, class ... Args>
		static inline Level GetLogLevel(T head, Args... args)
		{
			return GetLogLevel(args...);
		}
		template<typename T>
		static inline Level GetLogLevel(T tail)
		{
			return Level::Info;
		}
		template<>
		static inline Level GetLogLevel(Level tail)
		{
			return tail;
		}

		static inline Level GetLogLevel() { return Level::Info; }
	};
}