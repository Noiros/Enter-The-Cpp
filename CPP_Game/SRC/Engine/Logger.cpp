#include <iostream>
#include <chrono>
#include <ctime>
#include "Logger.h"


std::string Logger::GetCurrentDateTime() {
	auto now = std::chrono::system_clock::now();

	std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

	std::tm tmNow{};
	localtime_s(&tmNow, &timeNow);

	std::ostringstream oss;
	oss << std::put_time(&tmNow, "%H:%M:%S");

	return oss.str();
}


void Logger::Log(std::string_view msg) {
	LogEntry logEntry;
	logEntry.type = LogType::info;
	logEntry.dateTime = GetCurrentDateTime();
	logEntry.msg = msg;

	message.push_back(logEntry);

	std::cout << ANSI_COLOR_LOG << "[" << logEntry.dateTime << "] " << logEntry.msg << ANSI_COLOR_RESET << std::endl;
}

void Logger::Err(std::string_view msg) {
	LogEntry logEntry;
	logEntry.type = LogType::error;
	logEntry.dateTime = GetCurrentDateTime();
	logEntry.msg = msg;

	message.push_back(logEntry);

	std::cout << ANSI_COLOR_ERR << "[" << logEntry.dateTime << "] " << logEntry.msg << ANSI_COLOR_RESET << std::endl;
}