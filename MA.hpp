//
// Created by lenovo on 2019/7/5.
//

#ifndef RISC5_MA_HPP
#define RISC5_MA_HPP

#include "Instruction.hpp"
#include "WB.hpp"
#include <iostream>

class MA:public Instruction{
public:
    MA(){init();}

    void run();

    void pass(WB &);
};

void MA::run() {
    switch (op) {
        case LUI:
        case AUIPC:
        case JAL:
        case JALR:
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ORI:
        case ANDI:
        case SLLI:
        case SRLI:
        case SRAI:
        case ADD:
        case SUB:
        case SLL:
        case SRL:
        case SRA:
        case SLT:
        case SLTU:
        case XOR:
        case OR:
        case AND: {
            break;
        }

        case LB: {
            Val_Ma = int(memory.mem[Val_Ex]);
            break;
        }
        case LH: {
            Val_Ma = (unsigned char)memory.mem[Val_Ex] + int(memory.mem[Val_Ex + 1] << 8);
            break;
        }
        case LW: {
            Val_Ma = int((unsigned char)memory.mem[Val_Ex]) + int((unsigned char)memory.mem[Val_Ex + 1] << 8) +
                     int((unsigned char)memory.mem[Val_Ex + 2] << 16) + int(memory.mem[Val_Ex + 3] << 24);
            break;
        }
        case LBU: {
            Val_Ma = int((unsigned char)memory.mem[Val_Ex]);
            break;
        }
        case LHU: {
            Val_Ma = int((unsigned char)memory.mem[Val_Ex]) + int((unsigned char)memory.mem[Val_Ex + 1] << 8);
            break;
        }
        case SB: {
            memory.mem[Val_Ex] = Val_rs2 & 255;

            memory.judge_end(Val_Ex);
            break;
        }
        case SH: {
            memory.mem[Val_Ex] = Val_rs2 & 255;
            memory.mem[Val_Ex + 1] = (Val_rs2 >> 8) & 255;

            memory.judge_end(Val_Ex);
            memory.judge_end(Val_Ex + 1);
            break;
        }
        case SW: {
            memory.mem[Val_Ex] = Val_rs2 & 255 ;
            memory.mem[Val_Ex + 1] = (Val_rs2 >> 8) & 255;
            memory.mem[Val_Ex + 2] = (Val_rs2 >> 16) & 255;
            memory.mem[Val_Ex + 3] = (Val_rs2 >> 24) & 255;

            memory.judge_end(Val_Ex);
            memory.judge_end(Val_Ex + 1);
            memory.judge_end(Val_Ex + 2);
            memory.judge_end(Val_Ex + 3);
            break;
        }

    }
}

void MA::pass(WB & obj) {
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

#endif //RISC5_MA_HPP
