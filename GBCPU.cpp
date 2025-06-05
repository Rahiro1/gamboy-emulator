#include "GBCPU.h"
#include <cstdint>


GBCPU::GBCPU() {
	using a = GBCPU;

	opcodeLookup = {
		{&a::NOP},{&a::LDBCN16},{&a::LDBCA},{&a::INCBC},{&a::INCB},{&a::DECB},{&a::LDBN8},{&a::RLCA},{&a::LDN16SP},{&a::ADDHLBC},{&a::LDABC},{&a::DECBC},{&a::INCC},{&a::DECC},{&a::LDCN8},{&a::RRCA},
		{&a::STOP},{&a::LDDEN16},{&a::LDDEA},{&a::INCDE},{&a::INCD},{&a::DECD},{&a::LDDN8},{&a::RLA},{&a::JRN16},{&a::ADDHLDE},{&a::LDADE},{&a::DECDE},{&a::INCE},{&a::DECE},{&a::LDEN8},{&a::RRA},
		{&a::JRNZN16},{&a::LDHLN16},{&a::LDHLIA},{&a::INCHL},{&a::INCH},{&a::DECH},{&a::LDHN8},{&a::DAA},{&a::JRZN16},{&a::ADDHLHL},{&a::LDAHLI},{&a::DECHL},{&a::INCL},{&a::DECL},{&a::LDLN8},{&a::CPL},
		{&a::JRNCN16},{&a::LDSPN16},{&a::LDHLDA},{&a::INCSP},{&a::INC_HL_},{&a::DEC_HL_},{&a::LDHLN8},{&a::SCF},{  &a::JRCN16},{&a::ADDHLSP},{&a::LDAHLD},{&a::DECSP},{&a::INCA},{&a::DECA},{&a::LDAN8},{&a::CCF},
		{&a::LDBB},{&a::LDBC},{&a::LDBD},{&a::LDBE},{&a::LDBH},{&a::LDBL},{&a::LDBHL},{&a::LDBA},{&a::LDCB},{&a::LDCC},{&a::LDCD},{&a::LDCE},{&a::LDCH},{&a::LDCL},{&a::LDCHL},{&a::LDCA},
		{&a::LDDB},{&a::LDDC},{&a::LDDD},{&a::LDDE},{&a::LDDH},{&a::LDDL},{&a::LDDHL},{&a::LDDA},{&a::LDEB},{&a::LDEC},{&a::LDED},{&a::LDEE},{&a::LDEH},{&a::LDEL},{&a::LDEHL},{&a::LDEA},
		{&a::LDHB},{&a::LDHC},{&a::LDHD},{&a::LDHE},{&a::LDHH},{&a::LDHL},{&a::LDHHL},{&a::LDHA},{&a::LDLB},{&a::LDLC},{&a::LDLD},{&a::LDLE},{&a::LDLH},{&a::LDLL},{&a::LDLHL},{&a::LDLA},
		{&a::LDHLB},{&a::LDHLC},{&a::LDHLD},{&a::LDHLE},{&a::LDHLH},{&a::LDHLL},{&a::HALT},{&a::LDHLA},{&a::LDAB},{&a::LDAC},{&a::LDAD},{&a::LDAE},{&a::LDAH},{&a::LDAL},{&a::LDAHL},{&a::LDAA},
		{&a::ADDAB},{&a::ADDAC},{&a::ADDAD},{&a::ADDAE},{&a::ADDAH},{&a::ADDAL},{&a::ADDAHL},{&a::ADDAA},{&a::ADCAB},{&a::ADCAC},{&a::ADCAD},{&a::ADCAE},{&a::ADCAH},{&a::ADCAL},{&a::ADCAHL},{&a::ADCAA},
		{&a::SUBAB},{&a::SUBAC},{&a::SUBAD},{&a::SUBAE},{&a::SUBAH},{&a::SUBAL},{&a::SUBAHL},{&a::SUBAA},{&a::SBCAB},{&a::SBCAC},{&a::SBCAD},{&a::SBCAE},{&a::SBCAH},{&a::SBCAL},{&a::SBCAHL},{&a::SBCAA},
		{&a::ANDAB},{&a::ANDAC},{&a::ANDAD},{&a::ANDAE},{&a::ANDAH},{&a::ANDAL},{&a::ANDAHL},{&a::ANDAA},{&a::XORAB},{&a::XORAC },{&a::XORAD},{&a::XORAE},{&a::XORAH},{&a::XORAL},{&a::XORAHL},{&a::XORAA},
		{&a::ORAB},{&a::ORAC},{&a::ORAD},{&a::ORAE},{&a::ORAH},{&a::ORAL},{&a::ORAHL},{&a::ORAA},{&a::CPAB},{&a::CPAC},{&a::CPAD},{&a::CPAE},{&a::CPAH},{&a::CPAL},{&a::CPAHL},{&a::CPAA},
		{&a::RETNZ},{&a::POPBC},{&a::JPNZN16},{&a::JPN16},{&a::CALLNZN16},{&a::PUSHBC},{&a::ADDAN8},{&a::RST00},{&a::RETZ},{&a::RET},{&a::JPZN16},{&a::XXX},{&a::CALLZN16},{&a::CALLN16},{&a::ADCAN8},{&a::RST08},
		{&a::RETNC},{&a::POPDE},{&a::JPNCN16},{&a::XXX},{&a::CALLNCN16},{&a::PUSHDE},{&a::SUBAN8},{&a::RST10},{&a::RETC},{&a::RETI},{&a::JPCN16},{&a::XXX},{&a::CALLCN16},{&a::XXX},{&a::SBCAN8},{&a::RST18},
		{&a::LDHN16A},{&a::POPHL},{&a::LDHCA},{&a::XXX},{&a::XXX},{&a::PUSHHL},{&a::ANDAN8},{&a::RST20},{&a::ADDSPE8},{&a::JPHL},{&a::LDN16A},{&a::XXX},{&a::XXX},{&a::XXX},{&a::XORAN8},{&a::RST28},
		{&a::LDHAN16},{&a::POPAF},{&a::LDHAC},{&a::DI},{&a::XXX},{&a::PUSHAF},{&a::ORAN8},{&a::RST30},{&a::LDHLSPADDE8},{&a::LDSPHL},{&a::LDAN16},{&a::EI},{&a::XXX},{&a::XXX},{&a::CPAN8},{&a::RST38}
	};

	bitShiftLookup = {
		{&a::RLCB},{&a::RLCC},{&a::RLCD},{&a::RLCE},{&a::RLCH},{&a::RLCL},{&a::RLCHL},{&a::RLCA},{&a::RRCB},{&a::RRCC},{&a::RRCD},{&a::RRCE},{&a::RRCH},{&a::RRCL},{&a::RRCHL},{&a::RRCA},
		{&a::RLB},{&a::RLC},{&a::RLD},{&a::RLE},{&a::RLH},{&a::RLL},{&a::RLHL},{&a::RLA},{&a::RRB},{&a::RRC},{&a::RRD},{&a::RRE},{&a::RRH},{&a::RRL},{&a::RRHL},{&a::RRA},
		{&a::SLAB},{&a::SLAC},{&a::SLAD},{&a::SLAE},{&a::SLAH},{&a::SLAL},{&a::SLAHL},{&a::SLAA},{&a::SRAB},{&a::SRAC},{&a::SRAD},{&a::SRAE},{&a::SRAH},{&a::SRAL},{&a::SRAHL},{&a::SRAA},
		{&a::SWAPB},{&a::SWAPC},{&a::SWAPD},{&a::SWAPE},{&a::SWAPH},{&a::SWAPL},{&a::SWAPHL},{&a::SWAPA},{&a::SRLB},{&a::SRLC},{&a::SRLD},{&a::SRLE},{&a::SRLH},{&a::SRLL},{&a::SRLHL},{&a::SRLA},
		{&a::BIT0B},{&a::BIT0C},{&a::BIT0D},{&a::BIT0E},{&a::BIT0H},{&a::BIT0L},{&a::BIT0HL},{&a::BIT0A},{&a::BIT1B},{&a::BIT1C},{&a::BIT1D},{&a::BIT1E},{&a::BIT1H},{&a::BIT1H},{&a::BIT1H},{&a::BIT1H},
		{&a::BIT2B},{&a::BIT2C},{&a::BIT2D},{&a::BIT2E},{&a::BIT2H},{&a::BIT2L},{&a::BIT2HL},{&a::BIT2A},{&a::BIT3B},{&a::BIT3C},{&a::BIT3D},{&a::BIT3E},{&a::BIT3H},{&a::BIT3H},{&a::BIT3H},{&a::BIT3H},
		{&a::BIT4B},{&a::BIT4C},{&a::BIT4D},{&a::BIT4E},{&a::BIT4H},{&a::BIT4L},{&a::BIT4HL},{&a::BIT4A},{&a::BIT5B},{&a::BIT5C},{&a::BIT5D},{&a::BIT5E},{&a::BIT5H},{&a::BIT5H},{&a::BIT5H},{&a::BIT5H},
		{&a::BIT6B},{&a::BIT6C},{&a::BIT6D},{&a::BIT6E},{&a::BIT6H},{&a::BIT6L},{&a::BIT6HL},{&a::BIT6A},{&a::BIT7B},{&a::BIT7C},{&a::BIT7D},{&a::BIT7E},{&a::BIT7H},{&a::BIT7H},{&a::BIT7H},{&a::BIT7H},
		{&a::RES0B},{&a::RES0C},{&a::RES0D},{&a::RES0E},{&a::RES0H},{&a::RES0L},{&a::RES0HL},{&a::RES0A},{&a::RES1B},{&a::RES1C},{&a::RES1D},{&a::RES1E},{&a::RES1H},{&a::RES1H},{&a::RES1H},{&a::RES1H},
		{&a::RES2B},{&a::RES2C},{&a::RES2D},{&a::RES2E},{&a::RES2H},{&a::RES2L},{&a::RES2HL},{&a::RES2A},{&a::RES3B},{&a::RES3C},{&a::RES3D},{&a::RES3E},{&a::RES3H},{&a::RES3H},{&a::RES3H},{&a::RES3H},
		{&a::RES4B},{&a::RES4C},{&a::RES4D},{&a::RES4E},{&a::RES4H},{&a::RES4L},{&a::RES4HL},{&a::RES4A},{&a::RES5B},{&a::RES5C},{&a::RES5D},{&a::RES5E},{&a::RES5H},{&a::RES5H},{&a::RES5H},{&a::RES5H},
		{&a::RES6B},{&a::RES6C},{&a::RES6D},{&a::RES6E},{&a::RES6H},{&a::RES6L},{&a::RES6HL},{&a::RES6A},{&a::RES7B},{&a::RES7C},{&a::RES7D},{&a::RES7E},{&a::RES7H},{&a::RES7H},{&a::RES7H},{&a::RES7H},
		{&a::SET0B},{&a::SET0C},{&a::SET0D},{&a::SET0E},{&a::SET0H},{&a::SET0L},{&a::SET0HL},{&a::SET0A},{&a::SET1B},{&a::SET1C},{&a::SET1D},{&a::SET1E},{&a::SET1H},{&a::SET1H},{&a::SET1H},{&a::SET1H},
		{&a::SET2B},{&a::SET2C},{&a::SET2D},{&a::SET2E},{&a::SET2H},{&a::SET2L},{&a::SET2HL},{&a::SET2A},{&a::SET3B},{&a::SET3C},{&a::SET3D},{&a::SET3E},{&a::SET3H},{&a::SET3H},{&a::SET3H},{&a::SET3H},
		{&a::SET4B},{&a::SET4C},{&a::SET4D},{&a::SET4E},{&a::SET4H},{&a::SET4L},{&a::SET4HL},{&a::SET4A},{&a::SET5B},{&a::SET5C},{&a::SET5D},{&a::SET5E},{&a::SET5H},{&a::SET5H},{&a::SET5H},{&a::SET5H},
		{&a::SET6B},{&a::SET6C},{&a::SET6D},{&a::SET6E},{&a::SET6H},{&a::SET6L},{&a::SET6HL},{&a::SET6A},{&a::SET7B},{&a::SET7C},{&a::SET7D},{&a::SET7E},{&a::SET7H},{&a::SET7H},{&a::SET7H},{&a::SET7H},

	};

	nameLookup = {
		"NOP", "LDBCN16", "LDBCA", "INCBC", "INCB", "DECB", "LDBN8", "RLCA", "LDN16SP", "ADDHLBC", "LDABC", "DECBC", "INCC", "DECC", "LDCN8", "RRCA",
		"STOP", "LDDEN16", "LDDEA", "INCDE", "INCD", "DECD", "LDDN8", "RLA", "JRN16", "ADDHLDE", "LDADE", "DECDE", "INCE", "DECE", "LDEN8", "RRA",
		"JRNZN16","LDHLN16","LDHLIA","INCHL","INCH","DECH","LDHN8","DAA","JRZN16","ADDHLHL","LDAHLI","DECHL","INCL","DECL","LDLN8","CPL",
		"JRNCN16","LDSPN16","LDHLDA","INCSP","INC_HL_","DEC_HL_","LDHLN8","SCF", "JRCN16","ADDHLSP","LDAHLD","DECSP","INCA","DECA","LDAN8","CCF",
		"LDBB","LDBC","LDBD","LDBE","LDBH","LDBL","LDBHL","LDBA","LDCB","LDCC","LDCD","LDCE","LDCH","LDCL","LDCHL","LDCA",
		"LDDB","LDDC","LDDD","LDDE","LDDH","LDDL","LDDHL","LDDA","LDEB","LDEC","LDED","LDEE","LDEH","LDEL","LDEHL","LDEA",
		"LDHB","LDHC","LDHD","LDHE","LDHH","LDHL","LDHHL","LDHA","LDLB","LDLC","LDLD","LDLE","LDLH","LDLL","LDLHL","LDLA",
		"LDHLB","LDHLC","LDHLD","LDHLE","LDHLH","LDHLL","HALT","LDHLA","LDAB","LDAC","LDAD","LDAE","LDAH","LDAL","LDAHL","LDAA ",
		"ADDAB","ADDAC","ADDAD","ADDAE","ADDAH","ADDAL","ADDAHL","ADDAA","ADCAB","ADCAC","ADCAD","ADCAE","ADCAH","ADCAL","ADCAHL","ADCAA",
		"SUBAB","SUBAC","SUBAD","SUBAE","SUBAH","SUBAL","SUBAHL","SUBAA","SBCAB","SBCAC","SBCAD","SBCAE","SBCAH","SBCAL","SBCAHL","SBCAA",
		"ANDAB","ANDAC","ANDAD","ANDAE","ANDAH","ANDAL","ANDAHL","ANDAA","XORAB","XORAC","XORAD","XORAE","XORAH","XORAL","XORAHL","XORAA",
		"ORAB","ORAC","ORAD","ORAE","ORAH","ORAL","ORAHL","ORAA","CPAB","CPAC","CPAD","CPAE","CPAH","CPAL","CPAHL","CPAA",
		"RETNZ","POPBC","JPNZN16","JPN16","CALLNZN16","PUSHBC","ADDAN8","RST00","RETZ","RET","JPZN16","XXX","CALLZN16","CALLN16","ADCAN8","RST08",
		"RETNC","POPDE","JPNCN16","XXX","CALLNCN16","PUSHDE","SUBAN8","RST10","RETC","RETI","JPCN16","XXX","CALLCN16","XXX","SBCAN8","RST18",
		"LDHN16A","POPHL","LDHCA","XXX","XXX","PUSHHL","ANDAN8","RST20","ADDSPE8","JPHL","LDN16A","XXX","XXX","XXX","XORAN8","RST28",
		"LDHAN16","POPAF","LDHAC","DI","XXX","PUSHAF","ORAN8","RST30","LDHLSPADDE8","LDSPHL","LDAN16","EI","XXX","XXX","CPAN8","RST38"
	};

	pc = 0x0100;
	GBCPU::a = 0x01;
	zf = 1;
	nf = 0;
	hf = 1;
	cf = 1;
	b = 0;
	c = 0x13;
	d = 0;
	e = 0xD8;
	h = 1;
	l = 0x4d;
	sp = 0xFFFE;
	
}

