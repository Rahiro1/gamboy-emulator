#pragma once
#include <cstdint>
#include "GBBus.h"
#include <vector>
#include <string>
#include <format>
#include "CPUStateLog.h"

class GBCPU
{
public: 

    GBCPU();

    void ConnectBus(GBBus *newBus);
    void Clock();


public: // registers

    uint8_t a = 0x00;
    uint8_t b = 0x00;
    uint8_t c = 0x00;
    uint8_t d = 0x00;
    uint8_t e = 0x00;
    uint8_t h = 0x00;
    uint8_t l = 0x00; 
    uint16_t sp = 0x0000;
    uint16_t pc = 0x0000;
    uint8_t instruction;

    //flags
    bool zf = 0;   // zero flag
    bool nf = 0;   // subtraction flag
    bool hf = 0;   // half carry flag
    bool cf = 0;   // carry flag

    //getters and setters for 16-bit Registers
    uint16_t GetF();
    uint16_t GetBC();
    uint16_t GetDE();
    uint16_t GetHL();
    void SetF(uint8_t number);
    void SetBC(uint16_t number);
    void SetDE(uint16_t number);
    void SetHL(uint16_t number);

    void SetFlags(int setZ, int setN, int setH, int setC);

    //arithmetic while also setting flags operations
    //additions
    uint16_t AddAndSetFlagsU16(uint16_t x, uint16_t y, bool addCarry);
    uint8_t AddAndSetFlagsU8(uint8_t x, uint8_t y, bool addCarry);
    uint16_t AddAndSetFlagsU16FromS8(uint16_t x, int8_t y, bool addCarry );

    //subtractions
    uint8_t SubAndSetFlagsU8(uint8_t x, uint8_t y, bool addCarry);

    //compare - discards result
    void CompareAndSetFlags(uint8_t x, uint8_t y);

    //increment
    uint8_t IncrementAndSetFlagsU8(uint8_t x);
    uint16_t IncrementAndSetFlagsU16(uint16_t x);
    // decrement
    uint8_t DecrementAndSetFlagsU8(uint8_t x);
    uint16_t DecrementAndSetFlagsU16(uint16_t x);

    //bitwise AND
    uint8_t AndAndSetFlags(uint8_t x, uint8_t y);

    //bitwise OR
    uint8_t OrAndSetFlags(uint8_t x, uint8_t y);

    //bitwise XOR
    uint8_t XorAndSetFlags(uint8_t x, uint8_t y);




    // opcodes
    // do nothing (1)
    void NOP();

    //crash (1)
    void XXX();

    //loads excluding stack pointer loads (88)

    // load register from register opcodes 
    // 8-bit register from 8-bit register (49)
    void LDR8R8(uint8_t &ptrRegTo, uint8_t regFrom);
    void LDBB();    void LDBC();    void LDBD();    void LDBE();    void LDBH();    void LDBL();    void LDBA();
    void LDCB();    void LDCC();    void LDCD();    void LDCE();    void LDCH();    void LDCL();    void LDCA();
    void LDDB();    void LDDC();    void LDDD();    void LDDE();    void LDDH();    void LDDL();    void LDDA();
    void LDEB();    void LDEC();    void LDED();    void LDEE();    void LDEH();    void LDEL();    void LDEA();
    void LDHB();    void LDHC();    void LDHD();    void LDHE();    void LDHH();    void LDHL();    void LDHA();
    void LDLB();    void LDLC();    void LDLD();    void LDLE();    void LDLH();    void LDLL();    void LDLA();
    void LDAB();    void LDAC();    void LDAD();    void LDAE();    void LDAH();    void LDAL();    void LDAA();

    // 8-bit register from 8-bit value (7)
    void LDR8N8(uint8_t &ptrRegTo);
    void LDBN8();   void LDCN8();   void LDDN8();   void LDEN8();   void LDHN8();   void LDLN8();   void LDAN8();

    //16-bit register from 16-bit value (3)
    void LDR16N16(uint8_t& ptrRegToOne, uint8_t& ptrRegToTwo);
    void LDBCN16(); void LDDEN16(); void LDHLN16();

    //8-bit byte at HL addrress from 8-bit register (7)
    void LDHLR8(uint8_t regFrom);
    void LDHLB();    void LDHLC();    void LDHLD();    void LDHLE();    void LDHLH();    void LDHLL();    void LDHLA();

    //8-bit byte at HL address from 8-bit value (1)
    void LDHLN8();

    //8-bit register from HL address (7)
    void LDR8HL(uint8_t& ptrRegTo);
    void LDBHL();    void LDCHL();    void LDDHL();    void LDEHL();    void LDHHL();    void LDLHL();    void LDAHL();

    //16-bit address from accumulator (register) (2)
    // easier to implement seperately
    void LDBCA();   void LDDEA(); 

