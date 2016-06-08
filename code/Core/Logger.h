#pragma once
#include <string>
#include <EASTL\vector.h>

namespace Core
{
	class ILogger
	{
	public:
		ILogger() {};
		virtual ~ILogger() = 0 {};
		virtual void LogError(const std::string& msg) {};
		virtual void LogWarning(const std::string& msg) {}; 
		virtual void LogMessage(const std::string& msg) {};
	};

	class Logger : public ILogger
	{
	public:
		Logger();
		virtual ~Logger();

		void LogError(const std::string& msg) override;
		void LogWarning(const std::string& msg) override;
		void LogMessage(const std::string& msg) override;

		unsigned int GetErrorCount();
		unsigned int GetWarningCount();

	private:
		eastl::vector<std::string> m_Errors;
		eastl::vector<std::string> m_Warnings;
		eastl::vector<std::string> m_Messages;
	};
}
