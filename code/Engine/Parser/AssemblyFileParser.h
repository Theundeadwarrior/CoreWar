#pragma once

#include "Lexer.h"
#include "RedCodeEngine.h"
#include "CoreUtilities.h"

//namespace eastl
//{	
//	template<typename T, typename Allocator> class basic_string;
//	class allocator;
//	typedef basic_string<char, allocator> string;
//}

#include <EASTL/string.h>
#include <EASTL/map.h>

#include <EASTL/vector.h>

namespace Engine
{
	struct SymbolHelper
	{
		SymbolHelper()
		{
			m_SymbolToOpCode["DAT"] = EOpCode::EOpCode_DAT;
			m_SymbolToOpCode["MOV"] = EOpCode::EOpCode_MOV;
			m_SymbolToOpCode["ADD"] = EOpCode::EOpCode_ADD;
			m_SymbolToOpCode["SUB"] = EOpCode::EOpCode_SUB;
			m_SymbolToOpCode["MUL"] = EOpCode::EOpCode_MUL;
			m_SymbolToOpCode["DIV"] = EOpCode::EOpCode_DIV;
			m_SymbolToOpCode["MOD"] = EOpCode::EOpCode_MOD;
			m_SymbolToOpCode["JMP"] = EOpCode::EOpCode_JMP;
			m_SymbolToOpCode["JMZ"] = EOpCode::EOpCode_JMZ;
			m_SymbolToOpCode["JMN"] = EOpCode::EOpCode_JMN;
			m_SymbolToOpCode["DJN"] = EOpCode::EOpCode_DJN;
			m_SymbolToOpCode["CMP"] = EOpCode::EOpCode_CMP;
			m_SymbolToOpCode["STL"] = EOpCode::EOpCode_SLT;
			m_SymbolToOpCode["SPL"] = EOpCode::EOpCode_SPL;
			m_SymbolToOpCode["ORG"] = EOpCode::EOpCode_ORG;

			m_SymbolToModifier["A"] = EModifier::EModifier_A;
			m_SymbolToModifier["B"] = EModifier::EModifier_B;
			m_SymbolToModifier["AB"] = EModifier::EModifier_AB;
			m_SymbolToModifier["BA"] = EModifier::EModifier_BA;
			m_SymbolToModifier["F"] = EModifier::EModifier_F;
			m_SymbolToModifier["X"] = EModifier::EModifier_X;
			m_SymbolToModifier["I"] = EModifier::EModifier_I;

			m_SymbolToMode["#"] = EMode::EMode_Immediate;
			m_SymbolToMode["$"] = EMode::EMode_Direct;
			m_SymbolToMode["@"] = EMode::EMode_Indirect;
			m_SymbolToMode["<"] = EMode::EMode_PredIndirect;
			m_SymbolToMode[">"] = EMode::EMode_PostIndirect;
		}

		EOpCode GetOpCodeFromString(const eastl::string& string)
		{
			return m_SymbolToOpCode[string];
		}

		EModifier GetModifierFromString(const eastl::string& string)
		{
			return m_SymbolToModifier[string];
		}

		EMode GetModeFromString(const eastl::string& string)
		{
			return m_SymbolToMode[string];
		}

		bool ModeExistsFromString(const eastl::string& string)
		{
			return m_SymbolToMode.find(string) != m_SymbolToMode.end();
		}
		
		bool ModifierExistsFromString(const eastl::string& string)
		{
			return m_SymbolToModifier.find(string) != m_SymbolToModifier.end();
		}

		eastl::map<eastl::string, EOpCode> m_SymbolToOpCode;
		eastl::map<eastl::string, EModifier> m_SymbolToModifier;
		eastl::map<eastl::string, EMode> m_SymbolToMode;
	};

	static SymbolHelper g_SymbolHelper;

	class AssemblyFileInstruction
	{
	public:
		AssemblyFileInstruction()
			: m_Labels("")
			, m_OpCode(EOpCode::EOpCode_Invalid)
			, m_Modifier(EModifier::EModifier_Invalid)
		{}

		eastl::string m_Labels;
		EOpCode m_OpCode;
		EModifier m_Modifier;
		EMode m_Mode1, m_Mode2;
		eastl::string m_Expr1, m_Expr2;
	};

	class RedCodeParser
	{
	public:
		RedCodeParser();
		~RedCodeParser();

		void Reset(const eastl::string& text);

		void ParseAssemblyFile();

		void GetResolvedInstructions(eastl::vector<Engine::Instruction>& out) { out = m_ResolvedInstructions; }

	protected:
		void Match(Token::Type type)
		{
			if (m_Lookahead.m_Type == type)
				Consume();
			else
			{
				kamiLogError("Couldn't match the right token type");
				Consume();
			}
		}

		void List();
		void Line();
		void Comment();
		void Instruction();

		void Consume() { m_Lookahead = m_Lexer.NextToken(); }

		void ResolveAssemblyInstructions(const eastl::vector<AssemblyFileInstruction>& input);

		Lexer m_Lexer;
		Token m_Lookahead;

	private:
		bool IsParsingDone();
		int GetLabelValueFromString(const eastl::string & str);
		static int EvaluateExpression(const eastl::string& expr);
		void ResolveAssemblyInstruction(const AssemblyFileInstruction& input, Engine::Instruction& output);


	private:
		eastl::vector<AssemblyFileInstruction> m_AssemblyInstructions;
		eastl::map<eastl::string, unsigned int> m_LabelToInstructionNumber;
		eastl::vector<Engine::Instruction> m_ResolvedInstructions;
	};
}