    //accumulator from memory address (1)
    void LDAN16();

    //16-bit address from accumulator (value) (1)
    void LDN16A();

    //16-bit address equal to 0xFF00 + 8-bit value from accumulator (1)
    void LDHN16A();

    //16-bit address equal to 0xFF00 + register C from accumulator (1)
    void LDHCA();

    //accumulator from 16-bit address (register) (2)
    void LDABC();   void LDADE();

    //accumulator from 16-bit address (value) (1)
    void LDHAN16();

    //accumulator from 0xFF00 + C (1) 
    void LDHAC();

    //HL register address from accumulator and increment HL after (1)
    void LDHLIA();

    //HL register address from accumulator and decrement HL after (1)
    void LDHLDA();

    //accumulator from HL address amd increment HL after (1)
    void LDAHLI();

    //accumulator from HL address amd decrement HL after (1)
    void LDAHLD();


    //aritmetic instructions (70)

    //8-bit arithmetic instructions
    //add 8-bit register to a (7)
    void ADCAR8(uint8_t regFrom);
    void ADCAB();    void ADCAC();    void ADCAD();    void ADCAE();    void ADCAH();    void ADCAL();    void ADCAA();

    //add HL addressed byte plus carry flag to a (1)
    void ADCAHL();

    //add 8-bit value to a with carry (1)
    void ADCAN8();

    //add 8-bit register to 1 no carry (7)
    void ADDAR8(uint8_t regFrom);
    void ADDAB();    void ADDAC();    void ADDAD();    void ADDAE();    void ADDAH();    void ADDAL();    void ADDAA();

    //add HL addressed byte to a no carry (1)
    void ADDAHL();

    //add 8-bit value to a no carry (1)
    void ADDAN8();

    //add stack pointer to HL no carry (1)
    void ADDHLSP();

    //add 8-bit signed value to stack pointer no carry (1)
    void ADDSPE8();

    //subtract 8-bit register from accumulator with carry (7)
    void SBCAR8(uint8_t reg);
    void SBCAB();    void SBCAC();    void SBCAD();    void SBCAE();    void SBCAH();    void SBCAL();    void SBCAA();
    
    //subtract HL addressed byte from a with carry (1)
    void SBCAHL();

    //subtract 8-bit value from a with carry (1)
    void SBCAN8();

    //subtract 8-bit register from accumulator no carry (7)
    void SUBAR8(uint8_t reg);
    void SUBAB();    void SUBAC();    void SUBAD();    void SUBAE();    void SUBAH();    void SUBAL();    void SUBAA();

    //subtract HL addressed byte from a no carry (1)
    void SUBAHL();

    //subtract 8-bit value from a no carry (1)
    void SUBAN8();

    //compare 8-bit register with accumulator (7)
    void CPAR8(uint8_t reg);
    void CPAB();    void CPAC();    void CPAD();    void CPAE();    void CPAH();    void CPAL();    void CPAA();

    //compare HL addressed byte with accumulator (1)
    void CPAHL();

    //compare 8-bit value with accumulator (1)
    void CPAN8();

    //increment 8-bit register (7)
    void INCR8(uint8_t& reg);
    void INCB();    void INCC();    void INCD();    void INCE();    void INCH();    void INCL();    void INCA();

    //increment HL addressed byte (1)
    void INC_HL_();

    //decrement 8-bit register (7)
    void DECR8(uint8_t& reg);
    void DECB();    void DECC();    void DECD();    void DECE();    void DECH();    void DECL();    void DECA();

    //decrement HL addressed byte (1)
    void DEC_HL_();

    //add 16-bit register to HL no carry (3)
    void ADDHLBC(); void ADDHLDE(); void ADDHLHL();

    //16-bit increment (2)
    void INCBC();   void INCDE(); void INCHL();

    //16-bit decrement (2)
    void DECBC();   void DECDE(); void DECHL();





    //Bitwise Logic Instructions (28)
    

    //AND a and 8-bit register (7)
    void ANDAR8(uint8_t reg);
    void ANDAB();    void ANDAC();    void ANDAD();    void ANDAE();    void ANDAH();    void ANDAL();    void ANDAA();

    //AND a and HL addressed (1)
    void ANDAHL();

    //AND a and 8-bit value (1)
    void ANDAN8();

    //OP a and 8-bit register (7)
    void ORAR8(uint8_t reg);
    void ORAB();    void ORAC();    void ORAD();    void ORAE();    void ORAH();    void ORAL();    void ORAA();

    //OR a and HL addressed (1)
    void ORAHL();

    //OR a and 8-bit value (1)
    void ORAN8();

    //XOR a and 8-bit register (7)
    void XORAR8(uint8_t reg);
    void XORAB();    void XORAC();    void XORAD();    void XORAE();    void XORAH();    void XORAL();    void XORAA();

