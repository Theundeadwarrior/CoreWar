#pragma once
#include "UnitTestsFramework.h"
#include "Parser\ExpressionEvaluator.h"

#define EPSILON 0.0005
#define EQUALS_WITH_EPSILON(a,b) (((a) - (b)) < EPSILON || ((b) - (a)) < EPSILON)

TEST_CASE(SimpleValue)
{
	std::string integer = "4";
	std::string floating = "4.56";
	Engine::ExpressionEvaluator evaluator;
	
	int intResult = (int)evaluator.EvaluateExpression(integer);
	CHECK(intResult == 4);

	float floatResult = evaluator.EvaluateExpression(floating);
	CHECK(EQUALS_WITH_EPSILON(floatResult, 4.56));
}

TEST_CASE(SimpleSum)
{
	Engine::ExpressionEvaluator evaluator;

	std::string expr = "1+32";
	int result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 33);
	
	expr = "1-32";
	result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == -31);

	expr = "-5 + 10";
	result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 5);
}

TEST_CASE(SimpleMultiplication)
{
	Engine::ExpressionEvaluator evaluator;

	std::string expr = "4 * 20";
	int result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 80);

	expr = "25 / 5";
	result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 5);
}

TEST_CASE(PrecedenceOfOperation)
{
	Engine::ExpressionEvaluator evaluator;

	std::string expr = "4 * 20 + 4";
	int result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 84);

	expr = "4 + 4 * 20";
	result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 84);
}

TEST_CASE(ParenthesisPrecedence)
{
	Engine::ExpressionEvaluator evaluator;

	std::string expr = "(4 * 20) + 4";
	int result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 84);

	expr = "4 * (20 + 4)";
	result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 96);
}

TEST_CASE(NegativeParenthesis)
{
	Engine::ExpressionEvaluator evaluator;

	std::string expr = "-(4 * 2) + 9";
	int result = (int)evaluator.EvaluateExpression(expr);
	CHECK(result == 1);
}