void GBCPU::ConnectBus(GBBus *newBus) { bus = newBus; }

void GBCPU::Clock() {

	if (remainingCycles == 0) {

		pcToLog = pc;

		instruction = Read(pc++);
		if (instruction == 0xCB) {
			useCBTable = true;
			instruction = Read(pc++);
		}
		
		//<< nameLookup[instruction]

		cpulog.Log("A:" + std::format("{0:#04X}", a).erase(0, 2));
		cpulog.Log(" F:" + std::format("{0:#04X}", GetF()).erase(0, 2));
		cpulog.Log(" B:" + std::format("{0:#04X}", b).erase(0, 2));
		cpulog.Log(" C:" + std::format("{0:#04X}", c).erase(0, 2));
		cpulog.Log(" D:" + std::format("{0:#04X}", d).erase(0, 2));
		cpulog.Log(" E:" + std::format("{0:#04X}", e).erase(0, 2));
		cpulog.Log(" H:" + std::format("{0:#04X}", h).erase(0, 2));
		cpulog.Log(" L:" + std::format("{0:#04X}", l).erase(0, 2));
		cpulog.Log(" SP:" + std::format("{0:#06X}", sp).erase(0, 2));
		cpulog.Log(" PC:" + std::format("{0:#06X}", pcToLog).erase(0, 2));
		cpulog.Log(" PCMEM:" + std::format("{0:#04X}", Read(pcToLog)).erase(0, 2));
		cpulog.Log("," + std::format("{0:#04X}", Read(pcToLog + 1)).erase(0, 2));
		cpulog.Log("," + std::format("{0:#04X}", Read(pcToLog + 2)).erase(0, 2));
		cpulog.Log("," + std::format("{0:#04X}", Read(pcToLog + 3)).erase(0, 2));
		cpulog.Log(std::format("\n"));
		
		if (!useCBTable) {
			(this->*opcodeLookup[instruction].operate)();
		}
		else {
			useCBTable = false;
			(this->*bitShiftLookup[instruction].operate)();
		}
		

	}

	remainingCycles--;
	 
	debug_totalCycles++;

	if (debug_totalCycles == 2400000) {
		cpulog.WriteToFile();
	}
}


uint8_t GBCPU::Read(uint16_t address) {
	
	uint8_t output = bus->Read(address);
	if (address == 0xFEA0) {
		printf("NOW!");
	}
	//std::cout << "Read: " << (int)output << "\n";
	return output;
}
void GBCPU::Write(uint16_t address, uint8_t data) {
	bus->Write(address, data);
	//std::cout << "Write: " << (int)data << "\n";
} 

