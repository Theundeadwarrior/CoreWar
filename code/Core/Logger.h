#pragma once
#include <EASTL\string.h>
#include <EASTL\vector.h>

namespace Core
{
	class ILogger
	{
	public:
		ILogger() {};
		virtual ~ILogger() = 0 {};
		virtual void LogError(const eastl::string& msg) {};
		virtual void LogWarning(const eastl::string& msg) {};
		virtual void LogMessage(const eastl::string& msg) {};
	};

	class Logger : public ILogger
	{
	public:
		Logger();
		virtual ~Logger();

		void LogError(const eastl::string& msg) override;
		void LogWarning(const eastl::string& msg) override;
		void LogMessage(const eastl::string& msg) override;

		unsigned int GetErrorCount();
		unsigned int GetWarningCount();

	private:
		eastl::vector<eastl::string> m_Errors;
		eastl::vector<eastl::string> m_Warnings;
		eastl::vector<eastl::string> m_Messages;
	};
}
