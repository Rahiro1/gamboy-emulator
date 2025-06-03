#pragma once
#include <string>
#include <iostream>
#include <fstream>

class CPUStateLog
{
private:
	std::string log = "";
public:
	void Log(std::string message);
	void WriteToFile();
};

