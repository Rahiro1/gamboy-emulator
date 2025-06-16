#include <iostream>
#include "GBCPU.h"
#include "GBBus.h"
#include <string>

int main()
{
    
    GBCPU cpu;
    GBBus bus;
    std::string fileName = "Blargg test roms/03-op sp,hl.gb";
    bool powerOn = true;

    cpu.ConnectBus(&bus);

    bus.LoadCartridge(fileName);

    while (powerOn) {
        cpu.Clock();
    }
}