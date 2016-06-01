#pragma once

#include "UnitTestsFramework.h"
#include "Parser\AssemblyFileParser.h"

using namespace Engine;

class FakeParser : public RedCodeParser
{
public:
	FakeParser(const eastl::string& text)
		: RedCodeParser()
	{
		Reset(text);
	}

	void FakeComment()
	{
		Comment();
	}

	void FakeConsume()
	{
		Consume();
	}

	Token GetLookAhead()
	{
		return m_Lookahead;
	}
};