#include "GBBus.h"
#include <iostream>
#include <fstream>

GBBus::GBBus() {
	//cpu.ConnectBus(this);
	for (uint8_t i : vram ) {i = 0;}
	for (uint8_t i : externalRam) {i = 0;}
	for (uint8_t i : wram) {i = 0;}
	for (uint8_t i : wramCGBSwitch) {i = 0;}
	for (uint8_t i : hram) {i = 0;}
	for (uint8_t i : oam) {i = 0;}
	for (uint8_t i : ioRegs) {i = 0;}

	activeRomBank = 1;
}

void GBBus::Write(uint16_t address, uint8_t data) {

	if (address == 0xFF01) {
		std::cout << (char)data;
	}

	if (address >= 0x8000 && address < 0xA000) {
		vram[address - 0x8000] = data;
	}

	if (address >= 0xA000 && address < 0xC000) {
		externalRam[address - 0xA000] = data;
	}


	// echo ram - if in this range it will always be caught by the two below ifs - mirror of 0xC000 - 0xDDFF
	if (address >= 0xE000 && address < 0xFE00) {
		address -= 0x2000;
	}

	if (address >= 0xC000 && address < 0xD000) {
		wram[address - 0xC000] = data;
	}
	if (address >= 0xD000 && address < 0xE000) {
		// when adding CGB this will be switchable
		wramCGBSwitch[address - 0xD000] = data;
	}

	if (address >= 0xFE00 && address < 0xFEA0) {
		// object access memory
		oam[address - 0xFE00] = data;
	}

	if (address >= 0xFF00 && address < 0xFF80) {
		// I/O registers
		ioRegs[address - 0xFF00] = data;
	}

	if (address >= 0xFF80 && address < 0xFFFF) {
		// fast ram
		hram[address - 0xFF80] = data;
	}

	if (address == 0xFFFF) {
		// I/O registers
		irptReg = data;
	}




	if (address < 0x8000) {
		mbc.InputAsWrite(address, data);
	}
}

uint8_t GBBus::Read(uint16_t address) {

	if (address == 0xFF44) {
		return 0x90;
	}

	if (address < 0x4000) {
		// rom bank 0 - on all roms
		return cartridgeRom[address];
	}
	if (address < 0x8000) {
		//switchable rom bank - only on some roms
		address += (mbc.GetRomBankNum() - 1) * 0x4000;
		return cartridgeRom[address];
	} 

	if (address >= 0x8000 && address < 0xA000) {
		return vram[address - 0x8000];
	}

	if (address >= 0xA000 && address < 0xC000) {
		return externalRam[address - 0xA000];
	}



	// echo ram - if in this range it will always be caught by the two below ifs - mirror of 0xC000 - 0xDDFF
	if (address >= 0xE000 && address < 0xFE00) {
		address -= 0x2000;
	}

	if (address >= 0xC000 && address < 0xD000) {
		return wram[address - 0xC000];
		
	}
	if (address >= 0xD000 && address < 0xE000) {
		// when adding CGB this will be switchable
		return wramCGBSwitch[address - 0xD000];
		
	}

	if (address >= 0xFE00 && address < 0xFEA0) {
		// object access memory
		return oam[address - 0xFE00];
	}

	if (address >= 0xFF00 && address < 0xFF80) {
		// I/O registers
		return ioRegs[address - 0xFF00];
	}

	if (address >= 0xFF80 && address < 0xFFFF) {
		// fast ram
		return hram[address - 0xFF80];
	}

	if (address == 0xFFFF) {
		// I/O registers
		return irptReg;
	}

	//insert error

	return 0x0000;
}

bool GBBus::LoadCartridge(std::string fileName) {

	std::ifstream cartridge(fileName, std::ifstream::binary);
	std::streampos fSize = 0;


	fSize = cartridge.tellg();
	cartridge.seekg(0, std::ios::end);
	fSize = cartridge.tellg() - fSize;
	cartridge.seekg(0, std::ios::beg);

	uint8_t j;

	for (int i = 0; i < fSize; i++) {
		cartridgeRom.push_back(cartridge.get());
	}

	cartridge.close();

	uint8_t cType = Read(0x147);
	uint8_t cRomSize = Read(0x148);
	uint8_t cRamSize = Read(0x149);

	SelectMBC(cType);
	mbc.InitialiseMBC(cType, cRomSize, cRamSize);

	return true;
}

void GBBus::SelectMBC(uint8_t cartridgeType) {

	//set memory bank controller to correct type
	if (cartridgeType < 4) {
		MBC1 mbc1;
		mbc = mbc1;
		return;
	}

	//error here if no return

}