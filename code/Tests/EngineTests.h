#pragma once

#include "UnitTestsFramework.h"
#include "RedCodeEngine.h"

using namespace Engine;

TEST_CASE(Core_Is_Circular)
{
	Engine::Core core(Instruction(), 10);

	// Instruction at 9 is the same as 19,29 or -1,-11,-21...
	Instruction ins;
	ins.m_Opcode = EOpCode::EOpCode_ADD;

	core.SetInstruction(ins, 9);

	CHECK(core.GetInstruction(9) == ins);
	CHECK(core.GetInstruction(19) == ins);
	CHECK(core.GetInstruction(29) == ins);
	CHECK(core.GetInstruction(-1) == ins);
	CHECK(core.GetInstruction(-11) == ins);
	CHECK(core.GetInstruction(-21) == ins);
}

TEST_CASE(MOV_0_1)
{
	Engine::Core core(Instruction(), 2);
}
