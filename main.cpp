#include <iostream>
#include "Instruction.hpp"
#include "IF.hpp"
#include "ID.hpp"
#include "EX.hpp"
#include "MA.hpp"
#include "WB.hpp"
#include "predect_and_pc_controller.hpp"

IF _IF;
ID _ID;
EX _EX;
MA _MA;
WB _WB;
Predict _predict;

void serial_run();
void parallel_run();

int cnt = 0;

int main() {
    memory.Load_Memory();


    while(memory.end == 0){
//        serial_run();

//        if(cnt==92)
//        {
//            std::cout<<"yes"<<std::endl;
//        }

        parallel_run();
        //////////////////////////debug//////////////////////////
//        std::cout<<std::dec<<"after run: cnt:"<<++cnt<<"  pc:"<<pc.data<<"  op:"<<_WB.op<<std::endl;
//        std::cout<<"------"<<std::endl;
//        for(int i = 0; i < 32; i++) std::cout<<r[i].data<<"  ";
//        std::cout<<std::endl;
//        std::cout<<"--------------------------"<<std::endl;
//        if(cnt > 200)break;
    }
    std::cout<<((r[10].data & 0xff) % 253)<<std::endl;
//    std::cout<<_predict.right_cnt/(double)_predict.cnt*100<<"%"<<std::endl;
    return 0;
}

void serial_run(){
    _IF.run();
    _IF.pass(_ID);
    _ID.run(_EX, _WB);
    _ID.pass(_EX);
    _EX.run();
    _EX.pass(_MA);
    _MA.run();
    _MA.pass(_WB);
    _WB.run();
}

void parallel_run(){

    cnt++;
//    std::cout<<"------------------------------------------------------"<<std::endl;
//
//    if(cnt == 121)
//    {
//        std::cout<<"here"<<std::endl;
//    }
    _WB.run();
//    std::cout<<"time:"<<std::dec<<cnt<<"  WB: pc:"<<std::hex<<pc.data<<"  pc.lock:"<<pc.lock<<std::dec<<"  op:"<<oper[_WB.op]<<"  rs1:"<<_WB.rs1<<"  rs2:"<<_WB.rs2<<"  rd:"<<_WB.rd<<"  imm:"<<std::hex<<_WB.imm<<"  Val_rs1:"<<_WB.Val_rs1<<"  Val_rs2:"<<_WB.Val_rs2<<std::endl;

    _MA.run();
//    std::cout<<"time:"<<std::dec<<cnt<<"  MA: pc:"<<std::hex<<pc.data<<"  pc.lock:"<<pc.lock<<std::dec<<"  op:"<<oper[_MA.op]<<"  rs1:"<<_MA.rs1<<"  rs2:"<<_MA.rs2<<"  rd:"<<_MA.rd<<"  imm:"<<std::hex<<_MA.imm<<"  Val_rs1:"<<_MA.Val_rs1<<"  Val_rs2:"<<_MA.Val_rs2<<std::endl;
    _MA.pass(_WB);


    _EX.run();
    _predict.EX_judge(_EX);
//    std::cout<<"time:"<<std::dec<<cnt<<"  EX: pc:"<<std::hex<<pc.data<<"  pc.lock:"<<pc.lock<<std::dec<<"  op:"<<oper[_EX.op]<<"  rs1:"<<_EX.rs1<<"  rs2:"<<_EX.rs2<<"  rd:"<<_EX.rd<<"  imm:"<<std::hex<<_EX.imm<<"  Val_rs1:"<<_EX.Val_rs1<<"  Val_rs2:"<<_EX.Val_rs2<<"  Val_EX:"<<_EX.Val_Ex<<std::endl;
    _EX.pass(_MA);


    _ID.run(_EX, _WB);
    if(_predict.pcUpdate == -1) _predict.ID_predict(_ID);
    else _ID.init();
//    std::cout<<"time:"<<std::dec<<cnt<<"  ID: pc:"<<std::hex<<pc.data<<"  pc.lock:"<<pc.lock<<std::dec<<"  op:"<<oper[_ID.op]<<"  rs1:"<<_ID.rs1<<"  rs2:"<<_ID.rs2<<"  rd:"<<_ID.rd<<"  imm:"<<std::hex<<_ID.imm<<"  Val_rs1:"<<_ID.Val_rs1<<"  Val_rs2:"<<_ID.Val_rs2<<std::endl;
    _ID.pass(_EX);


    if(_predict.pcUpdate != -1) {
        pc = _predict.pcUpdate;
        _predict.init();
    }
    if(!_ID.stall_flag) _IF.run();
//    std::cout<<"time:"<<std::dec<<cnt<<"  IF: pc:"<<std::hex<<pc.data<<"  pc.lock:"<<pc.lock<<std::dec<<"  op:"<<oper[_IF.op]<<"  rs1:"<<_IF.rs1<<"  rs2:"<<_IF.rs2<<"  rd:"<<_IF.rd<<"  imm:"<<std::hex<<_IF.imm<<"  Val_rs1:"<<_IF.Val_rs1<<"  Val_rs2:"<<_IF.Val_rs2<<std::endl;
    if(!_ID.stall_flag) _IF.pass(_ID);

//    std::cout<<"----------------------"<<std::endl;
//
//    for(int i = 0; i < 32; i++){
//        std::cout<<i<<":("<<std::dec<<r[i].data<<","<<r[i].lock<<"), ";
//    }
//    std::cout<<std::endl;
//    std::cout<<"------------------------------------------------------"<<std::endl;
}