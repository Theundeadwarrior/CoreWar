#include <RedCodeEngine.h>

#include <new>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line){ return malloc(size); };
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line){ return malloc(size); };

#ifndef UNIT_TEST

int main()
{
	static Engine::Instruction Invalid_Instruction;
	Invalid_Instruction.m_Opcode = Engine::EOpCode::EOpCode_Invalid;

	Engine::Core core(Engine::Instruction(), 8000);

	core.SetInstruction(Invalid_Instruction, 400);
	core.SetInstruction(Invalid_Instruction, 8000);

	Engine::MARS mars;
	mars.Step();


	//printf("Hello world!");
	return 0;
}
#endif