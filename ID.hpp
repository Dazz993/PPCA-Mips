//
// Created by lenovo on 2019/7/5.
//

#ifndef RISC5_ID_HPP
#define RISC5_ID_HPP

#include "Instruction.hpp"
#include "EX.hpp"
#include <iostream>

class ID : public Instruction{
private:
    void get_Val_rs1(EX &ex, WB &wb);

    void get_Val_rs2(EX &ex, WB &wb);

public:
    bool stall_flag;

    ID(){init(); stall_flag = false;}

    void run(EX &ex, WB &wb);

    void pass(EX &);
};

void ID::get_Val_rs1(EX &ex, WB &wb) {
    int rd_EX = ex.rd, rd_WB = wb.rd;
    if(rs1 == 0){
        Val_rs1 = 0;
        return;
    } else if(rd_EX == rs1 && (ex.op != LB && ex.op != LH && ex.op != LW && ex.op != LBU && ex.op != LHU)){
        Val_rs1 = ex.Val_Ex;
    } else if(rd_EX == rs1 && (ex.op == LB || ex.op == LH || ex.op == LW || ex.op == LBU || ex.op == LHU)){
        //stall one time
        stall_flag = true;
    } else if(rd_WB == rs1 && (wb.op == LB || wb.op == LH || wb.op == LW || wb.op == LBU || wb.op == LHU)) {
        Val_rs1 = wb.Val_Ma;
    } else if(rd_WB == rs1 && (wb.op != LB && wb.op != LH && wb.op != LW && wb.op != LBU && wb.op != LHU)) {
        Val_rs1 = wb.Val_Ex;
    } else {
        Val_rs1 = r[rs1].data;
    }
}

void ID::get_Val_rs2(EX &ex, WB &wb) {
    int rd_EX = ex.rd, rd_WB = wb.rd;
    if(rs2 == 0){
        Val_rs2 = 0;
        return;
    } else if(rd_EX == rs2 && (ex.op != LB && ex.op != LH && ex.op != LW && ex.op != LBU && ex.op != LHU)){
        Val_rs2 = ex.Val_Ex;
    } else if(rd_EX == rs2 && (ex.op == LB || ex.op == LH || ex.op == LW || ex.op == LBU || ex.op == LHU)){
        //stall one time
        stall_flag = true;
    } else if(rd_WB == rs2 && (wb.op == LB || wb.op == LH || wb.op == LW || wb.op == LBU || wb.op == LHU)) {
        Val_rs2 = wb.Val_Ma;
    } else if(rd_WB == rs2 && (wb.op != LB && wb.op != LH && wb.op != LW && wb.op != LBU && wb.op != LHU)) {
        Val_rs2 = wb.Val_Ex;
    } else {
        Val_rs2 = r[rs2].data;
    }
}

void ID::run(EX &ex, WB &wb){
    stall_flag = false;

    switch (op) {
        case JALR:
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:
        case ADDI:
        case SLTI:
        case SLTIU:
        case XORI:
        case ORI:
        case ANDI:
        case SLLI:
        case SRLI:
        case SRAI:
            get_Val_rs1(ex, wb);
            break;

        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
        case SB:
        case SH:
        case SW:
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
            get_Val_rs1(ex, wb);
            get_Val_rs2(ex, wb);
            break;
        default: break;
    }
    show_information_for_debug();
}

void ID::pass(EX & obj) {
    if(!stall_flag) {
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
    } else { // stall
        ID tmp0;
        tmp0.pass(obj);
    }
}

#endif //RISC5_ID_HPP
