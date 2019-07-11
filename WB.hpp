//
// Created by lenovo on 2019/7/5.
//

#ifndef RISC5_WB_HPP
#define RISC5_WB_HPP

#include "Instruction.hpp"
#include <iostream>

class WB:public Instruction{
public:
    WB(){init();}

    void run();
};

void WB::run() {
    switch (op) {

        //only change r[rd] by ex
        case LUI:
        case AUIPC:
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
        case AND:
            if(rd != 0){
                r[rd] = Val_Ex;
                r[rd].lock--;
                show_change_rd_with_ex_for_debug();
            }
            break;

            //only change pc by ex
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
            pc.lock--;
            break;

            //change r[rd] and pc by ex
        case JAL:
        case JALR:
            if(rd != 0) {
                r[rd] = Val_Ex;
                r[rd].lock--;
                show_change_rd_with_ex_for_debug();
            }
            break;

            //change r[rd] by ma
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:
            if(rd != 0) {
                r[rd] = Val_Ma;
                r[rd].lock--;
                show_change_rd_with_ma_for_debug();
            }
            break;

            //not change register
        case SB:
        case SH:
        case SW:
            break;
    }
}
#endif //RISC5_WB_HPP