uint16_t GBCPU::GetF()
{
	uint16_t f = 0;
	f |= (zf << 7);
	f |= (nf << 6);
	f |= (hf << 5);
	f |= (cf << 4);
	return f;
}



//getters and setters for 16-bit Registers
//16-bit registers are in big- endian order
uint16_t GBCPU::GetBC() {
	return (((uint16_t)b << 8) + (uint16_t)c);
}

uint16_t GBCPU::GetDE() {
	return (((uint16_t)d << 8) + (uint16_t)e);
}

uint16_t GBCPU::GetHL() {
	return (((uint16_t)h << 8) + (uint16_t)l);
}

void GBCPU::SetF(uint8_t number)
{
	zf = number & 0b10000000;
	nf = number & 0b01000000;
	hf = number & 0b00100000;
	cf = number & 0b00010000;
}

void GBCPU::SetBC(uint16_t number) {
	c = number & 0x00FF;
	b = ((number & 0xFF00) >> 8) & 0x00FF;
}

void GBCPU::SetDE(uint16_t number) {
	e = number & 0x00FF;
	d = ((number & 0xFF00) >> 8) & 0x00FF;
}

void GBCPU::SetHL(uint16_t number) {
	l = number & 0x00FF;
	h = ((number & 0xFF00) >> 8) & 0x00FF;
}


// sets the f register
// zero for zero the flag, 1 for change the bit to a 1, -1 for unnaffected
void GBCPU::SetFlags(int setZ, int setN, int setH, int setC) {
	if (setZ != -1) {zf = setZ;}
	if (setN != -1) {nf = setN;}
	if (setH != -1) {hf = setH;}
	if (setC != -1) {cf = setC;}
}

uint16_t GBCPU::AddAndSetFlagsU16(uint16_t x, uint16_t y, bool addCarry) {

	uint32_t result = x + y;
	uint32_t carry = 0;
	if (addCarry) { carry = cf; }
	result += carry;
	SetFlags(-1, 0, (x & 0x0FFF) + (y & 0x0FFF) + carry > 0x0FFF, result > 0xFFFF);
	return (uint16_t)result;
}
uint8_t GBCPU::AddAndSetFlagsU8(uint8_t x, uint8_t y, bool addCarry) {

	uint16_t result = (uint16_t)x + (uint16_t)y;
	// add the carry flag
	uint16_t carry = 0;
	if (addCarry) {carry = cf;}
	result += carry;

	SetFlags((result & 0xFF) == 0, 0, ((x & 0x0F) + (y&0x0F) + carry) > 0x0F, result > 0xFF);

	return result & 0xFF;
}

uint16_t GBCPU::AddAndSetFlagsU16FromS8(uint16_t x, int8_t y, bool addCarry) {

	// TODO - implement this method properly

	int setH = 0;
	int setC = 0;

	uint8_t flagTest = x & y;

	if (flagTest & 0x08) {setH = 1;}
	if (flagTest & 0x0F) {setC = 1;}

	SetFlags(0, 0, setH, setC);

	x += y;
	return x;
}

uint8_t GBCPU::SubAndSetFlagsU8(uint8_t x, uint8_t y, bool addCarry)
{
	uint16_t result = x - y;
	uint16_t carry = addCarry ? cf : 0;
	result -= carry;

	SetFlags(result == 0,1,(x & 0xf) < (y & 0xf) - (uint8_t)carry, (uint16_t)x < (uint16_t)y + carry);

	return result & 0xFF;
}

void GBCPU::CompareAndSetFlags(uint8_t x, uint8_t y)
{
	int difference = x - y;
	SetFlags(difference == 0, 1, (x & 0xf) < (y & 0xf), difference < 0);
}

uint8_t GBCPU::IncrementAndSetFlagsU8(uint8_t x)
{
	uint8_t result = x + 1;

	SetFlags(result == 0, 0, (x & 0xf) == 0x000F, -1);

	return result;
}

uint16_t GBCPU::IncrementAndSetFlagsU16(uint16_t x)
{
	uint16_t result = x + 1;

	return result;
}

uint8_t GBCPU::DecrementAndSetFlagsU8(uint8_t x)
{
	uint8_t result = x - 1;

	SetFlags(result == 0, 1, (x & 0xf) == 0, -1);

	return result;
}

uint16_t GBCPU::DecrementAndSetFlagsU16(uint16_t x)
{
	uint16_t result = x - 1;


	return result;
}

uint8_t GBCPU::AndAndSetFlags(uint8_t x, uint8_t y)
{
	uint8_t result = x & y;
	SetFlags(result == 0, 0, 1, 0);
	return result;
}

uint8_t GBCPU::OrAndSetFlags(uint8_t x, uint8_t y)
{
	uint8_t result = x | y;
	SetFlags(result == 0, 0, 0, 0);
	return result;
}

uint8_t GBCPU::XorAndSetFlags(uint8_t x, uint8_t y)
{
	uint8_t result = x ^ y;
	SetFlags(result == 0, 0, 0, 0);
	return result;
}

//reads at the location pointed to by the pc and increments it twice (PCI = pc increment)
// returns 16-bit little-endian concatenation of the two 
uint16_t GBCPU::ReadDoublePCI() {
	uint8_t lo = Read(pc);
	pc++;
	uint8_t hi = Read(pc);
	pc++;
	return ((uint16_t)hi << 8 | lo);
}



// operation types
// methods for final implementaition of opcodes

void GBCPU::NOP() {
	remainingCycles = 4;
}

void GBCPU::XXX(){

}

void GBCPU::LDR8R8(uint8_t& ptrRegTo, uint8_t regFrom) {
	ptrRegTo = regFrom;
	remainingCycles = 4;
}


void GBCPU::LDR8N8(uint8_t& ptrRegTo) {
	// read the next byte
	uint8_t n8 = Read(pc++);
	// assign it to register
	ptrRegTo = n8;

	remainingCycles = 8;
}

void GBCPU::LDR16N16(uint8_t& ptrRegToHi, uint8_t& ptrRegToLo) {
	// Readine the bytes and assigning seperately is equiv of reading the 16-bit
	ptrRegToLo = Read(pc++);
	ptrRegToHi = Read(pc++);
	

	remainingCycles = 12;
}

void GBCPU::LDHLR8(uint8_t regFrom) {
	Write(GetHL(), regFrom);

	remainingCycles = 8;
}

void GBCPU::LDHLN8() {
	Write(GetHL(), Read(pc++));

	remainingCycles = 12;
}

void GBCPU::LDR8HL(uint8_t &ptrRegTo) {
	ptrRegTo = Read(GetHL());

	remainingCycles = 8;
}

//16-bit address from accumulator (register) (2)
void GBCPU::LDBCA() {
	Write(GetBC(), a);

	remainingCycles = 8;
}

void GBCPU::LDDEA() {
	Write(GetDE(), a);

	remainingCycles = 8;
}

//accumulator from memory address (1)
void GBCPU::LDAN16() {
	a = Read(ReadDoublePCI());

	remainingCycles = 16;
}


//16-bit address from accumulator (value) (1)
void GBCPU::LDN16A() {
	Write(ReadDoublePCI(), a);

	remainingCycles = 16;
}

//16-bit address equal to 0xFF00 + 8-bit value from accumulator
void GBCPU::LDHN16A() {
	Write(0xFF00 | Read(pc++), a);

	remainingCycles = 12;
}

//16-bit address equal to 0xFF00 + register C from accumulator (1)
void GBCPU::LDHCA() {
	Write(0xFF00 | c, a);

	remainingCycles = 8;
}

//accumulator from 16-bit register
void GBCPU::LDABC() {
	a = Read(GetBC());

	remainingCycles = 8;
}

void GBCPU::LDADE() {
	a = Read(GetDE());

	remainingCycles = 8;
}

//accumulator from 16-bit address (value)
void GBCPU::LDHAN16() {
	a = Read(0xFF00 | Read(pc++));

	remainingCycles = 12;
}

//accumulator from 0xFF00 + C
void GBCPU::LDHAC() {
	a = Read(0xFF00 | c);

	remainingCycles = 8;
}

//HL register address from accumulator and increment after (1)
void GBCPU::LDHLIA() {
	Write(GetHL(), a);
	SetHL(GetHL() + 1);

	remainingCycles = 8;
}

//HL register address from accumulator and decrement after (1)
void GBCPU::LDHLDA() {
	Write(GetHL(), a);
	SetHL(GetHL() - 1);

	remainingCycles = 8;
}

//accumulator from HL address amd increment HL after (1)
void GBCPU::LDAHLI() {
	a = Read(GetHL());
	SetHL(GetHL() + 1);

	remainingCycles = 8;
}

//accumulator from HL address amd decrement HL after (1)
void GBCPU::LDAHLD() {
	a = Read(GetHL());
	SetHL(GetHL() - 1);

	remainingCycles = 8;
}

//stack pointer from 16-bit value (1)
void GBCPU::LDSPN16() {
	sp = ReadDoublePCI();

	remainingCycles = 12;
}

//16-bit address from stack pointer (1)
void GBCPU::LDN16SP() {
	uint16_t address = ReadDoublePCI();
	Write(address, (uint8_t)(sp & 0xFF));
	Write(address + 1, (uint8_t)((sp & 0xFF00) >> 8));

	remainingCycles = 20;
}

