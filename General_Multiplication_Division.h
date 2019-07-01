//
// Created by charl on 2019-06-29.
//

#ifndef HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_GENERAL_MULTIPLICATION_DIVISION_H
#define HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_GENERAL_MULTIPLICATION_DIVISION_H

#include "Elementary.h"
#include "Grade_School_Addition_Subtraction.h"

static int Digit=11;
char* WholeNumberMultiplication(char* number1, char* number2);
int* AddOperation(int num1[], int num2[], int ArrayLength);
char* DecimalNumberMultiplication(char* number1, char* number2);
int Compare(char* number1, char* number2);
int isSame (char* number1, char* number2);
char* Round(char* number);
char* WholeNumberDivision(char* number1, char* number2);
char* DecimalNumberDivision(char* number1, char* number2);

#endif //HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_GENERAL_MULTIPLICATION_DIVISION_H