    //XOR a and HL addressed (1)
    void XORAHL();

    //XOR a and 8-bit value (1)
    void XORAN8();

    //ComPLement accumulator (NOT) (1)
    void CPL();




    //stack instrucions (14)
    

    //increment stack pointer (1)
    void INCSP();

    //decrement stack pointer (1)
    void DECSP();

    //pushes (4)
    void PUSHAF();  void PUSHBC();  void PUSHDE();  void PUSHHL();

    //pops (4)
    void POPAF();  void POPBC();  void POPDE();  void POPHL();

    //stack pointer from 16-bit value (1)
    void LDSPN16();

    //16-bit address from stack pointer (1)
    void LDN16SP();

    //stack pointer from HL (1)
    void LDSPHL();

    //loads HL, but first loaads the stck pointer plus a signed 8-bit value (1)
    void LDHLSPADDE8();



    //Jumps and subroutines - can be conditional on Z or C (30)
    

    //jumps (5)
    void JPCCN16(bool condition);
    void JPN16();   void JPZN16();  void JPNZN16();  void JPCN16(); void JPNCN16();

    //jump hl - only reads 1 byte instead of 3 (1)
    void JPHL();

    //relative Jumps (5)
    void JRCCN16(bool condition);
    void JRN16();   void JRZN16(); void JRNZN16();  void JRCN16();  void JRNCN16();

    //calls - push next adress on the stack and jump to pc (5)
    void CALLCCN16(bool condition);
    void CALLN16(); void CALLZN16();    void CALLNZN16();   void CALLCN16();     void CALLNCN16();

    //specific calls - quicker calls for specific memory locations (8)
    void RSTVEC(uint16_t address);
    void RST00();   void RST08();   void RST10();   void RST18();   void RST20();   void RST28();   void RST30();   void RST38();

    //returns - 16 cpu cycles (1)
    void RET();

    // return with condition - 20/8 cpu cycles (4)
    void RETCC(bool condition);
    void RETZ(); void RETNZ();    void RETC(); void RETNC();

    //return and enable interrupts (1)
    void RETI();


    // other instructions

    //STOP - not implemented - switches to power saving mode (for if the console is left on by accident , can be used on CGB for speed switching to and from double speed)
    void STOP();

    //decimal adjust accumulator (1)
    void DAA();

    //enable interrupts
    void EI();

    //disable interrupts
    void DI();

    void HALT();

    //carry flag instructions - compliment and set
    void CCF(); void SCF();


    // bit shift instructions

    //bit shift left through carry flag
    void RLR8(uint8_t &reg);
    void RLB();    void RLC();    void RLD();    void RLE();    void RLH();    void RLL();
    // accumulator requres 4 cycles instead of two
    void RLA();
    // HL addressed
    void RLHL();

    //bit shift left not through carry flag 
    void RLCR8(uint8_t& reg);
    void RLCB();    void RLCC();    void RLCD();    void RLCE();    void RLCH();    void RLCL();
    // accumulator requres 4 cycles instead of two
    void RLCA();
    // HL addressed
    void RLCHL();

    //bit shift right through carry flag
    void RRR8(uint8_t& reg);
    void RRB();    void RRC();    void RRD();    void RRE();    void RRH();    void RRL();
    // accumulator requres 4 cycles instead of two
    void RRA();
    // HL addressed
    void RRHL();

    //bit shift right not through carry flag 
    void RRCR8(uint8_t& reg);
    void RRCB();    void RRCC();    void RRCD();    void RRCE();    void RRCH();    void RRCL();
    // accumulator requres 4 cycles instead of two
    void RRCA();
    // HL addressed
    void RRCHL();

    //bit shift left arithmeticly into carry flag (no wrap around)
    void SLAR8(uint8_t& reg);
    void SLAB();    void SLAC();    void SLAD();    void SLAE();    void SLAH();    void SLAL();    void SLAA();
    // HL addressed
    void SLAHL();

    //bit shift left
    void SRAR8(uint8_t& reg);
    void SRAB();    void SRAC();    void SRAD();    void SRAE();    void SRAH();    void SRAL();    void SRAA();
    // HL addressed
    void SRAHL();

    //bit shift left
    void SRLR8(uint8_t& reg);
    void SRLB();    void SRLC();    void SRLD();    void SRLE();    void SRLH();    void SRLL();    void SRLA();
    // HL addressed
    void SRLHL();

    //swap the upper four bits with the lower four
    void SWAPR8(uint8_t& reg);
    void SWAPB();    void SWAPC();    void SWAPD();    void SWAPE();    void SWAPH();    void SWAPL();
    // accumulator requres 4 cycles instead of two
    void SWAPA();
    // HL addressed
    void SWAPHL();


    //bit flag instructions

