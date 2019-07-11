//
// Created by lenovo on 2019/7/5.
//

#ifndef RISC5_EX_HPP
#define RISC5_EX_HPP

#include "Instruction.hpp"
#include "MA.hpp"
#include <iostream>

class EX:public Instruction{
public:
    EX(){init();}

    void run();

    void pass(MA &);
};

void EX::run() {
    switch (op) {
        case LUI: { //I-type, U-immediate
            Val_Ex = imm;
            break;
        }
        case AUIPC: { //I-type, U-immediate
            Val_Ex = Val_pc + imm;
            break;
        }
        case JAL: { //U-type, J-immediate
            Val_Ex = Val_pc + 4;
            Val_pc = Val_pc + imm;
            break;
        }
        case JALR: { //I-type, I-immediate
            Val_Ex = Val_pc + 4;
            Val_pc = (Val_rs1 + imm) & 0xfffffffe;
            break;
        }
        case BEQ: { //S-type, B-immediate
            break;
        }
        case BNE: { //S-type, B-immediate
            break;
        }
        case BLT: { //S-type, B-immediate
            break;
        }
        case BGE: { //S-type, B-immediate
            break;
        }
        case BLTU: { //S-type, B-immediate
            break;
        }
        case BGEU: { //S-type, B-immediate
            break;
        }
        case LB: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LH: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LW: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LBU: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case LHU: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SB: { //S-type, S-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SH: { //S-type, S-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SW: { //S-type, S-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case ADDI: { //I-type, I-immediate
            Val_Ex = Val_rs1 + imm;
            break;
        }
        case SLTI: { //I-type, I-immediate
            if (Val_rs1 < imm)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case SLTIU: { //I-type, I-immediate
            if ((unsigned int) Val_rs1 < (unsigned int)imm)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case XORI: { //I-type, I-immediate
            Val_Ex = Val_rs1 ^ imm;
            break;
        }
        case ORI: { //I-type, I-immediate
            Val_Ex = Val_rs1 | imm;
            break;
        }
        case ANDI: { //I-type, I-immediate
            Val_Ex = Val_rs1 & imm;
            break;
        }
        case SLLI: { //R-type
            Val_Ex = (unsigned int) Val_rs1 << (unsigned int)rs2;
            break;
        }
        case SRLI: { //I-type
            Val_Ex = (unsigned int) Val_rs1 >> (unsigned int)rs2;
            break;
        }
        case SRAI: { //I-type
            Val_Ex = Val_rs1 >> (unsigned int)rs2;
            break;
        }
        case ADD: { //R-type
            Val_Ex = Val_rs1 + Val_rs2;
            break;
        }
        case SUB: { //R-type
            Val_Ex = Val_rs1 - Val_rs2;
            break;
        }
        case SLL: { //R-type
            Val_Ex = (unsigned int)Val_rs1 << (unsigned int)(Val_rs2 & 0x1f);
            break;
        }
        case SRL: { //R-type
            Val_Ex = (unsigned int) Val_rs1 >> (unsigned int)(Val_rs2 & 0x1f);
            break;
        }
        case SRA: { //R-type
            Val_Ex = Val_rs1 << (unsigned int)(Val_rs2 & 0x1f);
            break;
        }
        case SLT: { //R-type
            if (Val_rs1 < Val_rs2)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case SLTU: { //R-type
            if ((unsigned int) Val_rs1 < (unsigned int) Val_rs2)
                Val_Ex = 1;
            else Val_Ex = 0;
            break;
        }
        case XOR: { //R-type
            Val_Ex = Val_rs1 ^ Val_rs2;
            break;
        }
        case OR: { //R-type
            Val_Ex = Val_rs1 | Val_rs2;
            break;
        }
        case AND: { //R-type
            Val_Ex = Val_rs1 & Val_rs2;
            break;
        }
    }
}

void EX::pass(MA & obj) {
    obj.op = op;
    obj.inst = inst;
    obj.opcode = opcode;
    obj.rd = rd;
    obj.rs1 = rs1;
    obj.rs2 = rs2;
    obj.imm = imm;
    obj.Val_rs1 = Val_rs1;
    obj.Val_rs2 = Val_rs2;
    obj.Val_Ex = Val_Ex;
    obj.Val_Ma = Val_Ma;
    obj.Val_pc = Val_pc;

}

#endif //RISC5_EX_HPP
