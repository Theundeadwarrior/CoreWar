#pragma once
#include "UnitTestsFramework.h"
#include "Parser\Lexer.h"
#include "Parser\AssemblyFileParser.h"
#include "ParserMock.h"
#include "CoreUtilities.h"

TEST_CASE(Parser_Fail1)
{
	eastl::vector<Engine::Instruction> parsedInstruction;
	FakeParser parser("start DAT.T #  0,$  1 ; test \n test MOV.AB 0,start ; blabla \n");
	parser.AssemblyFile();
	parser.GetResolvedInstructions(parsedInstruction);


	unsigned int errorCount = ::Core::g_GeneralLogger.GetErrorCount();
	CHECK(errorCount == 1);
	CHECK(parsedInstruction.size() == 0);
}
