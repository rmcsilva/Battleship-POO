#pragma once
#include <fstream>

class Logger
{
	std::ofstream infoLog;

	std::ostringstream combatMessages;
	std::ostringstream eventMessages;

	static const std::string INFO_LOG_FILENAME;

public:
	Logger();
	~Logger();

	void addLineToInfoLog(const std::string &line);
	void addLineToCombatLog(const std::string &line);
	void addLineToEventLog(const std::string &line);
	void flushCombatLog();
	void flushEventLog();
};