#pragma once
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MBC1.h"

class GBBus
{
public:
	GBBus();

public:
	// devices
	//GBCPU cpu;

	//rom
	std::vector<uint8_t> cartridgeRom;

	//ram
	uint8_t vram[8 * 1024];
	uint8_t externalRam[16 * 0x2000];
	uint8_t wram[4 * 1024];
	uint8_t wramCGBSwitch[4 * 1024];
	uint8_t hram[159];

	//other
	uint8_t oam[160];
	uint8_t ioRegs[128];
	uint8_t irptReg; 

	int activeRomBank = 1;

	void Write(uint16_t address, uint8_t data);
	uint8_t Read(uint16_t address);
	bool LoadCartridge(std::string filename);

private:
	MBC1 mbc;
	void SelectMBC(uint8_t cartridgeType);

};

