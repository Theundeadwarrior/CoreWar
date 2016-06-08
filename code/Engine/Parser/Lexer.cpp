#include "Lexer.h"
#include <EASTL/string.h>
#include <assert.h>

namespace Engine
{
	//Lexer::Lexer(const std::string & str)
	//	: m_InputString(str)
	//	, m_EndOfString(m_InputString.end())
	//	, m_CurrentChar(m_InputString.begin())
	//	, m_EOF((char)-1)
	//{
	//}

	Lexer::Lexer() 
		: m_EOF((char)-1) 
	{}

	Lexer::~Lexer()
	{
	}

	void Lexer::ResetLexer(const std::string & str)
	{
		m_InputString = str;
		m_EndOfString = &m_InputString.back();
		m_CurrentChar = &m_InputString.front();
	}

	inline void Lexer::Consume()
	{
		m_CurrentChar++;
		if (m_CurrentChar > m_EndOfString)
			m_CurrentChar = &m_EOF;
	}

	void Lexer::WhiteSpace()
	{
		while (*m_CurrentChar == ' ' || *m_CurrentChar == '\t')
			Consume();
	}

	Token Lexer::AlphaNumeral()
	{
		std::string name = "";
		while (isalnum(*m_CurrentChar))
		{
			name.push_back(*m_CurrentChar);
			Consume();
		}
		if (name == "DAT" || name == "MOV" ||
			name == "ADD" || name == "SUB" ||
			name == "MUL" || name == "DIV" ||
			name == "MOD" || name == "JMP" ||
			name == "JMZ" || name == "JMN" ||
			name == "DJN" || name == "CMP" ||
			name == "SLT" || name == "SPL" ||
			name == "ORG" || name == "EQU" || name == "END")
		{
			return Token(Token::e_OpCode, name);
		}
		return Token(Token::e_AlphaNumeric, name);
	}

	Token Lexer::Number()
	{
		std::string number = "";
		while (isdigit(*m_CurrentChar))
		{
			number.push_back(*m_CurrentChar);
			Consume();
		}
		
		return Token(Token::e_Number, number);
	}

	Token Lexer::NextToken()
	{
		while (m_CurrentChar != &m_EOF)
		{
			switch (*m_CurrentChar)
			{
			case ' ': case '\t':
				WhiteSpace(); 
				break;
			case'\n': case '\r':
			{
				Consume();
				if (*m_CurrentChar == '\n')
					Consume();
				return Token(Token::e_EOL, "EOL");
			}
			case ';':
				Consume();
				return Token(Token::e_SemiColon, ";");

			case '.' :
				Consume();
				return Token(Token::e_Dot, ".");
			
			case ',':
				Consume();
				return Token(Token::e_Comma, ",");

			// Addressing Modes
			case '#':
			case '$':
			case '@':
			case '<':
			case '>':
			{
				const char currentChar = *m_CurrentChar;
				Consume();
				return Token(Token::e_Mode, std::string(&currentChar, 1));
			}

			//case '#':
			//	Consume();
			//	return Token(Token::e_Sharp, "#");
			//	
			//case '$':
			//	Consume();
			//	return Token(Token::e_Dollar, "$");

			//case '@':
			//	Consume();
			//	return Token(Token::e_AtSign, "@");

			//case '<':
			//	Consume();
			//	return Token(Token::e_SmallerThan, "<");

			//case '>':
			//	Consume();
			//	return Token(Token::e_BiggerThan, ">");

			// Math Operators
			case '%':
			case '+':
			case '-':
			case '*':
			case '/':
			{
				const char currentChar = *m_CurrentChar;
				Consume();
				return Token(Token::e_ExpressionOperation, std::string(&currentChar, 1));
			}

			//case '%':
			//	Consume();
			//	return Token(Token::e_Percent, "%");

			//case '+':
			//	Consume();
			//	return Token(Token::e_Plus, "+");

			//case '-':
			//	Consume();
			//	return Token(Token::e_Minus, "-");

			//case '*':
			//	Consume();
			//	return Token(Token::e_Star, "*");

			//case '/':
			//	Consume();
			//	return Token(Token::e_Division, "/");

			default:
				if (isalpha(*m_CurrentChar))
					return AlphaNumeral();
				else if (isdigit(*m_CurrentChar))
					return Number();
				assert(false && "not implemented");
			}
		}

		return Token(Token::e_EOF, "EOF");
	}
}
