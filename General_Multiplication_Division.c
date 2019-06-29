//
// Created by charl on 2019-06-29.
//

#include "General_Multiplication_Division.h"
/*
 *This is the grade school Multiplication method
 * This method is more complex than addition and subtraction, but we don't have to deal with sign.
 * The idea is to identify which number is bigger first; then we create an 2 dimensional array; we add up each result
 */
char* WholeNumberMultiplication(char* number1, char* number2)
{
    int NumberofColumn = 0; //This is the number of columns the 2 dimensional array should have
    //It's determined by the length of the smaller number
    //Create two variables for comparing (you don't have to)
    char* Number1 = NULL;   //Contains bigger number
    char* Number2 = NULL;   //Contains smaller number
    int i, j;   //counting variables

    //First we need to check if two numbers have useless 0s at the front (again, people are mean...)
    //We don't have to in addition and subtraction but we do need this in multiplication and division; the algorithm depends on the true length of two inputs
    for(i=0; i<strlen(number1); i++)
    {
        if(number1[i] != '0')
        {
            number1 = &number1[i];
            break;
        }
    }
    for(i=0; i<strlen(number2); i++)
    {
        if(number2[i] != '0')
        {
            number2 = &number2[i];
            break;
        }
    }

    //Now we identify the bigger number by comparing the length of two numbers
    if(strlen(number1) >= strlen(number2))
    {
        //This is the reason why we do this, the NumberArrayLength is the length of bigger number and the column is the length of smaller number
        NumberArrayLength = strlen(number1);
        NumberofColumn = strlen(number2);
        Number1 = number1;
        Number2 = number2;
    }
    else
    {
        NumberArrayLength = strlen(number2);
        NumberofColumn = strlen(number1);
        Number2 = number1;
        Number1 = number2;
    }

    int* num1 = NULL;
    int* num2 = NULL;
    toWholeNumber(&num1, Number1);
    toWholeNumber(&num2, Number2);

    int MaxLength = strlen(Number1) + strlen(Number2);  //Th width of the 2 dimensional array
    int **ProductResult = (int **) malloc(NumberofColumn * sizeof(int *));  //This is the 2 dimensional array
    for(i=0; i<NumberofColumn; i++)     //Initialize elements to 0
    {
        ProductResult[i] = (int*)malloc(MaxLength * sizeof(int));
        memset(ProductResult[i], 0, MaxLength*sizeof(int));
    }

    //Multiplication calculation I'm sure you don't have interest on that
    int digit = 0;
    int carry = 0;
    int temp = 0;
    int power_of_ten = 0;
    int k = 0, l = 1;
    int* WholeSum = malloc(MaxLength* sizeof(int));
    memset(WholeSum, 0, MaxLength* sizeof(int));

    for(i=NumberArrayLength-1; i>=NumberArrayLength-NumberofColumn; i--)
    {
        for(j=NumberArrayLength-1; j>=0; j--)
        {
            digit = num2[i] * num1[j];
            if(ProductResult[k][MaxLength-power_of_ten-l] + digit >= 10)
            {
                temp = ProductResult[k][MaxLength-power_of_ten-l];
                ProductResult[k][MaxLength-power_of_ten-l] = (temp + digit) % 10;
                carry = (temp + digit) / 10;
                l++;
                ProductResult[k][MaxLength-power_of_ten-l] = carry;
            }
            else
            {
                ProductResult[k][MaxLength-power_of_ten-l] += digit;
                l++;
            }
        }

        WholeSum = AddOperation(ProductResult[k], WholeSum, MaxLength);

        l = 1;
        k++;
        power_of_ten++;
    }

    char* finalresult= malloc(MaxLength+1);     //now we create finalresult to contain the answer
    for(i=0; i<MaxLength; i++)
        finalresult[i] = WholeSum[i]+48;    //Be aware of this
    finalresult[i] = '\0';      //And this

    for(i=0; i<strlen(finalresult); i++)    //Now we check if there is any useless 0s in the front
    {
        if(finalresult[i] != '0')
        {
            finalresult = &finalresult[i];
            break;
        }
    }
    if(i == strlen(finalresult))    //If it's just 0, print 0
        finalresult = "0";

    //finally we free all the pointers
    for(i=0; i<NumberofColumn; i++)
        free(ProductResult[i]);
    free(ProductResult);
    free(num1);
    free(num2);
    free(WholeSum);

    return finalresult;
}

