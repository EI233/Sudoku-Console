cmake_minimum_required(VERSION 3.23)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS -static)
add_executable(Sudoku main.c Lib/DPLL.c Lib/Load.c Lib/Menu.c Lib/Solution.c Lib/Sudoku.c Lib/Global.h)