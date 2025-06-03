#include <iostream>
#include "GBCPU.h"
#include "GBBus.h"
#include <string>

int main()
{
    
    GBCPU cpu;
    GBBus bus;
    std::string fileName = "Blargg test roms/06-ld r,r.gb";
    bool powerOn = true;

    cpu.ConnectBus(&bus);

    bus.LoadCartridge(fileName);

    while (powerOn) {
        cpu.Clock();
    }
}