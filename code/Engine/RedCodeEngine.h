#ifndef INCLUDE_RED_CODE_PARSER_H
#define INCLUDE_RED_CODE_PARSER_H

#pragma once
#include <EASTL/vector.h>
#include <EASTL/queue.h>
#include <string>

namespace Engine
{
	enum class EOpCode
	{
		EOpCode_DAT, EOpCode_MOV, EOpCode_ADD,
		EOpCode_SUB, EOpCode_MUL, EOpCode_DIV,
		EOpCode_MOD, EOpCode_JMP, EOpCode_JMZ,
		EOpCode_JMN, EOpCode_DJN, EOpCode_CMP,
		EOpCode_SLT, EOpCode_SPL, EOpCode_ORG,
		EOpCode_Invalid
	};

	enum class EModifier
	{
		EModifier_A, EModifier_B, EModifier_AB, EModifier_BA, EModifier_F, EModifier_X, EModifier_I,
		EModifier_Invalid
	};

	enum class EMode
	{
		EMode_Immediate, EMode_Direct, EMode_Indirect, EMode_PredIndirect, EMode_PostIndirect, EMode_Invalid
	};

	struct Instruction
	{
		Instruction(){}


		EOpCode m_Opcode;
		EModifier m_Modifier;
		EMode m_AMode;
		int m_Adress1; // needs to change to a pointer of some sort...
		EMode m_BMode;
		int m_Adress2; // needs to change to a pointer of some sort...

		bool operator==(const Instruction& other) const
		{
			if (m_Opcode == other.m_Opcode &&
				m_Modifier == other.m_Modifier &&
				m_AMode == other.m_AMode &&
				m_BMode == other.m_BMode &&
				m_Adress1 == other.m_Adress1 &&
				m_Adress2 == other.m_Adress2)
			{
				return true;
			}
			return false;
		}

#ifdef UNIT_TEST
		Instruction(const std::string& text)
		{
		}
#endif

	};

	struct RedCodeEngineInitParams
	{
		Instruction m_InitialInstruction; // Initial instruction to fill the core before loading warriors
		unsigned int m_CoreSize; // Size of the number of instruction for a core
		unsigned int m_CyclesBeforeTie; // Max number of rounds
		unsigned int m_InstructionLimitPerWarrior; // Max number of instruction per file
		unsigned int m_MinSeparation; // Minimum distance for warrior start position
		unsigned int m_NumWarriors;

		// TODO
		unsigned int m_ReadDistance;
		unsigned int m_WriteDistance;
	};

	class Core
	{
	public:
		Core(const Instruction& initialInstruction, unsigned int coreSize);
		~Core();
		void Reset(const Instruction& instruction);

		Instruction GetInstruction(int offset) const;
		void SetInstruction(const Instruction instruction, int offset);

	private:
		eastl::vector<Instruction> m_InstructionBuffer;
		int m_CoreSize;
	};

	class RuntimeWarrior
	{
	public:
		bool IsAlive()
		{
			return m_TaskQueue.empty() == false;
		}
		int GetCurrentInstruction()
		{
			if (m_TaskQueue.empty() == false)
			{
				int currentInstruction = m_TaskQueue.front();
				m_TaskQueue.pop();
				return currentInstruction;
			}
			return -1;
		}

		eastl::queue<int> m_TaskQueue;

	};

	// TODO
	// loader
	class MARS
	{
	public:
		MARS();
		void Step();


	protected:
		void ExecuteInstruction(RuntimeWarrior* w, int offset);
		void LoadInstructionList(const eastl::vector<Instruction>& instructions, int offset);

	private:
		Core m_Core;
		eastl::vector<RuntimeWarrior*> m_Warriors;
	};


}

#endif