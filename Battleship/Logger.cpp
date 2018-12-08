#include "stdafx.h"
#include "Logger.h"

const std::string Logger::INFO_LOG_FILENAME = "infoLog.txt";

Logger::Logger()
{
	infoLog = std::ofstream(INFO_LOG_FILENAME);
}

Logger::~Logger()
{
	infoLog.close();
}

std::string Logger::getCombatLog() {return combatLog.str();}
std::string Logger::getEventLog() {return eventLog.str();}
std::string Logger::getEnemyLog() {return enemyLog.str();}

void Logger::addLineToInfoLog(const std::string &line) {infoLog << line << std::endl;}
void Logger::addLineToCombatLog(const std::string &line) {combatLog << line << std::endl;}
void Logger::addLineToEventLog(const std::string& line) {eventLog << line << std::endl;}
void Logger::addLineToEnemyLog(const std::string& line) {enemyLog << line << std::endl;}

void Logger::flushCombatLog()
{
	combatLog.str("");
	combatLog.clear();
}
void Logger::flushEventLog()
{
	eventLog.str("");
	eventLog.clear();
}

void Logger::flushEnemyLog()
{
	enemyLog.str("");
	enemyLog.clear();
}
