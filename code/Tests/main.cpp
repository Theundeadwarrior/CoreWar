#include "CoreTests.h"
#include "EngineTests.h"
#include "ParserTest.h"
#include "ExpressionEvaluatorTest.h"
#include "ParserFailedTest.h"
#include "UnitTestsFramework.h"
#include "Logger.h"

#include <new>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line){ return malloc(size); };
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line){ return malloc(size); };


int main()
{
	::Core::g_GeneralLogger;
	s_TestRegistry.RunAllTests();
	return 0;
}

