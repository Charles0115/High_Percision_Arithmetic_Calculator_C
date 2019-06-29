//
// Created by charl on 2019-06-29.
//

#include "Faster_Multiplication_Division.h"


char* KaratsubaAlg(char* number1, char* number2)
{
    //Since two numbers have the same length, we need a variable to indicate the length.
    int Length = strlen(number1);
    char* finalresult = malloc(2 * Length);
    if(Length < 5)
    {
        int product = atoi(number1) * atoi(number2);
        itoa(product, finalresult, 10);
        return finalresult;
    }

    int SplitLength = Length/2;

    int i;
    char* high1 = malloc(SplitLength+1);
    char* low1 = &number1[SplitLength];
    char* high2 = malloc(SplitLength+1);
    char* low2 = &number2[SplitLength];

    strncpy(high1, number1, SplitLength);
    strncpy(high2, number2, SplitLength);
    high1[SplitLength] = 0;
    high2[SplitLength] = 0;

    char* product1 = KaratsubaAlg(low1, low2);
    char* product2 = KaratsubaAlg(WholeNumberAddition(low1, high1), WholeNumberAddition(low2, high2));
    char* product3 = KaratsubaAlg(high1, high2);

    char* temp1 = strdup(product3);
    for(i=0; i<2*(Length-SplitLength); i++)
        strcat(temp1, "0");
    char* temp2 = WholeNumberAddition(temp1, product1);
    char* temp3 = WholeNumberAddition(product1, product3);
    char* temp4 = WholeNumberSubtraction(product2, temp3);
    for(i=0; i<Length-SplitLength; i++)
        strcat(temp4, "0");
    finalresult = WholeNumberAddition(temp4, temp2);

    free(high1);
    free(high2);
    free(product1);
    free(product2);
    free(product3);
    free(temp1);
    free(temp2);
    free(temp3);
    free(temp4);

    return finalresult;
}



char* WholeNumberMultiplication(char* number1, char* number2)
{
    //First we need to check if two numbers have useless 0s at the front (again, people are mean...)
    //We don't have to in addition and subtraction but we do need this in multiplication and division; the algorithm depends on the true length of two inputs
    int i, length1 = strlen(number1), length2 = strlen(number2);
    for (i = 0; i < length1; i++)
    {
        if (number1[i] != '0')
        {
            number1 = &number1[i];	//This is like string.substring(i) in java
            break;
        }
    }
    if (i == length1)	//If the result is just 0, we can immediately return 0 because anything times 0 is 0
    {
        return "0";
    }

    //do the same thing for number2
    for (i = 0; i < length2; i++)
    {
        if (number2[i] != '0')
        {
            number2 = &number2[i];	//This is like string.substring(i) in java
            break;
        }
    }
    if (i == length2)	//If the result is just 0, return 0
    {
        return "0";
    }

    //To do the algorithm, we need two numbers to have the same number of digits.
    //thus, we add 0s at the front to the smaller number
    char* Number1;
    char* Number2;
    if(strlen(number1) > strlen(number2))
    {
        Number1 = strdup(number1);
        Number2 = malloc(strlen(number1));
        for(i = 0; i < strlen(number1) - strlen(number2); i++)
        {
            strcat(Number2, "0");
        }
        strcat(Number2, number2);
    }
    else if(strlen(number1) < strlen(number2))
    {
        Number2 = strdup(number2);
        Number1 = malloc(strlen(number2));
        for(i = 0; i < strlen(number2) - strlen(number1); i++)
        {
            strcat(Number1, "0");
        }
        strcat(Number1, number1);
    }
        //If they have the same length, we just pass values to Number1 and Number2
    else
    {
        Number1 = strdup(number1);
        Number2 = strdup(number2);
    }

    //Applies Karatsuba Algorithm
    char* finalresult = KaratsubaAlg(Number1, Number2);
    return finalresult;
}



/*
 * Same as subtraction, this function combines DecimalWholeMultiplication and DecimalNumberMultiplication.
 * Similar idea: We remove the decimal first and do the WholeNumberMultiplication, then we put the decimal back
 */
