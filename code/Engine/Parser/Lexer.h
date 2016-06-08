#pragma once
#include <string>

namespace Engine
{
	class Token
	{
	public:
		enum Type
		{
			e_EOL = -2,
			e_EOF = -1,
			e_NA = 0,
			e_SemiColon = 3,			// ;
			e_Comma = 4,				// ,
			e_Dot = 5,					// .
			e_Mode = 6,
			//e_Sharp = 6,				// #
			//e_Dollar = 7,				// $
			//e_AtSign = 8,				// @
			//e_SmallerThan = 9,			// <
			//e_BiggerThan = 10,			// >
			e_ExpressionOperation = 11,
			//e_Plus = 11,				// +
			//e_Minus = 12,				// -
			//e_Percent = 13,				// %
			//e_Division = 14,			// /
			//e_Star = 15,				// *


			e_OpCode = 30,
			e_OpCodeModifier = 31,
			e_Number = 99,
			e_AlphaNumeric = 100,
		};

		Token(Type type, const std::string name)
			: m_Name(name)
			, m_Type(type)
		{}

		std::string m_Name;
		Type m_Type;
	};

	class Lexer
	{
	public:
		Lexer();
		//Lexer(const std::string& str);
		~Lexer();

		void ResetLexer(const std::string& str);

		Token NextToken();

	private:
		Token AlphaNumeral();
		Token Number();

		void Consume();
		void WhiteSpace();

		std::string m_InputString;
		const char* m_EndOfString;
		const char* m_CurrentChar;
		char m_EOF;
	};
}

