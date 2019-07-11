//
// Created by lenovo on 2019/7/5.
//

#ifndef RISC5_IF_HPP
#define RISC5_IF_HPP

#include "Instruction.hpp"
#include "ID.hpp"
#include <iostream>

class IF : public Instruction {
private:
    void get_rd();

    void get_rs1();

    void get_rs2();

    void get_imm_I();

    void get_imm_S();

    void get_imm_B();

    void get_imm_U();

    void get_imm_J();

    void pc_lock() { pc.lock++; }

public:
    IF() { init(); }

    void run();

    void pass(ID &);
};

void IF::get_rd() {
    rd = (inst >> 7) & 0x1F;
//    if(rd == 0) std::cout<<"no.0 register!\n";
}

void IF::get_rs1() {
    rs1 = (inst >> 15) & 0x1F;
}

void IF::get_rs2() {
    rs2 = (inst >> 20) & 0x1F;
}

void IF::get_imm_I() {
    imm = inst >> 20;
}

void IF::get_imm_S() {
    imm = ((inst >> 7) & 0x1F) + ((inst >> 25) << 5);
}

void IF::get_imm_B() {
    imm = (((inst >> 8) & 0xF) << 1) + (((inst >> 25) & 0x3F) << 5)
          + (((inst >> 7) & 0x1) << 11) + ((inst >> 31) << 12);
}

void IF::get_imm_U() {
    imm = (inst >> 12) << 12;
}

void IF::get_imm_J() {
    imm = (((inst >> 21) & 0x3FF) << 1) + (((inst >> 20) & 0x1) << 11)
          + (((inst >> 12) & 0xFF) << 12) + ((inst >> 31) << 20);
}

void IF::run() {
    inst = int((unsigned char) memory.mem[pc.data]) + int((unsigned char) memory.mem[pc.data + 1] << 8) +
           int((unsigned char) memory.mem[pc.data + 2] << 16) +
           int((unsigned char) memory.mem[pc.data + 3] << 24);
    Val_pc = pc.data;
    pc.data += 4;

    opcode = inst & 0x7F;
    switch (opcode) {
        case 55 :
            op = LUI;
            get_imm_U();
            get_rd();
            break;
        case 23 :
            op = AUIPC;
            get_imm_U();
            get_rd();
            break;
        case 111:
            op = JAL;
            get_imm_J();
            get_rd();
            pc_lock();
            break;
        case 103:
            op = JALR;
            get_imm_I();
            get_rs1();
            get_rd();
            pc_lock();
            break;
        case 99: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = BEQ;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    pc_lock();
                    break;
                case 1:
                    op = BNE;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    pc_lock();
                    break;
                case 4:
                    op = BLT;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    pc_lock();
                    break;
                case 5:
                    op = BGE;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    pc_lock();
                    break;
                case 6:
                    op = BLTU;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    pc_lock();
                    break;
                case 7:
                    op = BGEU;
                    get_rs1();
                    get_rs2();
                    get_imm_B();
                    pc_lock();
                    break;
                default:
                    break;
            }
            break;
        }
        case 3: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = LB;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 1:
                    op = LH;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 2:
                    op = LW;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 4:
                    op = LBU;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                case 6:
                    op = LHU;
                    get_rs1();
                    get_imm_I();
                    get_rd();
                    break;
                default:
                    break;
            }
            break;
        }
        case 35: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = SB;
                    get_rs1();
                    get_rs2();
                    get_imm_S();
                    break;
                case 1:
                    op = SH;
                    get_rs1();
                    get_rs2();
                    get_imm_S();
                    break;
                case 2:
                    op = SW;
                    get_rs1();
                    get_rs2();
                    get_imm_S();
                    break;
                default:
                    break;
            }
            break;
        }
        case 19: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0:
                    op = ADDI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 2:
                    op = SLTI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 3:
                    op = SLTIU;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 4:
                    op = XORI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 6:
                    op = ORI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 7:
                    op = ANDI;
                    get_rs1();
                    get_rd();
                    get_imm_I();
                    break;
                case 1:
                    op = SLLI;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 5: {
                    int option3 = (inst >> 25) & 0x7F;
                    switch (option3) {
                        case 0 :
                            op = SRLI;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        case 32:
                            op = SRAI;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 51: {
            int opcode2 = (inst >> 12) & 0x7;
            switch (opcode2) {
                case 0: {
                    int option3 = (inst >> 25) & 0x7F;
                    switch (option3) {
                        case 0 :
                            op = ADD;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        case 32:
                            op = SUB;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case 1:
                    op = SLL;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 2:
                    op = SLT;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 3:
                    op = SLTU;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 4:
                    op = XOR;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 5: {
                    int option3 = (inst >> 25) & 0x7F;
                    switch (option3) {
                        case 0 :
                            op = SRL;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        case 32:
                            op = SRA;
                            get_rs1();
                            get_rs2();
                            get_rd();
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case 6:
                    op = OR;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                case 7:
                    op = AND;
                    get_rs1();
                    get_rs2();
                    get_rd();
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    show_information_for_debug();
}

void IF::pass(ID &obj) {
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

    init();
}

#endif //RISC5_IF_HPP
