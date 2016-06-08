#pragma once
#include <string>
#include "Lexer.h"

namespace Engine
{
	class ExpressionEvaluator
	{
	public:
		ExpressionEvaluator() : m_LookAheadToken(Token::e_NA, "") {}
		float EvaluateExpression(const std::string& expr);

	private:
		float Expression();
		float Term();
		float Factor();

		void Consume();

	private:
		Token m_LookAheadToken;
		Lexer m_Lexer;
	};

	inline void ExpressionEvaluator::Consume()
	{
		m_LookAheadToken = m_Lexer.NextToken();
	}

	inline float ExpressionEvaluator::Factor()
	{
		bool isNeg = false;
		if (m_LookAheadToken.m_Name == "-")
		{
			Consume();
			isNeg = true;
		}
		if (m_LookAheadToken.m_Type == Token::e_Number)
		{
			std::string num = m_LookAheadToken.m_Name;
			Consume();
			if (m_LookAheadToken.m_Type == Token::e_Dot)
			{
				Consume();
				num += "." + m_LookAheadToken.m_Name;
				Consume();
				return isNeg ? -std::stof(num) : std::stof(num);
			}
			return (float)(isNeg ? -std::stoi(num) : std::stoi(num));
		}
		else if (m_LookAheadToken.m_Name == "(")
		{
			Consume();
			float tempResult = Expression();
			Consume(); // for the ")"
			return isNeg ? -tempResult : tempResult;
		}
		return 0;
	}

	inline float ExpressionEvaluator::Term()
	{
		float result = Factor();
		if (m_LookAheadToken.m_Name == "*")
		{
			Consume();
			return result * Term();
		}
		else if (m_LookAheadToken.m_Name == "/")
		{
			Consume();
			return result / Term();
		}
		else if (m_LookAheadToken.m_Name == "%")
		{
			Consume();
			return (float)((int)result % (int)Term());
		}
		return result;

	}

	inline float ExpressionEvaluator::Expression()
	{
		float result = Term();
		if (m_LookAheadToken.m_Name == "+")
		{
			Consume();
			return result + Expression();
		}
		else if (m_LookAheadToken.m_Name == "-")
		{
			Consume();
			return result - Expression();
		}
		return result;
	}

	inline float ExpressionEvaluator::EvaluateExpression(const std::string & expr)
	{
		m_Lexer.ResetLexer(expr);
		Consume();
		return Expression();
	}
}