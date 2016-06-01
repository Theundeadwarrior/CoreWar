#include <RedCodeEngine.h>
#include <xutility>
#include <assert.h>

namespace Engine
{

	Core::Core(const Instruction& initialInstruction, unsigned int coreSize)
	{
		m_CoreSize = coreSize;
		m_InstructionBuffer.resize(coreSize);
		Reset(initialInstruction);
	}

	Core::~Core()
	{
	}

	void Core::Reset(const Instruction& instruction)
	{
		std::fill(m_InstructionBuffer.begin(), m_InstructionBuffer.end(), instruction);
	}

	Instruction Core::GetInstruction(int offset) const
	{
		int index = ((offset % m_CoreSize) + m_CoreSize) % m_CoreSize;
		return m_InstructionBuffer[index];
	}

	void Core::SetInstruction(const Instruction instruction, int offset)
	{
		m_InstructionBuffer[offset % m_CoreSize] = instruction;
	}


	MARS::MARS()
		: m_Core(Instruction(), 8000)
	{

	}

	void MARS::LoadInstructionList(const eastl::vector<Instruction>& instructions, int offset)
	{
		for (auto ins : instructions)
		{
			m_Core.SetInstruction(ins, offset);
		}
	}

	void MARS::Step()
	{
		for (auto* w : m_Warriors)
		{
			if (w->IsAlive())
			{
				ExecuteInstruction(w, w->GetCurrentInstruction());
			}
		}
	}

	void MARS::ExecuteInstruction(RuntimeWarrior* w, int offset)
	{
		Instruction instruction = m_Core.GetInstruction(offset);

		int ap, bp = 0;

		switch (instruction.m_AMode)
		{
		case EMode::EMode_Immediate:
			break;
		case EMode::EMode_Direct:
			ap = offset;
			break;
		default:
			assert("This is not implemented");
		}

		switch (instruction.m_BMode)
		{
		case EMode::EMode_Immediate:
			break;
		case EMode::EMode_Direct:
			bp = offset;
			break;
		default:
			assert("This is not implemented");
		}



		switch (instruction.m_Opcode)
		{
		case (EOpCode::EOpCode_DAT):
			break;
		case (EOpCode::EOpCode_MOV):
			if (instruction.m_Modifier == EModifier::EModifier_A)
				w->m_TaskQueue.push(offset + 1);

		}
		return;

	}

}