//stack pointer from HL
void GBCPU::LDSPHL() {
	sp = GetHL();

	remainingCycles = 8;
}

//loads HL, but first loaads the stck pointer plus a signed 8-bit value
void GBCPU::LDHLSPADDE8() {
	int8_t value = Read(pc++);

	int16_t signedSp = (int16_t)sp;
	signedSp += (int16_t)value;
	sp = (uint16_t)signedSp;

	SetHL(sp);

	remainingCycles = 12;
}







//add 8-bit register to a (7)
void GBCPU::ADCAR8(uint8_t regFrom) {
	a = AddAndSetFlagsU8(a, regFrom, true);

	remainingCycles = 4;
}

//add HL addressed byte plus carry flag to a (1)
void GBCPU::ADCAHL() {
	a = AddAndSetFlagsU8(a, Read(GetHL()), true);

	remainingCycles = 8;
}

//add 8-bit value to a with carry (1)
void GBCPU::ADCAN8() {
	a = AddAndSetFlagsU8(a, Read(pc++), true);

	remainingCycles = 8;
}

//add 8-bit register to 1 no carry (7)
void GBCPU::ADDAR8(uint8_t regFrom) {
	a = AddAndSetFlagsU8(a, regFrom, false);

	remainingCycles = 4;
}

//add HL addressed byte to a no carry (1)
void GBCPU::ADDAHL(){
	a = AddAndSetFlagsU8(a, Read(GetHL()), false);

	remainingCycles = 8;
}

//add 8-bit value to a no carry (1)
void GBCPU::ADDAN8() {
	a = AddAndSetFlagsU8(a, Read(pc++), true);

	remainingCycles = 8;
}

//add 16-bit register to HL no carry (3)
void GBCPU::ADDHLBC() {
	SetHL(AddAndSetFlagsU16(GetHL(), GetBC(), false ));

	remainingCycles = 8;
}

void GBCPU::ADDHLDE() {
	SetHL(AddAndSetFlagsU16(GetHL(), GetDE(), false));

	remainingCycles = 8;
}

void GBCPU::ADDHLHL() {
	SetHL(AddAndSetFlagsU16(GetHL(), GetHL(), false));

	remainingCycles = 8;
}

//add stack pointer to HL no carry (1)
void GBCPU::ADDHLSP() {
	SetHL(AddAndSetFlagsU16(GetHL(), sp, false));

	remainingCycles = 8;
}

//add 8-bit signed value to stack pointer no carry (1)
void GBCPU::ADDSPE8() {
	int8_t value = Read(pc++);
	sp = AddAndSetFlagsU16FromS8(sp, value, false);

	remainingCycles = 16;
}




//subtract 8-bit register from accumulator with carry (7)
void GBCPU::SBCAR8(uint8_t reg)
{
	a = SubAndSetFlagsU8(a, reg, true);

	remainingCycles = 4;
}

//subtract HL addressed byte from a with carry (1)
void GBCPU::SBCAHL() {
	a = SubAndSetFlagsU8(a, Read(GetHL()), true);

	remainingCycles = 8;
}

//subtract 8-bit value from a with carry (1)
void GBCPU::SBCAN8() {
	a = SubAndSetFlagsU8(a, Read(pc), true);
	pc++;

	remainingCycles = 8;
}

//subtract 8-bit register from accumulator no carry (7)
void GBCPU::SUBAR8(uint8_t reg) {
	a = SubAndSetFlagsU8(a, reg, false);

	remainingCycles = 4;
}

//subtract HL addressed byte from a no carry (1)
void GBCPU::SUBAHL() {
	a = SubAndSetFlagsU8(a, Read(GetHL()), false);

	remainingCycles = 8;
}

//subtract 8-bit value from a no carry (1)
void GBCPU::SUBAN8() {
	a = SubAndSetFlagsU8(a, Read(pc), false);
	pc++;

	remainingCycles = 8;
}

//compare 8-bit register with accumulator (7)
void GBCPU::CPAR8(uint8_t reg) {
	CompareAndSetFlags(a, reg);

	remainingCycles = 4;
}

//compare HL addressed byte with accumulator (1)
void GBCPU::CPAHL() {
	CompareAndSetFlags(a, Read(GetHL()));

	remainingCycles = 8;
}

//compare 8-bit value with accumulator (1)
void GBCPU::CPAN8() {
	CompareAndSetFlags(a, Read(pc++));

	remainingCycles = 8;
}

//increment 8-bit register (7)
void GBCPU::INCR8(uint8_t& reg) {
	reg = IncrementAndSetFlagsU8(reg);
	remainingCycles = 4;
}

//increment HL addressed byte (1)
void GBCPU::INC_HL_() {
	uint16_t address = GetHL();
	Write(address, IncrementAndSetFlagsU8(Read(address)));

	remainingCycles = 12;
}



//decrement 8-bit register (7)
void GBCPU::DECR8(uint8_t& reg) {
	reg = DecrementAndSetFlagsU8(reg);
	remainingCycles = 4;
}

//decrement HL addressed byte (1)
void GBCPU::DEC_HL_() {
	uint16_t address = GetHL();
	Write(address, DecrementAndSetFlagsU8(Read(address)));

	remainingCycles = 12;
}

void GBCPU::INCBC() {
	SetBC(IncrementAndSetFlagsU16(GetBC()));

	remainingCycles = 8;
}

void GBCPU::INCDE() {
	SetDE(IncrementAndSetFlagsU16(GetDE()));

	remainingCycles = 8;
}

void GBCPU::INCHL() {
	SetHL(IncrementAndSetFlagsU16(GetHL()));

	remainingCycles = 8;
}

void GBCPU::DECBC() {
	SetBC(DecrementAndSetFlagsU16(GetBC()));

	remainingCycles = 8;
}

void GBCPU::DECDE() {
	SetDE(DecrementAndSetFlagsU16(GetDE()));

	remainingCycles = 8;
}

void GBCPU::DECHL() {
	SetHL(DecrementAndSetFlagsU16(GetHL()));

	remainingCycles = 8;
}





//AND a and 8-bit register
void GBCPU::ANDAR8(uint8_t reg) {
	a = AndAndSetFlags(a, reg);

	remainingCycles = 4;
}

//AND a and HL addressed
void GBCPU::ANDAHL() {
	a = AndAndSetFlags(a, Read(GetHL()));

	remainingCycles = 8;
}

//AND a and 8-bit value
void GBCPU::ANDAN8() {
	a = AndAndSetFlags(a, Read(pc++));

	remainingCycles = 8;
}

//OP a and 8-bit register
void GBCPU::ORAR8(uint8_t reg) {
	a = OrAndSetFlags(a, reg);

	remainingCycles = 4;
}

//OR a and HL addressed
void GBCPU::ORAHL() {
	a = OrAndSetFlags(a, Read(GetHL()));

	remainingCycles = 8;
}

//OR a and 8-bit value
void GBCPU::ORAN8() {
	a = OrAndSetFlags(a, Read(pc++));

	remainingCycles = 8;
}

//XOR a and 8-bit register
void GBCPU::XORAR8(uint8_t reg) {
	a = XorAndSetFlags(a, reg);

	remainingCycles = 4;
}

//XOR a and HL addressed
void GBCPU::XORAHL() {
	a = XorAndSetFlags(a, Read(GetHL()));

	remainingCycles = 8;
}

//XOR a and 8-bit value
void GBCPU::XORAN8() {
	a = XorAndSetFlags(a, Read(pc++));

	remainingCycles = 8;
}

//ComPLement accumulator (-ive)
void GBCPU::CPL() {
	a = ~a;

	remainingCycles = 4;
}





//increment stack pointer
void GBCPU::INCSP() {
	sp++;

	remainingCycles = 8;
}

//decrement stack pointer
void GBCPU::DECSP() {
	sp--;

	remainingCycles = 8;
}

//pushes
void GBCPU::PUSHAF() {
	sp--;
	Write(sp, a);
	sp--;
	Write(sp, GetF() & 0xFF);

	remainingCycles = 16;
}

void GBCPU::PUSHBC() {
	sp--;
	Write(sp, b);
	sp--;
	Write(sp, c);

	remainingCycles = 16;
}

void GBCPU::PUSHDE() {
	sp--;
	Write(sp, d);
	sp--;
	Write(sp, e);

	remainingCycles = 16;
}

void GBCPU::PUSHHL() {
	sp--;
	Write(sp, h);
	sp--;
	Write(sp, l);

	remainingCycles = 16;
}

//pops
void GBCPU::POPAF() {
	SetF(Read(sp));
	sp++;
	a = Read(sp);
	sp++;

	remainingCycles = 12;
}

void GBCPU::POPBC() {
	c = Read(sp);
	sp++;
	b = Read(sp);
	sp++;

	remainingCycles = 12;
}

void GBCPU::POPDE() {
	e = Read(sp);
	sp++;
	d = Read(sp);
	sp++;

	remainingCycles = 12;
}

void GBCPU::POPHL() {
	l = Read(sp);
	sp++;
	h = Read(sp);
	sp++;

	remainingCycles = 12;
}



// jumps
void GBCPU::JPCCN16(bool condition) {
	if (!condition) {
		pc++;
		pc++;
		remainingCycles = 12;
		return;
	}
	pc = ReadDoublePCI();

	remainingCycles = 16;
}

