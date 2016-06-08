#include "Logger.h"

namespace Core
{
	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
	}

	void Logger::LogError(const std::string & msg)
	{
		m_Errors.push_back(msg);
	}

	void Logger::LogWarning(const std::string & msg)
	{
		m_Warnings.push_back(msg);
	}

	void Logger::LogMessage(const std::string & msg)
	{
		m_Messages.push_back(msg);
	}

	unsigned int Logger::GetErrorCount()
	{
		return (unsigned int)m_Errors.size();
	}

	unsigned int Logger::GetWarningCount()
	{
		return (unsigned int)m_Warnings.size();
	}
}
