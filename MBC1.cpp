#include "MBC1.h"



void MBC1::InputAsWrite(uint16_t address, uint8_t data) {

	if (address < 0x2000) {
		if ((data & 0x0F) == 0x0A) {
			ramToggle = true;
		}
		else {
			ramToggle = false;
		}
	}

	if (address >= 0x2000 && address < 0x4000) {
		romBankControl = data & 0b00011111;
	}

	if (address >= 0x4000 < 0x6000) {
		ramBankControl = data & 0b00000011;
	}

	if (address >= 0x6000 < 0x8000) {
		if (data == 0) {
			bankingModeToggle = true;
		}
		else {
			bankingModeToggle = false;
		}
	}
}

uint8_t MBC1::GetRomBankNum() {

	if (romBankControl == 0) {return 1;}
	// masking value based on # of banks in cart
	if (numberOfRomBanks < 4) { return romBankControl & 0b00000011; }
	if (numberOfRomBanks < 8) { return romBankControl & 0b00000111; }
	if (numberOfRomBanks < 16) { return romBankControl & 0b00001111; }

	return romBankControl;
}

uint8_t MBC1::GetRamBankNum() {
	return ramBankControl;
}

bool MBC1::GetRamEnabled()
{
	return ramToggle;
}

//cartridge type is from address 0x0147 and cartridge size is from address 0x148
void MBC1::InitialiseMBC(uint8_t cartridgeType, uint8_t romSize, uint8_t ramSize) {
	mbc1Type = cartridgeType;
	numberOfRomBanks = 2 << romSize;
	if (ramSize < 2) {
		numberOfRamBanks = 0;
	}
	if (ramSize == 2) {
		numberOfRamBanks = 1;
	}
	if (ramSize == 3) {
		numberOfRamBanks = 4;
	}
	if (ramSize == 4) {
		numberOfRamBanks = 16;
	}
	if (ramSize == 5) {
		numberOfRamBanks = 8;
	}

	// rom banks are 16KiB, ram banks are 8KiB
	sizeOfCartridge = numberOfRomBanks + numberOfRamBanks/2;
}