    //test bit (56)
    void BITR8(uint8_t bitNumber, uint8_t &reg);
    void BIT0B();    void BIT0C();    void BIT0D();    void BIT0E();    void BIT0H();    void BIT0L();  void BIT0A();
    void BIT1B();    void BIT1C();    void BIT1D();    void BIT1E();    void BIT1H();    void BIT1L();  void BIT1A();
    void BIT2B();    void BIT2C();    void BIT2D();    void BIT2E();    void BIT2H();    void BIT2L();  void BIT2A();
    void BIT3B();    void BIT3C();    void BIT3D();    void BIT3E();    void BIT3H();    void BIT3L();  void BIT3A();
    void BIT4B();    void BIT4C();    void BIT4D();    void BIT4E();    void BIT4H();    void BIT4L();  void BIT4A();
    void BIT5B();    void BIT5C();    void BIT5D();    void BIT5E();    void BIT5H();    void BIT5L();  void BIT5A();
    void BIT6B();    void BIT6C();    void BIT6D();    void BIT6E();    void BIT6H();    void BIT6L();  void BIT6A();
    void BIT7B();    void BIT7C();    void BIT7D();    void BIT7E();    void BIT7H();    void BIT7L();  void BIT7A();
    // HL addressed (8)
    void BITHL(uint8_t bitNumber);
    void BIT0HL();
    void BIT1HL();
    void BIT2HL();
    void BIT3HL();
    void BIT4HL();
    void BIT5HL();
    void BIT6HL();
    void BIT7HL();

    //set bit to 1
    void SETR8(uint8_t bitNumber, uint8_t& reg);
    void SET0B();    void SET0C();    void SET0D();    void SET0E();    void SET0H();    void SET0L();  void SET0A();
    void SET1B();    void SET1C();    void SET1D();    void SET1E();    void SET1H();    void SET1L();  void SET1A();
    void SET2B();    void SET2C();    void SET2D();    void SET2E();    void SET2H();    void SET2L();  void SET2A();
    void SET3B();    void SET3C();    void SET3D();    void SET3E();    void SET3H();    void SET3L();  void SET3A();
    void SET4B();    void SET4C();    void SET4D();    void SET4E();    void SET4H();    void SET4L();  void SET4A();
    void SET5B();    void SET5C();    void SET5D();    void SET5E();    void SET5H();    void SET5L();  void SET5A();
    void SET6B();    void SET6C();    void SET6D();    void SET6E();    void SET6H();    void SET6L();  void SET6A();
    void SET7B();    void SET7C();    void SET7D();    void SET7E();    void SET7H();    void SET7L();  void SET7A();
    // HL addressed
    void SETHL(uint8_t bitNumber);
    void SET0HL();
    void SET1HL();
    void SET2HL();
    void SET3HL();
    void SET4HL();
    void SET5HL();
    void SET6HL();
    void SET7HL();

    //set bit to 0
    void RESR8(uint8_t bitNumber, uint8_t& reg);
    void RES0B();    void RES0C();    void RES0D();    void RES0E();    void RES0H();    void RES0L();  void RES0A();
    void RES1B();    void RES1C();    void RES1D();    void RES1E();    void RES1H();    void RES1L();  void RES1A();
    void RES2B();    void RES2C();    void RES2D();    void RES2E();    void RES2H();    void RES2L();  void RES2A();
    void RES3B();    void RES3C();    void RES3D();    void RES3E();    void RES3H();    void RES3L();  void RES3A();
    void RES4B();    void RES4C();    void RES4D();    void RES4E();    void RES4H();    void RES4L();  void RES4A();
    void RES5B();    void RES5C();    void RES5D();    void RES5E();    void RES5H();    void RES5L();  void RES5A();
    void RES6B();    void RES6C();    void RES6D();    void RES6E();    void RES6H();    void RES6L();  void RES6A();
    void RES7B();    void RES7C();    void RES7D();    void RES7E();    void RES7H();    void RES7L();  void RES7A();
    // HL addressed
    void RESHL(uint8_t RESNumber);
    void RES0HL();
    void RES1HL();
    void RES2HL();
    void RES3HL();
    void RES4HL();
    void RES5HL();
    void RES6HL();
    void RES7HL();

    







private:
    GBBus *bus = nullptr;
    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t data);
    uint16_t ReadDoublePCI();
    int remainingCycles = 0;
    bool enableIntteruptsAfterNext = false;
    bool interruptsEnabled = false;

    struct OpcodeInfo {
        void (GBCPU::* operate)() = nullptr;
    };
     
    std::vector<OpcodeInfo> opcodeLookup;
    std::vector<OpcodeInfo> bitShiftLookup;
    std::vector<std::string> nameLookup;



    //debug
    int debug_totalCycles = 0;
    CPUStateLog cpulog;
};