void GBCPU::JPHL() {
	pc = GetHL();;

	remainingCycles = 1;
}

//relative Jumps
void GBCPU::JRCCN16(bool condition) {
	if (!condition) {
		pc++;
		remainingCycles = 8;
		return;
	}
	int8_t relAddress = Read(pc++);
	int16_t signedPc = (int16_t)pc;
	signedPc += (int16_t)relAddress;
	pc = (uint16_t)signedPc;

	remainingCycles = 12;
}

//calls
void GBCPU::CALLCCN16(bool condition) {

	if (!condition) {
		pc++;
		pc++;
		remainingCycles = 12;
		return;
	}

	uint16_t address = ReadDoublePCI();
	sp--;
	Write(sp, (pc & 0xFF00) >> 8);
	sp--;
	Write(sp, pc & 0xFF);
	pc = address;

	remainingCycles = 24;
}

void GBCPU::RSTVEC(uint16_t address) {
	sp--;
	Write(sp, (pc & 0xFF00) >> 8);
	sp--;
	Write(sp, pc & 0xFF);
	pc = address;

	remainingCycles = 16;
}

//returns
void GBCPU::RET() {
	uint8_t lo = Read(sp);
	sp++;
	uint8_t hi = Read(sp);
	sp++;
	pc = (hi << 8) | lo;

	remainingCycles = 16;
}

void GBCPU::RETCC(bool condition) {
	if (!condition) {
		remainingCycles = 8;
		return;
	}
	uint8_t lo = Read(sp);
	sp++;
	uint8_t hi = Read(sp);
	sp++;
	pc = (hi << 8) | lo;

	remainingCycles = 20;
}

void GBCPU::RETI() {
	uint8_t lo = Read(sp);
	sp++;
	uint8_t hi = Read(sp);
	sp++;
	pc = (hi << 8) | lo;
	interruptsEnabled = true;

	remainingCycles = 16;
}


// STOP
void GBCPU::STOP() {
	pc++;

	remainingCycles = 4;
	return;
}

void GBCPU::DAA() {
	// double check flags for this

	uint8_t adjustment = 0;

	if (nf) {
		adjustment += hf ? Read(0x0006) : 0;
		adjustment += cf ? Read(0x0060) : 0;
		a -= adjustment;
	}
	else {
		adjustment += (hf || ((a & Read(0x000F)) > Read(0x0009))) ? Read(0x0006) : 0;
		adjustment += (cf || (a > Read(0x0099))) ? Read(0x0060) : 0;
		a += adjustment;
	}

	SetFlags(a == 0, -1, 0, a > 0x99);

	remainingCycles = 4;
}

//enable interruts
void GBCPU::EI() {
	enableIntteruptsAfterNext = true;

	remainingCycles = 4;
}

//enable interruts
void GBCPU::DI() {
	interruptsEnabled = false;

	remainingCycles = 4;
}

void GBCPU::HALT(){

}

// carry flag instructions
void GBCPU::CCF() {
	bool zeroCF = cf ? false : true;
	SetFlags(-1, 0, 0, zeroCF);

	remainingCycles = 4;
}

void GBCPU::SCF() {
	SetFlags(-1, 0, 0, 1);

	remainingCycles = 4;
}


// bit shift instructions

//bit shift left
void GBCPU::RLR8(uint8_t& reg) {
	uint8_t carry = reg & 0b10000000;
	reg = reg << 1;
	if (cf) { reg++; }
	SetFlags(reg == 0, 0, 0, carry);

	remainingCycles = 8;
}

void GBCPU::RLHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	uint8_t carry = readByte & 0b10000000;
	readByte = readByte << 1;
	if (cf) { readByte++; }
	Write(hl,readByte);
	SetFlags(readByte == 0, -1, -1, carry);

	remainingCycles = 16;
}

void GBCPU::RLA() {
	uint8_t carry = a & 0b10000000;
	a = a << 1;
	if (cf) { a++; }
	SetFlags(0, 0, 0, carry);

	remainingCycles = 4;
}

// shift left not including carry
void GBCPU::RLCR8(uint8_t& reg) {
	uint8_t carry = reg & 0b10000000;
	reg = reg << 1;
	if (carry) { reg++; }
	SetFlags(reg == 0, 0, 0, carry);

	remainingCycles = 8;
}

void GBCPU::RLCHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	uint8_t carry = readByte & 0b10000000;
	readByte = readByte << 1;
	if (carry) { readByte++; }
	Write(hl, readByte);
	SetFlags(readByte == 0, 0, 0, carry);

	remainingCycles = 16;
}


void GBCPU::RLCA() {
	uint8_t carry = a & 0b10000000;
	a = a << 1;
	if (carry) { a++; }
	SetFlags(0, 0, 0, carry);

	remainingCycles = 4;
}

// rotate right
void GBCPU::RRR8(uint8_t& reg) {
	uint8_t carry = reg & 0b00000001;
	reg = reg >> 1;
	if (cf) {
		reg += 0b10000000;}
	SetFlags(reg == 0, -1, -1, carry);

	remainingCycles = 8;
}

void GBCPU::RRHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	uint8_t carry = readByte & 0b00000001;
	readByte = readByte >> 1;
	if (cf) { readByte ^= 0b10000000; }
	Write(hl, readByte);
	SetFlags(readByte == 0, 0, 0, carry);

	remainingCycles = 16;
}

void GBCPU::RRA() {
	uint8_t carry = a & 0b00000001;
	a = a >> 1;
	if (cf) { a ^= 0b10000000; }
	SetFlags(0, 0, 0, carry);

	remainingCycles = 4;
}

//rotate right not through carry bit
void GBCPU::RRCR8(uint8_t& reg) {
	uint8_t carry = reg & 0b00000001;
	reg = reg >> 1;
	if (carry) { reg ^= 0b10000000; }
	SetFlags(reg == 0, 0, 0, carry);

	remainingCycles = 8;
}

void GBCPU::RRCHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	uint8_t carry = readByte & 0b00000001;
	readByte = readByte >> 1;
	if (carry) { readByte ^= 0b10000000; }
	Write(hl, readByte);
	SetFlags(readByte == 0, 0, 0, carry);

	remainingCycles = 16;
}

void GBCPU::RRCA() {
	uint8_t carry = a & 0b00000001;
	a = a >> 1;
	if (carry) { a ^= 0b10000000; }
	SetFlags(0, 0, 0, carry);

	remainingCycles = 4;
}

//bit shift left arithmeticly into carry flag (no wrap around)
void GBCPU::SLAR8(uint8_t& reg) {
	bool setCf = reg >> 7;
	reg = reg << 1;
	SetFlags(reg == 0, 0, 0, setCf);

	remainingCycles = 8;
}

void GBCPU::SLAHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	bool setCf = readByte >> 7;
	readByte = readByte << 1;
	Write(hl, readByte);
	SetFlags(readByte == 0, 0, 0, setCf);

	remainingCycles = 16;
}

//bit shift right arithmeticly into carry flag (no wrap around)
void GBCPU::SRAR8(uint8_t& reg) {
	bool setCf = reg & 0b00000001;
	bool setBit7 = reg & 0b10000000;
	reg = reg >> 1;
	if (setBit7) { reg ^= 0b10000000; }
	SetFlags(reg == 0, 0, 0, setCf);

	remainingCycles = 8;
}

void GBCPU::SRAHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	bool setCf = readByte & 0b00000001;
	bool setBit7 = readByte & 0b10000000;
	readByte = readByte >> 1;
	if (setBit7) { readByte ^= 0b10000000; }
	Write(hl, readByte);
	SetFlags(readByte == 0, 0, 0, setCf);

	remainingCycles = 16;
}

//bit shift right logically into carry flag (no wrap around)
void GBCPU::SRLR8(uint8_t &reg) {
	bool setCf = reg & 0b00000001;
	reg = reg >> 1;
	SetFlags(reg == 0, 0, 0, setCf);

	remainingCycles = 8;
}

void GBCPU::SRLHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	bool setCf = readByte & 0b00000001;
	readByte = readByte >> 1;
	Write(hl, readByte);
	SetFlags(readByte == 0, 0, 0, setCf);

	remainingCycles = 16;
}

void GBCPU::SWAPR8(uint8_t& reg) {
	uint8_t hi = reg & 0b11110000;
	uint8_t lo = reg & 0b00001111;
	reg = (hi >> 4) + (lo << 4);
	SetFlags(reg == 0, 0, 0, 0);

	remainingCycles = 8;
}

void GBCPU::SWAPHL() {
	uint16_t hl = GetHL();
	uint8_t readByte = Read(hl);
	uint8_t hi = readByte & 0b11110000;
	uint8_t lo = readByte & 0b00001111;
	readByte = (hi >> 4) + (lo << 4);
	SetFlags(readByte == 0, 0, 0, 0);

	remainingCycles = 16;
}

//test bit number u of register R8
void GBCPU::BITR8(uint8_t bitNumber, uint8_t& reg) {
	if (bitNumber > 7) {
		XXX();
	}
	uint8_t bitSelector = 0b00000001 << bitNumber;
	bool setZ = (reg & bitSelector) > 0;
	SetFlags(setZ, 0, 1, -1);

	remainingCycles = 8;
}