char* DecimalNumberMultiplication(char* number1, char* number2)
{
    //First, we assume that both numbers have decimal numbers
    char* WholeNum1 = NULL;
    char* DecimalNum1 = NULL;
    char* WholeNum2 = NULL;
    char* DecimalNum2 = NULL;
    char* Number1 = strdup(number1);    //Make a copy of the inputs Really Important!
    char* Number2 = strdup(number2);
    WholeNum1 = strtok(Number1, ".");
    DecimalNum1 = strtok(NULL, ".");
    WholeNum2 = strtok(Number2, ".");
    DecimalNum2 = strtok(NULL, ".");

    int i;
    char* Decimal_Whole1 = NULL;
    char* Decimal_Whole2 = NULL;
    int DecimalDigit;
    char* finalresult = NULL;

    if(DecimalNum1==NULL && DecimalNum2!=NULL)  //If the first number is whole number and another is decimal number
    {
        Decimal_Whole1 = strdup(WholeNum1);
        Decimal_Whole2 = malloc(strlen(WholeNum2)+strlen(DecimalNum2));
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);
        DecimalDigit = strlen(DecimalNum2);
    }
    else if(DecimalNum1!=NULL && DecimalNum2==NULL) //If the first number is decimal number and another is whole number
    {
        Decimal_Whole2 = strdup(WholeNum2);
        Decimal_Whole1 = malloc(strlen(WholeNum1)+strlen(DecimalNum1));
        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);
        DecimalDigit = strlen(DecimalNum1);
    }
    else    //If both numbers are decimal numbers
    {
        Decimal_Whole1 = malloc(strlen(WholeNum1)+strlen(DecimalNum1));
        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);
        Decimal_Whole2 = malloc(strlen(WholeNum2)+strlen(DecimalNum2));
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);
        DecimalDigit = strlen(DecimalNum1) + strlen(DecimalNum2);
    }

    char* Product = WholeNumberMultiplication(Decimal_Whole1, Decimal_Whole2);  //This is the answer without decimal

    if(strcmp(Product, "0") == 0)   //Check if the answer is 0
        return "0";

    //If the answer is bigger than 1
    if(strlen(Product) > DecimalDigit)
    {
        finalresult = malloc(strlen(Product)+1);
        for (i = 0; i < strlen(Product) - DecimalDigit; i++)
            finalresult[i] = Product[i];
        finalresult[i++] = '.';

        while (Product[i - 1] != '\0')
        {
            finalresult[i] = Product[i - 1];
            i++;
        }
        finalresult[i] = '\0';
    }
        //If the answer is less than 1 but greater than 0.1
    else if(strlen(Product) == DecimalDigit)
    {
        //It has to be 0. something
        finalresult = malloc(strlen(Product)+2);
        strcpy(finalresult, "0.");
        strcat(finalresult, Product);

        //Check if there are any useless 0s at the end
        for(i=strlen(finalresult)-1; i>=0; i--)
        {
            if(finalresult[i] != '0')
            {
                finalresult[i+1] = '\0';
                break;
            }
        }
        free(Number1);
        free(Number2);
        free(Product);
        free(Decimal_Whole1);
        free(Decimal_Whole2);
        return finalresult;
    }
    else
    {
        char* TempResult = malloc(strlen(Product) + DecimalDigit);
        for(i=0; i<DecimalDigit; i++)
            TempResult[i] = '0';
        TempResult[i] = '\0';
        strcat(TempResult, Product);

        finalresult = malloc(strlen(TempResult)+1);
        for (i = 0; i < strlen(TempResult) - DecimalDigit; i++)
            finalresult[i] = TempResult[i];
        finalresult[i++] = '.';

        while (TempResult[i - 1] != '\0')
        {
            finalresult[i] = TempResult[i - 1];
            i++;
        }
        finalresult[i] = '\0';
        free(TempResult);

        i=0;
        while(finalresult[i]=='0')
            i++;

        finalresult = &finalresult[i];
        char* Temp = strdup(finalresult);
        strcpy(finalresult, "0");
        strcat(finalresult, Temp);
        free(Temp);
    }

    for(i=strlen(finalresult)-1; i>=0; i--)
    {
        if(finalresult[i] != '0')
        {
            finalresult[i+1] = '\0';
            if(finalresult[i] == '.')
                finalresult[i] = '\0';
            break;
        }
    }

    free(Number1);
    free(Number2);
    free(Product);
    free(Decimal_Whole1);
    free(Decimal_Whole2);
    return finalresult;
}