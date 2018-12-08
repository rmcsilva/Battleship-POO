#pragma once
#include <fstream>

class Logger
{
	std::ofstream infoLog;

	std::ostringstream enemyLog;
	std::ostringstream combatLog;
	std::ostringstream eventLog;

	static const std::string INFO_LOG_FILENAME;

public:
	Logger();
	~Logger();

	std::string getCombatLog();
	std::string getEventLog();
	std::string getEnemyLog();

	void addLineToInfoLog(const std::string &line);
	void addLineToCombatLog(const std::string &line);
	void addLineToEventLog(const std::string &line);
	void addLineToEnemyLog(const std::string &line);
	
	void flushCombatLog();
	void flushEventLog();
	void flushEnemyLog();
};