void GBCPU::BITHL(uint8_t bitNumber) {
	if (bitNumber > 7) {
		XXX();
	}

	uint16_t hl = GetHL();
	uint8_t bitSelector = 0b00000001 << bitNumber;
	uint8_t readByte = Read(hl);

	bool setZ = (readByte & bitSelector) > 0;
	SetFlags(setZ, 0, 1, -1);

	remainingCycles = 12;
}

//set bit number u of register R8 to 0
void GBCPU::RESR8(uint8_t bitNumber, uint8_t& reg) {
	if (bitNumber > 7) {
		XXX();
	}
	uint8_t bitSetter = 0b00000001 << bitNumber;
	reg |= bitSetter;

	remainingCycles = 8;
}

void GBCPU::RESHL(uint8_t bitNumber) {
	if (bitNumber > 7) {
		XXX();
	}

	uint16_t hl = GetHL();
	uint8_t bitSetter = 0b00000001 << bitNumber;
	uint8_t readByte = Read(hl);
	readByte |= bitSetter;
	Write(hl, readByte);

	remainingCycles = 12;
}

//est bit number u of register R8 to 1
void GBCPU::SETR8(uint8_t bitNumber, uint8_t& reg) {
	if (bitNumber > 7) {
		XXX();
	}
	uint8_t bitSetter = 0b11111110 << bitNumber;
	reg &= bitSetter;

	remainingCycles = 8;
}

void GBCPU::SETHL(uint8_t bitNumber) {
	if (bitNumber > 7) {
		XXX();
	}

	uint16_t hl = GetHL();
	uint8_t bitSetter = 0b11111110 << bitNumber;
	uint8_t readByte = Read(hl);
	readByte &= bitSetter;
	Write(hl, readByte);

	remainingCycles = 12;
}





// intermediate functions to specify registers

// 8-bit register from 8-but register loads (49)
// Load B

void GBCPU::LDBB() {LDR8R8(b, b);}
void GBCPU::LDBC() {LDR8R8(b, c);}
void GBCPU::LDBD() {LDR8R8(b, d);}
void GBCPU::LDBE() {LDR8R8(b, e);}
void GBCPU::LDBH() {LDR8R8(b, h);}
void GBCPU::LDBL() {LDR8R8(b, l);}
void GBCPU::LDBA() {LDR8R8(b, a);}

// Load C

void GBCPU::LDCB() {LDR8R8(c, b);}
void GBCPU::LDCC() {LDR8R8(c, c);}
void GBCPU::LDCD() {LDR8R8(c, d);}
void GBCPU::LDCE() {LDR8R8(c, e);}
void GBCPU::LDCH() {LDR8R8(c, h);}
void GBCPU::LDCL() {LDR8R8(c, l);}
void GBCPU::LDCA() {LDR8R8(c, a);}

// Load D

void GBCPU::LDDB() {LDR8R8(d, b);}
void GBCPU::LDDC() {LDR8R8(d, c);}
void GBCPU::LDDD() {LDR8R8(d, d);}
void GBCPU::LDDE() {LDR8R8(d, e);}
void GBCPU::LDDH() {LDR8R8(d, h);}
void GBCPU::LDDL() {LDR8R8(d, l);}
void GBCPU::LDDA() {LDR8R8(d, a);}

// Load E

void GBCPU::LDEB() {LDR8R8(e, b);}
void GBCPU::LDEC() {LDR8R8(e, c);}
void GBCPU::LDED() {LDR8R8(e, d);}
void GBCPU::LDEE() {LDR8R8(e, e);}
void GBCPU::LDEH() {LDR8R8(e, h);}
void GBCPU::LDEL() {LDR8R8(e, l);}
void GBCPU::LDEA() {LDR8R8(e, a);}
// Load H

void GBCPU::LDHB() {LDR8R8(h, b);}
void GBCPU::LDHC() {LDR8R8(h, c);}
void GBCPU::LDHD() {LDR8R8(h, d);}
void GBCPU::LDHE() {LDR8R8(h, e);}
void GBCPU::LDHH() {LDR8R8(h, h);}
void GBCPU::LDHL() {LDR8R8(h, l);}
void GBCPU::LDHA() {LDR8R8(h, a);}

// Load L

void GBCPU::LDLB() {LDR8R8(l, b);}
void GBCPU::LDLC() {LDR8R8(l, c);}
void GBCPU::LDLD() {LDR8R8(l, d);}
void GBCPU::LDLE() {LDR8R8(l, e);}
void GBCPU::LDLH() {LDR8R8(l, h);}
void GBCPU::LDLL() {LDR8R8(l, l);}
void GBCPU::LDLA() {LDR8R8(l, a);}

// Load A

void GBCPU::LDAB() {LDR8R8(a, b);}
void GBCPU::LDAC() {LDR8R8(a, c);}
void GBCPU::LDAD() {LDR8R8(a, d);}
void GBCPU::LDAE() {LDR8R8(a, e);}
void GBCPU::LDAH() {LDR8R8(a, h);}
void GBCPU::LDAL() {LDR8R8(a, l);}
void GBCPU::LDAA() {LDR8R8(a, a);}

// 8-bit register from 8-bit value loads (7)

void GBCPU::LDBN8() {LDR8N8(b);}
void GBCPU::LDCN8() {LDR8N8(c);}
void GBCPU::LDDN8() {LDR8N8(d);}
void GBCPU::LDEN8() {LDR8N8(e);}
void GBCPU::LDHN8() {LDR8N8(h);}
void GBCPU::LDLN8() {LDR8N8(l);}
void GBCPU::LDAN8() {LDR8N8(a);}

//16-bit register from 16-bit value loads

void GBCPU::LDBCN16() {	LDR16N16(b, c);}
void GBCPU::LDDEN16() {	LDR16N16(d, e);}
void GBCPU::LDHLN16() {	LDR16N16(h, l);}
//8-bit byte at 16-bit addrress from 8-bit register (7)

void GBCPU::LDHLB() {LDHLR8(b);}
void GBCPU::LDHLC() {LDHLR8(c);}
void GBCPU::LDHLD() {LDHLR8(d);}
void GBCPU::LDHLE() {LDHLR8(e);}
void GBCPU::LDHLH() {LDHLR8(h);}
void GBCPU::LDHLL() {LDHLR8(l);}
void GBCPU::LDHLA() {LDHLR8(a);}

//8-bit byte at 16-bit address from 8-bit value (1)
//unique so in operation types section above

//8-bit register from HL address (7)
void GBCPU::LDBHL() {LDR8HL(b);}
void GBCPU::LDCHL() {LDR8HL(c);}
void GBCPU::LDDHL() {LDR8HL(d);}
void GBCPU::LDEHL() {LDR8HL(e);}
void GBCPU::LDHHL() {LDR8HL(h);}
void GBCPU::LDLHL() {LDR8HL(l);}
void GBCPU::LDAHL() {LDR8HL(a);}

//16-bit address from accumulator  (2)
//easier to implement seperately, so in operation tyes above

//8-bit arithmetic instructions
// //add 8-bit register to a (7)
void GBCPU::ADCAB() {ADCAR8(b);}
void GBCPU::ADCAC() {ADCAR8(c);}
void GBCPU::ADCAD() {ADCAR8(d);}
void GBCPU::ADCAE() {ADCAR8(e);}
void GBCPU::ADCAH() {ADCAR8(h);}
void GBCPU::ADCAL() {ADCAR8(l);}
void GBCPU::ADCAA() {ADCAR8(a);}

//add 8-bit register to 1 no carry (7)

void GBCPU::ADDAB() { ADDAR8(b); }
void GBCPU::ADDAC() { ADDAR8(c); }
void GBCPU::ADDAD() { ADDAR8(d); }
void GBCPU::ADDAE() { ADDAR8(e); }
void GBCPU::ADDAH() { ADDAR8(h); }
void GBCPU::ADDAL() { ADDAR8(l); }
void GBCPU::ADDAA() { ADDAR8(a); }

//subtract 8-bit register from accumulator with carry (7)

void GBCPU::SBCAB() { SBCAR8(b); }
void GBCPU::SBCAC() { SBCAR8(c); }
void GBCPU::SBCAD() { SBCAR8(d); }
void GBCPU::SBCAE() { SBCAR8(e); }
void GBCPU::SBCAH() { SBCAR8(h); }
void GBCPU::SBCAL() { SBCAR8(l); }
void GBCPU::SBCAA() { SBCAR8(a); }

//subtract 8-bit register from accumulator no carry (7)

void GBCPU::SUBAB() { SUBAR8(b); }
void GBCPU::SUBAC() { SUBAR8(c); }
void GBCPU::SUBAD() { SUBAR8(d); }
void GBCPU::SUBAE() { SUBAR8(e); }
void GBCPU::SUBAH() { SUBAR8(h); }
void GBCPU::SUBAL() { SUBAR8(l); }
void GBCPU::SUBAA() { SUBAR8(a); }

//increment 8-bit register (7)

void GBCPU::INCB() { INCR8(b); }
void GBCPU::INCC() { INCR8(c); }
void GBCPU::INCD() { INCR8(d); }
void GBCPU::INCE() { INCR8(e); }
void GBCPU::INCH() { INCR8(h); }
void GBCPU::INCL() { INCR8(l); }
void GBCPU::INCA() { INCR8(a); }

//decrement 8-bit register (7)

