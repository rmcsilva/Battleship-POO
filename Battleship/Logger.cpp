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

void Logger::addLineToInfoLog(const std::string &line) {infoLog << line << std::endl;}
void Logger::addLineToCombatLog(const std::string &line) {combatMessages << line << std::endl;}
void Logger::addLineToEventLog(const std::string& line) {eventMessages << line << std::endl;}

void Logger::flushCombatLog() {combatMessages.flush();}
void Logger::flushEventLog() {eventMessages.flush();}