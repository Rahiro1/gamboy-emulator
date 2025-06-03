#pragma once
#include <cstdint>
#include <vector>
#include "MBC.h"

class MBC1 : public MBC
{
public:
	void InputAsWrite(uint16_t address, uint8_t data);
	void InitialiseMBC(uint8_t cartridgeType, uint8_t romSize, uint8_t ramSize);
	uint8_t GetRomBankNum();
	uint8_t GetRamBankNum();
	bool GetRamEnabled();

private:
	// 5-bit number
	uint8_t romBankControl = 0;
	// 2-bit number, if cartridge has more than 32 rom banks then ram bank control is an extension of rom bank control
	uint8_t ramBankControl = 0;
	int mbc1Type;
};

