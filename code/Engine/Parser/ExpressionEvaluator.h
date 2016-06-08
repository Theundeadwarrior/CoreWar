#pragma once
#include <string>
#include "Lexer.h"

namespace Engine
{
	class ExpressionEvaluator
	{
	public:
		float EvaluateExpression(const std::string& expr);

	private:
		float Expression();
		float Term();
		float Factor();

	private:
		Lexer m_Lexer;
	};

	inline float ExpressionEvaluator::Factor()
	{
		return 0;
		//Token t = m_Lexer.NextToken();
		//if (t.m_Type == Token::e_Number)
		//	return std::stoi(t.m_Name);
	}

	inline float ExpressionEvaluator::Term()
	{
		float result = Factor();

	}

	inline float ExpressionEvaluator::Expression()
	{
		float result = Term();
	}

	inline float ExpressionEvaluator::EvaluateExpression(const std::string & expr)
	{
		m_Lexer.ResetLexer(expr);
		Expression();
	}
}