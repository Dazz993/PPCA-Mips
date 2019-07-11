cmake_minimum_required(VERSION 3.5.2)
project(RISC5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2")

add_executable(code main.cpp Instruction.hpp Memory_And_Register.hpp Useful_Functions.hpp ID.hpp IF.hpp EX.hpp MA.hpp WB.hpp predect_and_pc_controller.hpp)