void GBCPU::DECB() { DECR8(b); }
void GBCPU::DECC() { DECR8(c); }
void GBCPU::DECD() { DECR8(d); }
void GBCPU::DECE() { DECR8(e); }
void GBCPU::DECH() { DECR8(h); }
void GBCPU::DECL() { DECR8(l); }
void GBCPU::DECA() { DECR8(a); }

////compare 8-bit register with accumulator (7)

void GBCPU::CPAB() { CPAR8(b); }
void GBCPU::CPAC() { CPAR8(c); }
void GBCPU::CPAD() { CPAR8(d); }
void GBCPU::CPAE() { CPAR8(e); }
void GBCPU::CPAH() { CPAR8(h); }
void GBCPU::CPAL() { CPAR8(l); }
void GBCPU::CPAA() { CPAR8(a); }

//and a and 8-bit register (7)

void GBCPU::ANDAB() { ANDAR8(b); }
void GBCPU::ANDAC() { ANDAR8(c); }
void GBCPU::ANDAD() { ANDAR8(d); }
void GBCPU::ANDAE() { ANDAR8(e); }
void GBCPU::ANDAH() { ANDAR8(h); }
void GBCPU::ANDAL() { ANDAR8(l); }
void GBCPU::ANDAA() { ANDAR8(a); }

//and a and 8-bit register (7)

void GBCPU::ORAB() { ORAR8(b); }
void GBCPU::ORAC() { ORAR8(c); }
void GBCPU::ORAD() { ORAR8(d); }
void GBCPU::ORAE() { ORAR8(e); }
void GBCPU::ORAH() { ORAR8(h); }
void GBCPU::ORAL() { ORAR8(l); }
void GBCPU::ORAA() { ORAR8(a); }

//and a and 8-bit register (7)

void GBCPU::XORAB() { XORAR8(b); }
void GBCPU::XORAC() { XORAR8(c); }
void GBCPU::XORAD() { XORAR8(d); }
void GBCPU::XORAE() { XORAR8(e); }
void GBCPU::XORAH() { XORAR8(h); }
void GBCPU::XORAL() { XORAR8(l); }
void GBCPU::XORAA() { XORAR8(a); }

//jumps (5)

void GBCPU::JPN16() { JPCCN16(true); }
void GBCPU::JPZN16() { JPCCN16(zf); }
void GBCPU::JPNZN16() { JPCCN16(!zf); }
void GBCPU::JPCN16() { JPCCN16(cf); }
void GBCPU::JPNCN16() { JPCCN16(!cf); }

//relative jumps (5)

void GBCPU::JRN16() { JRCCN16(true); }
void GBCPU::JRZN16() { JRCCN16(zf); }
void GBCPU::JRNZN16() { JRCCN16(!zf); }
void GBCPU::JRCN16() { JRCCN16(cf); }
void GBCPU::JRNCN16() { JRCCN16(!cf); }

//calls (5)

void GBCPU::CALLN16() { CALLCCN16(true); }
void GBCPU::CALLZN16() { CALLCCN16(zf); }
void GBCPU::CALLNZN16() { CALLCCN16(!zf); }
void GBCPU::CALLCN16() { CALLCCN16(cf); }
void GBCPU::CALLNCN16() { CALLCCN16(!cf); }

//specific calls

void GBCPU::RST00() { RSTVEC(0x00); }
void GBCPU::RST08() { RSTVEC(0x08); }
void GBCPU::RST10() { RSTVEC(0x10); }
void GBCPU::RST18() { RSTVEC(0x18); }
void GBCPU::RST20() { RSTVEC(0x20); }
void GBCPU::RST28() { RSTVEC(0x28); }
void GBCPU::RST30() { RSTVEC(0x30); }
void GBCPU::RST38() { RSTVEC(0x38); }

//returns
void GBCPU::RETZ() { RETCC(zf); }
void GBCPU::RETNZ() { RETCC(!zf); }
void GBCPU::RETC() { RETCC(cf); }
void GBCPU::RETNC() { RETCC(!cf); }

//rotate bits in reg and carryflag left

void GBCPU::RLB() { RLR8(b); }
void GBCPU::RLC() { RLR8(c); }
void GBCPU::RLD() { RLR8(d); }
void GBCPU::RLE() { RLR8(e); }
void GBCPU::RLH() { RLR8(h); }
void GBCPU::RLL() { RLR8(l); }

//rotate bits in reg left

void GBCPU::RLCB() { RLCR8(b); }
void GBCPU::RLCC() { RLCR8(c); }
void GBCPU::RLCD() { RLCR8(d); }
void GBCPU::RLCE() { RLCR8(e); }
void GBCPU::RLCH() { RLCR8(h); }
void GBCPU::RLCL() { RLCR8(l); }

//rotate bits in reg and carryflag RIGHT

void GBCPU::RRB() { RRR8(b); }
void GBCPU::RRC() { RRR8(c); }
void GBCPU::RRD() { RRR8(d); }
void GBCPU::RRE() { RRR8(e); }
void GBCPU::RRH() { RRR8(h); }
void GBCPU::RRL() { RRR8(l); }

//rotate bits in reg RIGHT

void GBCPU::RRCB() { RRCR8(b); }
void GBCPU::RRCC() { RRCR8(c); }
void GBCPU::RRCD() { RRCR8(d); }
void GBCPU::RRCE() { RRCR8(e); }
void GBCPU::RRCH() { RRCR8(h); }
void GBCPU::RRCL() { RRCR8(l); }

//bit shift left

void GBCPU::SLAB() { SLAR8(b); }
void GBCPU::SLAC() { SLAR8(c); }
void GBCPU::SLAD() { SLAR8(d); }
void GBCPU::SLAE() { SLAR8(e); }
void GBCPU::SLAH() { SLAR8(h); }
void GBCPU::SLAL() { SLAR8(l); }
void GBCPU::SLAA() { SLAR8(a); }

//bit shift right arithm

void GBCPU::SRAB() { SRAR8(b); }
void GBCPU::SRAC() { SRAR8(c); }
void GBCPU::SRAD() { SRAR8(d); }
void GBCPU::SRAE() { SRAR8(e); }
void GBCPU::SRAH() { SRAR8(h); }
void GBCPU::SRAL() { SRAR8(l); }
void GBCPU::SRAA() { SRAR8(a); }

//bit shift right logic

void GBCPU::SRLB() { SRLR8(b); }
void GBCPU::SRLC() { SRLR8(c); }
void GBCPU::SRLD() { SRLR8(d); }
void GBCPU::SRLE() { SRLR8(e); }
void GBCPU::SRLH() { SRLR8(h); }
void GBCPU::SRLL() { SRLR8(l); }
void GBCPU::SRLA() { SRLR8(a); }

//swap hi and lo nybble

void GBCPU::SWAPB() { SWAPR8(b); }
void GBCPU::SWAPC() { SWAPR8(c); }
void GBCPU::SWAPD() { SWAPR8(d); }
void GBCPU::SWAPE() { SWAPR8(e); }
void GBCPU::SWAPH() { SWAPR8(h); }
void GBCPU::SWAPL() { SWAPR8(l); }
void GBCPU::SWAPA() { SWAPR8(a); }

//test bit u in register r8

void GBCPU::BIT0B() { BITR8(0, b); }
void GBCPU::BIT0C() { BITR8(0, c); }
void GBCPU::BIT0D() { BITR8(0, d); }
void GBCPU::BIT0E() { BITR8(0, e); }
void GBCPU::BIT0H() { BITR8(0, h); }
void GBCPU::BIT0L() { BITR8(0, l); }
void GBCPU::BIT0A() { BITR8(0, a); }

void GBCPU::BIT1B() { BITR8(1, b); }
void GBCPU::BIT1C() { BITR8(1, c); }
void GBCPU::BIT1D() { BITR8(1, d); }
void GBCPU::BIT1E() { BITR8(1, e); }
void GBCPU::BIT1H() { BITR8(1, h); }
void GBCPU::BIT1L() { BITR8(1, l); }
void GBCPU::BIT1A() { BITR8(1, a); }

void GBCPU::BIT2B() { BITR8(2, b); }
void GBCPU::BIT2C() { BITR8(2, c); }
void GBCPU::BIT2D() { BITR8(2, d); }
void GBCPU::BIT2E() { BITR8(2, e); }
void GBCPU::BIT2H() { BITR8(2, h); }
void GBCPU::BIT2L() { BITR8(2, l); }
void GBCPU::BIT2A() { BITR8(2, a); }

void GBCPU::BIT3B() { BITR8(3, b); }
void GBCPU::BIT3C() { BITR8(3, c); }
void GBCPU::BIT3D() { BITR8(3, d); }
void GBCPU::BIT3E() { BITR8(3, e); }
void GBCPU::BIT3H() { BITR8(3, h); }
void GBCPU::BIT3L() { BITR8(3, l); }
void GBCPU::BIT3A() { BITR8(3, a); }

void GBCPU::BIT4B() { BITR8(4, b); }
void GBCPU::BIT4C() { BITR8(4, c); }
void GBCPU::BIT4D() { BITR8(4, d); }
void GBCPU::BIT4E() { BITR8(4, e); }
void GBCPU::BIT4H() { BITR8(4, h); }
void GBCPU::BIT4L() { BITR8(4, l); }
void GBCPU::BIT4A() { BITR8(4, a); }