/*
 * This is a simple addition method for multiplication only.
 */
int* AddOperation(int* num1, int* num2, int ArrayLength)
{
    int* finalresult = malloc(ArrayLength * sizeof(int));
    int* temp = malloc(ArrayLength * sizeof(int));
    int i;
    for(i=0; i<ArrayLength; i++)
    {
        temp[i] = num1[i];
    }
    int carry = 0;
    int digit =0;
    for(i=ArrayLength-1; i>0; i--)
    {
        digit = temp[i] + num2[i];
        finalresult[i] = digit % 10;
        carry = digit / 10;
        temp[i-1] = temp[i-1] + carry;
    }

    digit = temp[0] + num2[0];
    finalresult[0] = digit;
    free(temp);
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



int Compare(char* number1, char* number2)
{
    if(strlen(number1) > strlen(number2))
        return 1;
    else if(strlen(number1) < strlen(number2))
        return 0;
    else
    {
        int i;
        for(i=0; i<strlen(number1); i++)
        {
            if(number1[i] > number2[i])
                return 1;
            else if(number1[i] < number2[i])
                return 0;
        }
        return 1;
    }
}

int isSame (char* number1, char* number2)
{
    if(strlen(number1) == strlen(number2))
    {
        int i;
        for(i=0; i<strlen(number1); i++)
        {
            if(number1[i] != number2[i])
                return 0;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}



char* WholeNumberDivision(char* number1, char* number2)
{
    int i, j;
    int x = strlen(number1);
    int y = strlen(number2);
    for(j=0; j<strlen(number1); j++)
    {
        if(number1[j] != '0')
        {
            number1 = &number1[j];
            break;
        }
    }
    if(j==x)
        return "0";

    for(j=0; j<strlen(number2); j++)
    {
        if(number2[j] != '0')
        {
            number2 = &number2[j];
            break;
        }
    }
    if(j==y)
    {
        printf("The denominator is 0!! Program Ends.\n");
        exit(EXIT_FAILURE);
    }

    if(isSame(number1, number2) == 1)
        return "1";

    int isZero=0;
    int DecimalDigit;
    if(strlen(number1) >= strlen(number2))
        DecimalDigit = Digit;  // +1
    else
        DecimalDigit = Digit + strlen(number2) - strlen(number1);   //+1

    char* result = malloc(strlen(number1)+DecimalDigit);     //something//
    char* finalresult = NULL;
    char* TempNumber1 = malloc(strlen(number1)+DecimalDigit);
    char* TempNumber2 = NULL;
    char* TempSum = NULL;
    char* Temp = NULL;
    char SingleDigit[2] = {'\0', '\0'};
    strcpy(TempNumber1, number1);
    strcpy(result, "");

    for(i=0; i<DecimalDigit; i++)
        strcat(TempNumber1, "0");

    int DigitDifference = strlen(TempNumber1) - strlen(number2);
    TempSum = malloc(strlen(number2)+DigitDifference);
    TempNumber2 = malloc(strlen(number2)+DigitDifference);
    strcpy(TempNumber2, number2);   //soemthing//

    while(Compare(TempNumber1, number2))
    {
        if(isZero == 1)
            break;
        NumberArrayLength = strlen(TempNumber1);
        strcpy(TempNumber2, number2);
        for(i=0; i<DigitDifference; i++)
            strcat(TempNumber2, "0");

        while(!Compare(TempNumber1, TempNumber2))
        {
            strcat(result, "0");
            DigitDifference--;
            strcpy(TempNumber2, number2);
            for(i=0; i<DigitDifference; i++)
                strcat(TempNumber2, "0");
        }

        strcpy(TempSum, TempNumber2);
        i=1;
        while(i<10)
        {
            Temp = WholeNumberAddition(TempSum, TempNumber2);
            strcpy(TempSum, Temp);
            if(Compare(TempNumber1, TempSum))
                i++;
            else
                break;
        }

        SingleDigit[0] = (char)(i + 48);
        strcat(result, SingleDigit);

        Temp = WholeNumberSubtraction(TempSum, TempNumber2);
        strcpy(TempSum, Temp);

        Temp = WholeNumberSubtraction(TempNumber1, TempSum);
        strcpy(TempNumber1, Temp);
        if(strcmp(TempNumber1, "0") == 0)
        {
            for(j=0; j<DigitDifference; j++)
                strcat(result, "0");
            isZero = 1;
        }
        DigitDifference--;
    }


    int length = strlen(TempNumber2);
    while((length > strlen(number2)) && isZero==0)
    {
        SingleDigit[0] = '0';
        strcat(result, SingleDigit);
        length--;
    }




    if(isZero==0)
    {
        if(result[strlen(result)-1] < '5')
            result[strlen(result)-1] = '0';
        else
        {
            result[strlen(result)-1] = '0';
            Temp = Round(result);
            strcpy(result, Temp);
        }
    }




    if(strlen(number1) >= strlen(number2))
    {
        finalresult = malloc(strlen(result)+1);
        for (i = 0; i < strlen(result) - DecimalDigit; i++)     //for (i = 0; i < strlen(result) - DecimalDigit + 1; i++)
            finalresult[i] = result[i];
        finalresult[i++] = '.';

        while (result[i - 1] != '\0')
        {
            finalresult[i] = result[i - 1];
            i++;
        }
        finalresult[i] = '\0';

        if(finalresult[0]=='0' && finalresult[1] != '.')
            finalresult = &finalresult[1];

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
    }
    else
    {
        char* TempResult = malloc(strlen(result) + DecimalDigit);
        for(i=0; i<DecimalDigit; i++)
            TempResult[i] = '0';
        TempResult[i] = '\0';
        strcat(TempResult, result);

        TempResult[strlen(TempResult)-DecimalDigit-1] = '.';
        finalresult = strdup(TempResult);
        free(TempResult);

        i=0;
        while(finalresult[i] != '.')
            i++;
        finalresult = &finalresult[i-1];

        for(i=strlen(finalresult)-1; i>=0; i--)
        {
            if(finalresult[i] != '0')
            {
                finalresult[i+1] = '\0';
                break;
            }
        }
    }
    // free(result);
    //         free(TempNumber1);
    //         free(TempNumber2);
    //         free(TempSum);
    //free(Temp);   //don't know why this is the issue
    return finalresult;
}


char* DecimalNumberDivision(char* number1, char* number2)
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
    char* finalresult = NULL;

    if(DecimalNum1==NULL && DecimalNum2!=NULL)  //If the first number is whole number and another is decimal number
    {
        Decimal_Whole1 = strdup(WholeNum1);
        Decimal_Whole2 = malloc(strlen(WholeNum2)+strlen(DecimalNum2));
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);

        for(i=0; i<strlen(DecimalNum2); i++)
            strcat(Decimal_Whole1, "0");
    }
    else if(DecimalNum1!=NULL && DecimalNum2==NULL) //If the first number is decimal number and another is whole number
    {
        Decimal_Whole2 = strdup(WholeNum2);
        Decimal_Whole1 = malloc(strlen(WholeNum1)+strlen(DecimalNum1));
        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);

        for(i=0; i<strlen(DecimalNum1); i++)
            strcat(Decimal_Whole2, "0");
    }
    else    //If both numbers are decimal numbers
    {
        Decimal_Whole1 = malloc(strlen(WholeNum1)+strlen(DecimalNum1));
        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);
        Decimal_Whole2 = malloc(strlen(WholeNum2)+strlen(DecimalNum2));
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);

        if(strlen(DecimalNum1) >= strlen(DecimalNum2))
        {
            for(i=0; i<strlen(DecimalNum1) - strlen(DecimalNum2); i++)
                strcat(Decimal_Whole2, "0");
        }
        else
        {
            for(i=0; i<strlen(DecimalNum2) - strlen(DecimalNum1); i++)
                strcat(Decimal_Whole1, "0");
        }

    }

    finalresult = WholeNumberDivision(Decimal_Whole1, Decimal_Whole2);

    free(Number1);
    free(Number2);
    free(Decimal_Whole1);
    free(Decimal_Whole2);
    return finalresult;
}



char* Round(char* number)
{
    int i = strlen(number)-2;
    number[i] = (char)(number[i] + 1);
    while(number[i] == ':')
    {
        number[i] = '0';
        i--;
        number[i] = (char)(number[i] + 1);
    }
    return number;
}