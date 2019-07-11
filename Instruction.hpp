//
// Created by lenovo on 2019/7/3.
//
#ifndef INSTRUCTION
#define INSTRUCTION

#include "Memory_And_Register.hpp"
#include <iostream>
enum OPERTOR {
    LUI, AUIPC, JAL,
//  0    1      2

    JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB,
//  3     4    5    6    7    8     9     10

    LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI,
//  11  12  13   14  15  16  17    18    19     20    21   22   23

    SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR,
//  24    25    26    27   28   29   30   31   32    33   34   35

    AND
//  36
};

enum status{
    NormallyRun, NotBegin, pause
//  0    1              2
};

char oper[37][8]={
        "LUI", "AUIPC", "JAL",
//  0    1      2

        "JALR", "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU", "LB",
//  3     4    5    6    7    8     9     10

        "LH", "LW", "LBU", "LHU", "SB", "SH", "SW", "ADDI", "SLTI", "SLTIU", "XORI", "ORI", "ANDI",
//  11  12  13   14  15  16  17    18    19     20    21   22   23

        "SLLI", "SRLI", "SRAI", "ADD", "SUB", "SLL", "SLT", "SLTU", "XOR", "SRL", "SRA", "OR",
//  24    25    26    27   28   29   30   31   32    33   34   35

        "AND"
//  36
};

class Instruction {
public:
    OPERTOR op;
    int inst, opcode;
    int rd, rs1, rs2;
    int imm, Val_rs1, Val_rs2, Val_Ex, Val_Ma, Val_pc;

    Instruction();

    void init();

    int signedExtend(int data, int bits) {
        if (data & (1 << bits))
            data |= 0xffffffff >> bits << bits;
        return data;
    }

    void show_information_for_debug();
    
    void show_change_rd_with_ex_for_debug();

    void show_change_rd_with_ma_for_debug();

    void show_change_ma_for_debug();
};

void Instruction::show_information_for_debug(){
//    std::cout<<"after ID: pc:"<<std::hex<<pc.data<<std::dec<<"  op:"<<oper[op]<<"  rs1:"<<rs1<<"  rs2:"<<rs2<<"  imm:"<<std::hex<<imm<<"  inst:"<<inst<<std::endl;
};

void Instruction::show_change_rd_with_ex_for_debug(){
//    std::cout<<"change RD  "<<std::dec<<rd<<" : "<<Val_Ex<<std::endl;
}

void Instruction::show_change_rd_with_ma_for_debug(){
//    std::cout<<"change RD "<<std::dec<<rd<<" : "<<Val_Ma<<std::endl;
}

void Instruction::show_change_ma_for_debug(){
//    std::cout<<"change MA"<<std::dec<<rd<<" : "<<Val_Ma<<std::endl;
}


Instruction::Instruction() {
    op = LUI;
    inst = opcode = rd = rs1 = rs2 = imm =  Val_rs1 = Val_rs2 = Val_Ex = Val_Ma = Val_pc = 0;
}

void Instruction::init() {
    op = LUI;
    inst = opcode = 0;
    rd = rs1 = rs2 = imm = 0;
}

#endif