void GBCPU::BIT5B() { BITR8(5, b); }
void GBCPU::BIT5C() { BITR8(5, c); }
void GBCPU::BIT5D() { BITR8(5, d); }
void GBCPU::BIT5E() { BITR8(5, e); }
void GBCPU::BIT5H() { BITR8(5, h); }
void GBCPU::BIT5L() { BITR8(5, l); }
void GBCPU::BIT5A() { BITR8(5, a); }

void GBCPU::BIT6B() { BITR8(6, b); }
void GBCPU::BIT6C() { BITR8(6, c); }
void GBCPU::BIT6D() { BITR8(6, d); }
void GBCPU::BIT6E() { BITR8(6, e); }
void GBCPU::BIT6H() { BITR8(6, h); }
void GBCPU::BIT6L() { BITR8(6, l); }
void GBCPU::BIT6A() { BITR8(6, a); }

void GBCPU::BIT7B() { BITR8(7, b); }
void GBCPU::BIT7C() { BITR8(7, c); }
void GBCPU::BIT7D() { BITR8(7, d); }
void GBCPU::BIT7E() { BITR8(7, e); }
void GBCPU::BIT7H() { BITR8(7, h); }
void GBCPU::BIT7L() { BITR8(7, l); }
void GBCPU::BIT7A() { BITR8(7, a); }

// bit test HL adddressed
void GBCPU::BIT0HL() { BITHL(0); }
void GBCPU::BIT1HL() { BITHL(1); }
void GBCPU::BIT2HL() { BITHL(2); }
void GBCPU::BIT3HL() { BITHL(3); }
void GBCPU::BIT4HL() { BITHL(4); }
void GBCPU::BIT5HL() { BITHL(5); }
void GBCPU::BIT6HL() { BITHL(6); }
void GBCPU::BIT7HL() { BITHL(7); }

//test bit u in register r8

void GBCPU::SET0B() { SETR8(0, b); }
void GBCPU::SET0C() { SETR8(0, c); }
void GBCPU::SET0D() { SETR8(0, d); }
void GBCPU::SET0E() { SETR8(0, e); }
void GBCPU::SET0H() { SETR8(0, h); }
void GBCPU::SET0L() { SETR8(0, l); }
void GBCPU::SET0A() { SETR8(0, a); }

void GBCPU::SET1B() { SETR8(1, b); }
void GBCPU::SET1C() { SETR8(1, c); }
void GBCPU::SET1D() { SETR8(1, d); }
void GBCPU::SET1E() { SETR8(1, e); }
void GBCPU::SET1H() { SETR8(1, h); }
void GBCPU::SET1L() { SETR8(1, l); }
void GBCPU::SET1A() { SETR8(1, a); }

void GBCPU::SET2B() { SETR8(2, b); }
void GBCPU::SET2C() { SETR8(2, c); }
void GBCPU::SET2D() { SETR8(2, d); }
void GBCPU::SET2E() { SETR8(2, e); }
void GBCPU::SET2H() { SETR8(2, h); }
void GBCPU::SET2L() { SETR8(2, l); }
void GBCPU::SET2A() { SETR8(2, a); }

void GBCPU::SET3B() { SETR8(3, b); }
void GBCPU::SET3C() { SETR8(3, c); }
void GBCPU::SET3D() { SETR8(3, d); }
void GBCPU::SET3E() { SETR8(3, e); }
void GBCPU::SET3H() { SETR8(3, h); }
void GBCPU::SET3L() { SETR8(3, l); }
void GBCPU::SET3A() { SETR8(3, a); }

void GBCPU::SET4B() { SETR8(4, b); }
void GBCPU::SET4C() { SETR8(4, c); }
void GBCPU::SET4D() { SETR8(4, d); }
void GBCPU::SET4E() { SETR8(4, e); }
void GBCPU::SET4H() { SETR8(4, h); }
void GBCPU::SET4L() { SETR8(4, l); }
void GBCPU::SET4A() { SETR8(4, a); }

void GBCPU::SET5B() { SETR8(5, b); }
void GBCPU::SET5C() { SETR8(5, c); }
void GBCPU::SET5D() { SETR8(5, d); }
void GBCPU::SET5E() { SETR8(5, e); }
void GBCPU::SET5H() { SETR8(5, h); }
void GBCPU::SET5L() { SETR8(5, l); }
void GBCPU::SET5A() { SETR8(5, a); }

void GBCPU::SET6B() { SETR8(6, b); }
void GBCPU::SET6C() { SETR8(6, c); }
void GBCPU::SET6D() { SETR8(6, d); }
void GBCPU::SET6E() { SETR8(6, e); }
void GBCPU::SET6H() { SETR8(6, h); }
void GBCPU::SET6L() { SETR8(6, l); }
void GBCPU::SET6A() { SETR8(6, a); }

void GBCPU::SET7B() { SETR8(7, b); }
void GBCPU::SET7C() { SETR8(7, c); }
void GBCPU::SET7D() { SETR8(7, d); }
void GBCPU::SET7E() { SETR8(7, e); }
void GBCPU::SET7H() { SETR8(7, h); }
void GBCPU::SET7L() { SETR8(7, l); }
void GBCPU::SET7A() { SETR8(7, a); }

// bit set to 1 HL adddressed
void GBCPU::SET0HL() { SETHL(0); }
void GBCPU::SET1HL() { SETHL(1); }
void GBCPU::SET2HL() { SETHL(2); }
void GBCPU::SET3HL() { SETHL(3); }
void GBCPU::SET4HL() { SETHL(4); }
void GBCPU::SET5HL() { SETHL(5); }
void GBCPU::SET6HL() { SETHL(6); }
void GBCPU::SET7HL() { SETHL(7); }

//test RES u in register r8

void GBCPU::RES0B() { RESR8(0, b); }
void GBCPU::RES0C() { RESR8(0, c); }
void GBCPU::RES0D() { RESR8(0, d); }
void GBCPU::RES0E() { RESR8(0, e); }
void GBCPU::RES0H() { RESR8(0, h); }
void GBCPU::RES0L() { RESR8(0, l); }
void GBCPU::RES0A() { RESR8(0, a); }

void GBCPU::RES1B() { RESR8(1, b); }
void GBCPU::RES1C() { RESR8(1, c); }
void GBCPU::RES1D() { RESR8(1, d); }
void GBCPU::RES1E() { RESR8(1, e); }
void GBCPU::RES1H() { RESR8(1, h); }
void GBCPU::RES1L() { RESR8(1, l); }
void GBCPU::RES1A() { RESR8(1, a); }

void GBCPU::RES2B() { RESR8(2, b); }
void GBCPU::RES2C() { RESR8(2, c); }
void GBCPU::RES2D() { RESR8(2, d); }
void GBCPU::RES2E() { RESR8(2, e); }
void GBCPU::RES2H() { RESR8(2, h); }
void GBCPU::RES2L() { RESR8(2, l); }
void GBCPU::RES2A() { RESR8(2, a); }

void GBCPU::RES3B() { RESR8(3, b); }
void GBCPU::RES3C() { RESR8(3, c); }
void GBCPU::RES3D() { RESR8(3, d); }
void GBCPU::RES3E() { RESR8(3, e); }
void GBCPU::RES3H() { RESR8(3, h); }
void GBCPU::RES3L() { RESR8(3, l); }
void GBCPU::RES3A() { RESR8(3, a); }

void GBCPU::RES4B() { RESR8(4, b); }
void GBCPU::RES4C() { RESR8(4, c); }
void GBCPU::RES4D() { RESR8(4, d); }
void GBCPU::RES4E() { RESR8(4, e); }
void GBCPU::RES4H() { RESR8(4, h); }
void GBCPU::RES4L() { RESR8(4, l); }
void GBCPU::RES4A() { RESR8(4, a); }

void GBCPU::RES5B() { RESR8(5, b); }
void GBCPU::RES5C() { RESR8(5, c); }
void GBCPU::RES5D() { RESR8(5, d); }
void GBCPU::RES5E() { RESR8(5, e); }
void GBCPU::RES5H() { RESR8(5, h); }
void GBCPU::RES5L() { RESR8(5, l); }
void GBCPU::RES5A() { RESR8(5, a); }

void GBCPU::RES6B() { RESR8(6, b); }
void GBCPU::RES6C() { RESR8(6, c); }
void GBCPU::RES6D() { RESR8(6, d); }
void GBCPU::RES6E() { RESR8(6, e); }
void GBCPU::RES6H() { RESR8(6, h); }
void GBCPU::RES6L() { RESR8(6, l); }
void GBCPU::RES6A() { RESR8(6, a); }

void GBCPU::RES7B() { RESR8(7, b); }
void GBCPU::RES7C() { RESR8(7, c); }
void GBCPU::RES7D() { RESR8(7, d); }
void GBCPU::RES7E() { RESR8(7, e); }
void GBCPU::RES7H() { RESR8(7, h); }
void GBCPU::RES7L() { RESR8(7, l); }
void GBCPU::RES7A() { RESR8(7, a); }

// RES set to 0 HL adddressed
void GBCPU::RES0HL() { RESHL(0); }
void GBCPU::RES1HL() { RESHL(1); }
void GBCPU::RES2HL() { RESHL(2); }
void GBCPU::RES3HL() { RESHL(3); }
void GBCPU::RES4HL() { RESHL(4); }
void GBCPU::RES5HL() { RESHL(5); }
void GBCPU::RES6HL() { RESHL(6); }
void GBCPU::RES7HL() { RESHL(7); }
