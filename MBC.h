#pragma once
#include <cstdint>

class MBC 
{
public:
	// redirected write to ROM
	virtual void InputAsWrite(uint16_t address, uint8_t data) = 0;
	virtual void InitialiseMBC(uint8_t cartridgeType, uint8_t romSize, uint8_t ramSize) = 0;
	virtual uint8_t GetRomBankNum() = 0;
	virtual uint8_t GetRamBankNum() = 0;
	virtual bool GetRamEnabled() = 0;

protected:
	bool ramToggle = false;
	bool bankingModeToggle = false;
	uint8_t numberOfRomBanks; // determines banking logic
	uint8_t numberOfRamBanks; // determines banking logic
	int sizeOfCartridge;
};

 