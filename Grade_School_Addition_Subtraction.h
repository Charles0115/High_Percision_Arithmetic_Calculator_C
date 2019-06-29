//
// Created by charl on 2019-05-12.
//

#ifndef HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_GRADE_SCHOOL_CALCULATION_H
#define HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_GRADE_SCHOOL_CALCULATION_H

#include "Elementary.h"

static int NumberArrayLength;
static int Digit=11;
void toWholeNumber(int* (*num), char* n);	//Change the input into int array
char* WholeNumberAddition(char* number1, char* number2);	//Add two whole numbers
char* WholeDecimalAddition(char* number1, char* number2);	//Add one decimal number, one whole number
char* DecimalNumberAddition(char* number1, char* number2);	//Add two decimal numbers
char* WholeNumberSubtraction(char* number1, char* number2);	//Subtract two whole numbers
char* DecimalNumberSubtraction(char* number1, char* number2);	//Subtract two decimal numbers + one decimal number, one whole number


#endif //HIGH_PERCISION_ARITHMETIC_CALCULATOR_C_GRADE_SCHOOL_CALCULATION_H
