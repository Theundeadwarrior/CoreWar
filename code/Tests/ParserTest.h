#pragma once

#include "UnitTestsFramework.h"
#include "Parser\Lexer.h"
#include "Parser\AssemblyFileParser.h"
#include "ParserMock.h"

using namespace Engine;

TEST_CASE(Lexer_Name)
{
	Lexer lexer;
	lexer.ResetLexer("AlphaNumericTest12345");
	Token token = lexer.NextToken();

	CHECK(token.m_Type == Token::e_AlphaNumeric);
	CHECK(token.m_Name == "AlphaNumericTest12345");

	lexer.ResetLexer("  alpha	0000000");
	token = lexer.NextToken();

	CHECK(token.m_Type == Token::e_AlphaNumeric);
	CHECK(token.m_Name == "alpha");

	token = lexer.NextToken();
	CHECK(token.m_Type == Token::e_Number);
	CHECK(token.m_Name == "0000000");
}

TEST_CASE(Parser_Reset_Resets_Lookahead)
{
	FakeParser parser("Word1;");
	Token t = parser.GetLookAhead();
	CHECK(t.m_Type == Token::e_AlphaNumeric);
	CHECK(t.m_Name == "Word1");

	parser.Reset("; Word2");
	t = parser.GetLookAhead();
	CHECK(t.m_Type == Token::e_SemiColon);
}

TEST_CASE(Parser_Consume_Advances_LookAhead)
{
	FakeParser parser("Word1 Word2");
	Token t = parser.GetLookAhead();
	CHECK(t.m_Type == Token::e_AlphaNumeric);
	CHECK(t.m_Name == "Word1");

	parser.FakeConsume();
	t = parser.GetLookAhead();
	CHECK(t.m_Type == Token::e_AlphaNumeric);
	CHECK(t.m_Name == "Word2");
}

TEST_CASE(Parser_Comment)
{
	// Parsing a comment should ignore everything else on the line and return a lookahead starting at the new line
	FakeParser parser("; test\n Test");
	parser.FakeComment();
	Token t = parser.GetLookAhead();
	CHECK(t.m_Type == Token::e_AlphaNumeric);

	parser.Reset("This ; comment \n AlphaNumeric");

	parser.FakeConsume();
	parser.FakeComment();
	t = parser.GetLookAhead();
	CHECK(t.m_Type == Token::e_AlphaNumeric);
	CHECK(t.m_Name == "AlphaNumeric");
}

TEST_CASE(Parser_OpCode)
{
	FakeParser parser("DAT 0, 1 ; This is a comment \n");
	Token t = parser.GetLookAhead();

	CHECK(t.m_Type == Token::e_OpCode);
	CHECK(t.m_Name == "DAT");

	parser.Reset("DATA 0, 1 ; This is a comment \n");
	t = parser.GetLookAhead();

	CHECK(t.m_Type == Token::e_AlphaNumeric);
	CHECK(t.m_Name == "DATA");
}

TEST_CASE(Parser_AssemblyFile)
{
	eastl::vector<Engine::Instruction> parsedInstruction;

	FakeParser parser("DAT.X #0,#0 \nstart DAT.X #  1 + 4,$  1 ; test \n test MOV.AB #0*0 +4,$start + 5 ; blabla \n");
	parser.ParseAssemblyFile();
	parser.GetResolvedInstructions(parsedInstruction);

	CHECK(parsedInstruction[1].m_Opcode == EOpCode::EOpCode_DAT);
	CHECK(parsedInstruction[1].m_Adress1 == 5);
	CHECK(parsedInstruction[1].m_Adress2 == 1);
	CHECK(parsedInstruction[1].m_Modifier == EModifier::EModifier_X);
	CHECK(parsedInstruction[1].m_AMode == EMode::EMode_Immediate);
	CHECK(parsedInstruction[1].m_BMode == EMode::EMode_Direct);

	CHECK(parsedInstruction[2].m_Adress1 == 4);
	CHECK(parsedInstruction[2].m_Adress2 == 6);
}


