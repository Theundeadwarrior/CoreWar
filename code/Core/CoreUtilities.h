#pragma once
#include "Logger.h"

#define kamiLogError(errorMessage) ::Core::g_GeneralLogger.LogError(errorMessage)
#define kamiLogWarning(warningMessage) ::Core::g_GeneralLogger.LogWarning(errorMessage)

namespace Core
{
	extern Logger g_GeneralLogger;
}
