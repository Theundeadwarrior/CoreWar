#include "AssemblyFileParser.h"
#include <algorithm>
#include <cctype>
#include <assert.h>


namespace Engine
{
	RedCodeParser::RedCodeParser()
		: m_Lookahead(Token::e_NA, "")
	{
		//m_Lexer.ResetLexer(text);
		//Consume();
	}

	RedCodeParser::~RedCodeParser()
	{
	}

	void RedCodeParser::Reset(const eastl::string & text)
	{
		m_Lexer.ResetLexer(text);
		Consume();
	}
	

	void RedCodeParser::AssemblyFile()
	{
		List();

		// Only resolve if there were no error parsing
		if (::Core::g_GeneralLogger.GetErrorCount() == 0)
			ResolveAssemblyInstructions(m_AssemblyInstructions);

		// Don't return any instructions if there are errors.
		if (::Core::g_GeneralLogger.GetErrorCount() != 0)
			m_ResolvedInstructions.clear();
	}

	void RedCodeParser::List()
	{
		while (!IsParsingDone())
		{
			Line();
		}
	}

	void RedCodeParser::Line()
	{
		if (m_Lookahead.m_Type == Token::e_SemiColon)
			Comment();
		else
			Instruction();
	}

	void RedCodeParser::Comment()
	{
		Match(Token::e_SemiColon);
		while (m_Lookahead.m_Type != Token::e_EOL && !IsParsingDone())
			Consume();
		Consume();
	}

	inline void RedCodeParser::Instruction()
	{
		AssemblyFileInstruction ins;

		while (m_Lookahead.m_Type != Token::e_OpCode)
		{
			// label list first
			ins.m_Labels.append(m_Lookahead.m_Name + " ");
			m_LabelToInstructionNumber[m_Lookahead.m_Name] = (unsigned int)m_AssemblyInstructions.size();
			Consume();
		}

		ins.m_OpCode = g_SymbolHelper.GetOpCodeFromString(m_Lookahead.m_Name);
		Consume();

		if (m_Lookahead.m_Type == Token::e_Dot)
		{
			Consume();
			if (!g_SymbolHelper.ModifierExistsFromString(m_Lookahead.m_Name))
			{
				kamiLogError("Invalid Modifier parsed in input file.");
				ins.m_Modifier = EModifier::EModifier_Invalid;
			}
			else
			{
				ins.m_Modifier = g_SymbolHelper.GetModifierFromString(m_Lookahead.m_Name);
			}
			Consume();
			
		}

		bool isFirstExpression = true;
		while(m_Lookahead.m_Type != Token::e_EOL && m_Lookahead.m_Type != Token::e_EOF && m_Lookahead.m_Type != Token::e_SemiColon)
		{
			if (m_Lookahead.m_Type == Token::e_Mode)
			{
				if (isFirstExpression)
					ins.m_Mode1 = g_SymbolHelper.GetModeFromString(m_Lookahead.m_Name);
				else
					ins.m_Mode2 = g_SymbolHelper.GetModeFromString(m_Lookahead.m_Name);
			}
			else if (m_Lookahead.m_Type == Token::e_Comma)
			{
				isFirstExpression = false;
			}
			else
			{
				if (isFirstExpression)
					ins.m_Expr1.append(m_Lookahead.m_Name);
				else
					ins.m_Expr2.append(m_Lookahead.m_Name);
			}
			Consume();
		}

		if (m_Lookahead.m_Type == Token::e_SemiColon)
		{
			Comment();
		}

		m_AssemblyInstructions.push_back(ins);
	}

	int RedCodeParser::GetLabelValueFromString(const eastl::string& str)
	{
		auto it = m_LabelToInstructionNumber.find(str);
		if (it != m_LabelToInstructionNumber.end())
			return it->second;
		else
		{
			kamiLogError("Invalid label! Couldn't resolve. Verify your assembly file.");
		}
		return 0;
	}

	int RedCodeParser::EvaluateExpression(const eastl::string& expr)
	{
		return 0;
	}

	void RedCodeParser::ResolveAssemblyInstructions(const eastl::vector<AssemblyFileInstruction>& input)
	{
		char modes[5]{ '#', '$', '@', '<', '>' };
		char exprOp[5]{ '+', '-', '*', '/', '%' };

		m_ResolvedInstructions.reserve(m_AssemblyInstructions.size());

		for (unsigned int currentInstructionNumber = 0; currentInstructionNumber < input.size(); ++currentInstructionNumber)
		{
			auto i = input[currentInstructionNumber];
			Engine::Instruction resolvedInstruction;
			resolvedInstruction.m_Opcode = i.m_OpCode;
			resolvedInstruction.m_Modifier = i.m_Modifier;
			resolvedInstruction.m_AMode = i.m_Mode1;
			resolvedInstruction.m_BMode = i.m_Mode2;
			resolvedInstruction.m_Adress1 = EvaluateExpression(i.m_Expr1);
			resolvedInstruction.m_Adress2 = EvaluateExpression(i.m_Expr2);

			m_ResolvedInstructions.push_back(resolvedInstruction);
		}
	}

	bool RedCodeParser::IsParsingDone()
	{
		if (m_Lookahead.m_Type == Token::e_EOF || ::Core::g_GeneralLogger.GetErrorCount() != 0)
			return true;
		return false;
	}
}