//
// Created by lenovo on 2019/7/10.
//

#ifndef RISC5_PRIDICT_AND_PC_CONTROLLER_HPP
#define RISC5_PRIDICT_AND_PC_CONTROLLER_HPP

#include "ID.hpp"
#include "Memory_And_Register.hpp"

class Predict{
public:
    int pcUpdate;

    int cnt, right_cnt;

    int history[6];

    Predict();

    void init();

    void ID_predict(ID &id);

    void EX_judge(EX &ex);
};

Predict::Predict() {
    init();
    cnt = right_cnt = 0;
    for(int i = 0; i < 6; i++){
        history[i] = 0;
    }
}

void Predict::init() {
    pcUpdate = -1;
}

void Predict::ID_predict(ID &id) {
    init();

    switch (id.op){
        case JAL:
            pcUpdate = id.Val_pc + id.imm;
            break;
        case JALR:
            pcUpdate = (id.Val_rs1 + id.imm) & 0xfffffffe;
            break;
        case BEQ:  // 0
            if(history[0] >= 0) pcUpdate = id.Val_pc + id.imm;
            break;
        case BNE:  // 1
            if(history[1] >= 0) pcUpdate = id.Val_pc + id.imm;
            break;
        case BLT:  // 2
            if(history[2] >= 0) pcUpdate = id.Val_pc + id.imm;
            break;
        case BGE:  // 3
            if(history[3] >= 0) pcUpdate = id.Val_pc + id.imm;
            break;
        case BLTU: // 4
            if(history[4] >= 0) pcUpdate = id.Val_pc + id.imm;
            break;
        case BGEU: // 5
            if(history[5] >= 0) pcUpdate = id.Val_pc + id.imm;
            break;
        default: break;
    }
}

void Predict::EX_judge(EX &ex) {
    init();

    switch (ex.op){
        case BEQ:  // 0
            cnt++;
            if(ex.Val_rs1 == ex.Val_rs2){ //jump
                if(history[0] >= 0) { //predict right
                    right_cnt++;
                } else { //predict wrong
                    pcUpdate = ex.Val_pc + ex.imm;
                }
                history[0]++;
            } else {
                if(history[0] >= 0) { //predict wrong
                    pcUpdate = ex.Val_pc + 4;
                } else { //predict right
                    right_cnt++;
                }
                history[0]--;
            }
            break;
        case BNE:  // 1
            cnt++;
            if(ex.Val_rs1 != ex.Val_rs2){ //it should jump
                if(history[1] >= 0) { //predict right
                    right_cnt++;
                } else { //predict wrong
                    pcUpdate = ex.Val_pc + ex.imm;
                }
                history[1]++;
            } else {
                if(history[1] >= 0) { //predict wrong
                    pcUpdate = ex.Val_pc + 4;
                } else { //predict right
                    right_cnt++;
                }
                history[1]--;
            }
            break;
        case BLT:  // 2
            cnt++;
            if(ex.Val_rs1 < ex.Val_rs2){ //jump
                if(history[2] >= 0) { //predict right
                    right_cnt++;
                } else { //predict wrong
                    pcUpdate = ex.Val_pc + ex.imm;
                }
                history[2]++;
            } else {
                if(history[2] >= 0) { //predict wrong
                    pcUpdate = ex.Val_pc + 4;
                } else { //predict right
                    right_cnt++;
                }
                history[2]--;
            }
            break;
        case BGE:  // 3
            cnt++;
            if(ex.Val_rs1 >= ex.Val_rs2){ //jump
                if(history[3] >= 0) { //predict right
                    right_cnt++;
                } else { //predict wrong
                    pcUpdate = ex.Val_pc + ex.imm;
                }
                history[3]++;
            } else {
                if(history[3] >= 0) { //predict wrong
                    pcUpdate = ex.Val_pc + 4;
                } else { //predict right
                    right_cnt++;
                }
                history[3]--;
            }
            break;
        case BLTU: // 4
            cnt++;
            if((unsigned int)ex.Val_rs1 < (unsigned int)ex.Val_rs2){ //jump
                if(history[4] >= 0) { //predict right
                    right_cnt++;
                } else { //predict wrong
                    pcUpdate = ex.Val_pc + ex.imm;
                }
                history[4]++;
            } else {
                if(history[4] >= 0) { //predict wrong
                    pcUpdate = ex.Val_pc + 4;
                } else { //predict right
                    right_cnt++;
                }
                history[4]--;
            }
            break;
        case BGEU: // 5
            cnt++;
            if((unsigned int)ex.Val_rs1 >= (unsigned int)ex.Val_rs2){ //jump
                if(history[5] >= 0) { //predict right
                    right_cnt++;
                } else { //predict wrong
                    pcUpdate = ex.Val_pc + ex.imm;
                }
                history[5]++;
            } else {
                if(history[5] >= 0) { //predict wrong
                    pcUpdate = ex.Val_pc + 4;
                } else { //predict right
                    right_cnt++;
                }
                history[5]--;
            }
            break;
        default: break;
    }
}
#endif //RISC5_PRIDICT_AND_PC_CONTROLLER_HPP
