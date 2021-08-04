#include "LexParser.h"
#include "Logger.h"
#include <fstream>
#include <vector>
#include <regex>
using namespace std;
namespace Compiler
{
	LexParser::LexParser(const char* fileName) :
		byteStream(ifstream(fileName, ios::in)),
		fileName(fileName)
	{
		if (!byteStream.is_open())
		{
			Console::Log("Cannot Load File", fileName, "!", Level::Fatal);
		}

	}


	namespace Lex
	{
		const vector<pair<TokenType, regex>> RegexList =
		{
			{ TokenType::comment_h, regex(R"(^//.*)") },
			{ TokenType::comment_l_b, regex(R"(^/\*)") },
			{ TokenType::Plus, regex(R"(^\+)") },
			{ TokenType::Minus, regex(R"(^\-)") },
			{ TokenType::Multi, regex(R"(^\*)") },
			{ TokenType::Divid, regex(R"(^/)") },
			{ TokenType::Remain, regex(R"(^%)") },
			{ TokenType::Eq, regex(R"(^==)") },
			{ TokenType::Neq, regex(R"(^\!=)") },
			{ TokenType::Geq, regex(R"(^>=)") },
			{ TokenType::Leq, regex(R"(^<=)") },
			{ TokenType::And, regex(R"(^&&)") },
			{ TokenType::Or, regex(R"(^\|\|)") },
			{ TokenType::Assign, regex(R"(^=)") },
			{ TokenType::Ge, regex(R"(^>)") },
			{ TokenType::Le, regex(R"(^<)") },
			{ TokenType::Not, regex(R"(^!)") },
			{ TokenType::Comma, regex(R"(^,)") },

			{ TokenType::If, regex(R"(^if)") },
			{ TokenType::Else, regex(R"(^else)") },
			{ TokenType::While, regex(R"(^while)") },
			{ TokenType::Break, regex(R"(^break)") },
			{ TokenType::Return, regex(R"(^return)") },
			{ TokenType::Const, regex(R"(^const)") },
			{ TokenType::Continue, regex(R"(^continue)") },

			{ TokenType::Void, regex(R"(^void)") },
			{ TokenType::Int, regex(R"(^int)") },

			{ TokenType::Pbs, regex(R"(^\()") },
			{ TokenType::Pbe, regex(R"(^\))") },
			{ TokenType::Sbs, regex(R"(^\[)") },
			{ TokenType::Sbe, regex(R"(^\])") },
			{ TokenType::Brs, regex(R"(^\{)") },
			{ TokenType::Bre, regex(R"(^\})") },
			{ TokenType::Int, regex(R"(^int)") },
			{ TokenType::blank, regex(R"(^\s+)")},
			{ TokenType::Sep, regex(R"(^;)")},

			{ TokenType::Ident, regex(R"(^[a-zA-Z_]+[a-zA-Z_0-9]*)")},
			{ TokenType::Interger, regex(R"(^[0-9]+)")},
		};
	}


	template<typename T>
	wchar_t PopCharFromIterU8(T& p)
	{
		int ch = (uint8_t)p[0];
		if ((ch & 0x80) == 0) // 1
		{
			p += 1;
			return (wchar_t)ch;
		}
		if ((ch & 0x1F) == 0xC0)// 2
		{
			int ch1 = (uint8_t)p[1];
			ch = (ch & 0x1F) << 5 | (ch1 & 0x3F);
			p += 2;
			return(wchar_t)ch;
		}
		if ((ch & 0xF0) == 0xE0)// 3
		{
			int ch1 = (uint8_t)p[1];
			int ch2 = (uint8_t)p[2];
			ch = (ch & 0x1F) << 12 | (ch1 & 0x3F) << 6 | (ch2 & 0x3F);
			p += 3;
			return (wchar_t)ch;
		}
	}
	

	std::deque<Lex::Token> LexParser::GetTokens()
	{
		std::deque<Lex::Token> tokens;

		auto _linec = 0ul;
		auto _charc = 0ul;

		string lineContent;
		while (getline(byteStream, lineContent))
		{
			_linec += 1;
			_charc = 1;

			string::const_iterator pread = lineContent.begin();
			string::const_iterator end = lineContent.end();

			while (pread != end)
			{
				smatch m;
				for (const auto& p : Lex::RegexList)
				{
					const auto& type = p.first;
					const auto& e = p.second;
					if (regex_search(pread, end, m, e))
					{
						Lex::Token token;
						token.type = type;
						token._line = _linec;
						token._start = _charc;

						switch (type)
						{
						case Lex::TokenType::Ident:
							token.value = m.str();
						default:
							tokens.emplace_back(move(token));
							_charc += m.length();
							pread += m.length();
							break;

						case Lex::TokenType::comment_l_b:
						{
							const auto rend = regex(R"(\*/)");
							while (!regex_search(pread, end, m, rend))
							{
								getline(byteStream, lineContent);
								if (byteStream.eof())
								{
									Console::Log("In File", fileName,
										to_string(_linec) + ":" + to_string(_charc),
										"Comment at the end of the file is not closed!", Level::Warning);
									return tokens;
								}
								pread = lineContent.begin();
								end = lineContent.end();
								_linec += 1;
								_charc = 1;
							}
							_charc += m.position();
							pread += m.position();
						}
						case Lex::TokenType::comment_h:
						case Lex::TokenType::blank:
							_charc += m.length();
							pread += m.length();
							break;
						}
						break;
					}
				}
				if (m.empty())
				{
					Console::Log("In File", fileName,
						to_string(_linec) + ":" + to_string(_charc),
						" Found Unexpected char", PopCharFromIterU8(pread),
						"skiped", Level::Warning);
				}
			}
		}
		tokens.push_back(Lex::Token({ Lex::TokenType::End }));
		return tokens;
	}

}

