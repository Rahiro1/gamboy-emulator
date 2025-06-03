#include "CPUStateLog.h"

void CPUStateLog::Log(std::string message) {
	log.append(message);
}

void CPUStateLog::WriteToFile() {
	std::ofstream logFile("CPULog.txt");

	logFile << log;

	logFile.close();
}