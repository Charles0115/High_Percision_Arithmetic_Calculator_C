cmake_minimum_required(VERSION 3.13)
project(High_Percision_Arithmetic_Calculator_C C)

set(CMAKE_C_STANDARD 99)

add_executable(High_Percision_Arithmetic_Calculator_C main.c Stack.c Stack.h Queue.c Queue.h Elementary.h Grade_School_Addition_Subtraction.c Grade_School_Addition_Subtraction.h General_Multiplication_Division.c General_Multiplication_Division.h)