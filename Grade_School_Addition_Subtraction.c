//
// Created by charl on 2019-05-12.
//

#include "Grade_School_Addition_Subtraction.h"

/*
 * This function changes the input from char array to int array
 * Notice that the output is void, and the input is int* (*num), we are passing the reference of the pointer
 * By doing this can we only free the variable once
 */
void toWholeNumber(int* (*num), char* n)
{
    *num = malloc(NumberArrayLength * sizeof(int));

    int i;
    int j = 0;

    for (i = 0; i < NumberArrayLength-strlen(n); i++)
    {
        (*num)[i] = 0;	//Again, num is the reference, *num is the int pointer
    }
    while (i < NumberArrayLength)
    {
        (*num)[i] = n[j] - 48;
        i++;
        j++;
    }
}

/*
 *This is the Grade School Addition Function
 *Notice: all of the calculation function has no output; all of them are call by reference ie. char*(*finalresult)
 */
char* WholeNumberAddition(char* number1, char* number2)
{
    int i, length1 = strlen(number1), length2 = strlen(number2);
    //Sometimes there are useless 0s at the front, we need to clear them
    //Simply keep the digits after the last digit of 0s
    for (i = 0; i < length1; i++)
    {
        if (number1[i] != '0')
        {
            number1 = &number1[i];	//This is like string.substring(i) in java
            break;
        }
    }
    if (i == length1)	//If the result is just 0, we change the number1 to 0 as well
    {
        number1 = "0";
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
    if (i == length2)	//If the result is just 0, we change the *finalresult to 0 as well
    {
        number2 = "0";
    }

    //NumberArrayLength is determined by the length of the bigger input
    NumberArrayLength = strlen(number1) >= strlen(number2)? strlen(number1): strlen(number2);

    //Initialize 2 int arrays and set each of them to each number (input)
    int* num1 = NULL;
    int* num2 = NULL;
    toWholeNumber(&num1, number1);
    toWholeNumber(&num2, number2);

    //Create some dynamic arrays
    int* result = malloc((NumberArrayLength + 1) * sizeof(int));		//reason for NumberArrayLength + 1 is because 789+789=1578
    char* finalresult = malloc(NumberArrayLength + 2);	//reason NumberArrayLength + 2 is because of '\0' at the last

    int carry = 0;
    int digit = 0;
    //Grad school addition part (the boring part)
    for (i = NumberArrayLength - 1; i > 0; i--)
    {
        digit = num1[i] + num2[i];
        result[i + 1] = digit % 10;
        carry = digit / 10;
        num1[i - 1] = num1[i - 1] + carry;
    }
    digit = num1[0] + num2[0];
    result[1] = digit % 10;
    carry = digit / 10;
    if (carry == 1)
        result[0] = 1;
    else
    {
        result[0] = 0;
    }

    //Now the result array has contained the answer, we just need to transfer the answer to *finalresult
    for (i = 0; i < NumberArrayLength + 1; i++)		//be aware that this the length of result is NumberArrayLength + 1
    {
        finalresult[i] = result[i] + 48;	//Since *finalresult is char*, we need to change it from int to char by adding 48
    }
    finalresult[i] = '\0';	//Don't forget to put '\0' at last otherwise it will pop up some weird symbols

    //There is a chance that the first number is 0 since 10+10=20, not 50+51=101
    //We check if the first number is 0. If it is, then we just get rid of it
    if(finalresult[0] == '0')
        finalresult = &finalresult[1];

    //Finally, we free those dynamic arrays
    free(num1);
    free(num2);
    free(result);
    return finalresult;
}

/*
 * Addition function for one whole number and one decimal number
 * Because only one input has decimal number, this becomes really easy.
 * We can simply calculate the whole number part by using WholeNumberAddition and then add the decimal places using strcat
 */
char* WholeDecimalAddition(char* number1, char* number2)
{
    //First, we need to figure out which number has decimal number
    char* WholeNum1 = NULL;
    char* DecimalNum1 = NULL;
    char* WholeNum2 = NULL;
    char* DecimalNum2 = NULL;
    char* Number1 = strdup(number1);
    char* Number2 = strdup(number2);
    WholeNum1 = strtok(Number1, ".");
    DecimalNum1 = strtok(NULL, ".");
    WholeNum2 = strtok(Number2, ".");
    DecimalNum2 = strtok(NULL, ".");

    char* WholeNumberSum = NULL;	//This contains the whole number result
    char* finalresult = NULL;

    if (DecimalNum2 != NULL)	//If the first number is a whole number and the second one is a decimal number
    {
        WholeNumberSum = WholeNumberAddition(WholeNum1, WholeNum2);
        //The length of *finalresult should the the length of WholeNumberSum plus the length of decimal places plus 1 for '.'
        finalresult = malloc(strlen(WholeNumberSum)+strlen(DecimalNum2)+1);
        //Combine everything to *finalresult
        strcpy(finalresult, WholeNumberSum);
        strcat(finalresult, ".");
        strcat(finalresult, DecimalNum2);
    }
    else	//If the second number is a whole number and the first one is a decimal number
    {
        //Same as above
        WholeNumberSum = WholeNumberAddition(WholeNum1, WholeNum2);

        finalresult = malloc(strlen(WholeNumberSum)+strlen(DecimalNum1)+1);

        strcpy(finalresult, WholeNumberSum);
        strcat(finalresult, ".");
        strcat(finalresult, DecimalNum1);
    }
    //There may be useless 0s in the decimal places, we need to get rid of them
    int i;
    for (i = strlen(finalresult) - 1; i >= 0; i--)
    {
        if (finalresult[i] != '0')	//If the digit we find is non-zero, we know that everything after that are 0s and should be eliminated
        {
            finalresult[i + 1] = '\0';	//Simply putting '\0' behind the first non-zero digit will eliminate the zeros
            if (finalresult[i] == '.')	//If the first non-zero digit is the '.', it means the answer is a whole number
                finalresult[i] = '\0';	//We can ignore '.' as well
            break;
        }
    }
    free(WholeNumberSum);
    free(Number1);
    free(Number2);
    return finalresult;
}

/*
 * Addition function for two decimal numbers, this can be a little bit tricky
 * The idea is to get rid of the decimals and then treat them as two whole numbers
 * After doing the WholeNumberAddition, we can plug back in the decimal
 * It's very important to line up two numbers by their decimals, the idea is to add
 * 0s to the number that has less amount of DECIMAL numbers to make them equal size
 */
char* DecimalNumberAddition(char* number1, char* number2)
{
    //In this case, we know that both numbers have decimals, so we can just do it!
    char* WholeNum1 = NULL;
    char* DecimalNum1 = NULL;
    char* WholeNum2 = NULL;
    char* DecimalNum2 = NULL;
    char* Number1 = strdup(number1);
    char* Number2 = strdup(number2);
    WholeNum1 = strtok(Number1, ".");
    DecimalNum1 = strtok(NULL, ".");
    WholeNum2 = strtok(Number2, ".");
    DecimalNum2 = strtok(NULL, ".");

    int i;	//Counting variable i

    //Those two variables store two decimal numbers in Whole Number form.
    char* Decimal_Whole1 = NULL;
    char* Decimal_Whole2 = NULL;
    char* finalresult = NULL;

    /*
     * Here we have to split into cases since we don't know which number has more decimal numbers, or equal?
     * The first case is the situation where the first number has more decimal digits.
     */
    if (strlen(DecimalNum1) > strlen(DecimalNum2))
    {
        //Transferring decimal numbers into whole numbers, straight forward
        Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum1));
        Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum1));	//Be aware of the decimal digits! It's the length of the larger decimal digits!
        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);

        //We know strlen(DecimalNum1) > strlen(DecimalNum2), simply adding 0s to the back of the second number
        //to make them match in length
        for (i = 0; i < strlen(DecimalNum1) - strlen(DecimalNum2); i++)
            strcat(Decimal_Whole2, "0");

        finalresult = WholeNumberAddition(Decimal_Whole1, Decimal_Whole2);	//Now we do the addition calculation, putting the result into finalresult

        /*
         * This part is important!
         * Now we need to add the decimal back, we an easily figure out that the decimal should locate at strlen(*finalresult) - strlen(DecimalNum1)
         * Now we need to split *finalresult into two parts, just like substring in Java (too bad there's no such function in C!)
         * The idea is to create a temp variable which has length of strlen(*finalresult) + 1 (1 for the decimal) and move (copy) all the digits in
         * *finalresult into temp, including decimal
         *  (I tried to use realloc() but it didn't work for some weird reasons....)
         */
        char* Temp = malloc(strlen(finalresult) + 2);	//Declaring Temp variable
        for (i = 0; i < strlen(finalresult) - strlen(DecimalNum1); i++)
            Temp[i] = finalresult[i];	//This is the whole number part
        Temp[i++] = '.';	//After that is the decimal

        while (finalresult[i - 1] != '\0') 	//Be aware that the index here is i-1 since previous line Temp[i++]
        {
            Temp[i] = finalresult[i - 1];	//Copying decimal number part into Temp
            i++;
        }
        Temp[i] = '\0';		//Don't forget '\0' at the very end

        //If the answer is less than 1, it has to show "0."+something, right now the program will output "."+something.
        //The way to check is to check whether the first char is '.'
        if (Temp[0] == '.')
        {
            strcpy(finalresult, "0");
            strcat(finalresult, Temp);
            free(Temp);
        }
        else 	//Otherwise, just copy Temp variable to *finalresult and free Temp
        {
            strcpy(finalresult, Temp);
            free(Temp);

        }
    }
        //This case is the situation where the first number has less decimal digits.
    else if (strlen(DecimalNum1) < strlen(DecimalNum2))
    {
        Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum2));
        Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum2));
        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);

        //Pay a little attention on which has more digits than which
        for (i = 0; i < strlen(DecimalNum2) - strlen(DecimalNum1); i++)
            strcat(Decimal_Whole1, "0");

        finalresult = WholeNumberAddition(Decimal_Whole1, Decimal_Whole2);

        //Basically the same thing
        char* Temp = malloc(strlen(finalresult) + 2);
        for (i = 0; i < strlen(finalresult) - strlen(DecimalNum2); i++)
            Temp[i] = finalresult[i];
        Temp[i++] = '.';

        while (finalresult[i - 1] != '\0')
        {
            Temp[i] = finalresult[i - 1];
            i++;
        }
        Temp[i] = '\0';

        if (Temp[0] == '.')
        {
            strcpy(finalresult, "0");
            strcat(finalresult, Temp);
            free(Temp);
        }
        else {
            strcpy(finalresult, Temp);
            free(Temp);

        }
    }
        //This case is the situation where both numbers have the same decimal digits.
    else
    {
        Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum1));
        Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum2));

        strcpy(Decimal_Whole1, WholeNum1);
        strcat(Decimal_Whole1, DecimalNum1);
        strcpy(Decimal_Whole2, WholeNum2);
        strcat(Decimal_Whole2, DecimalNum2);

        finalresult = WholeNumberAddition(Decimal_Whole1, Decimal_Whole2);

        char* Temp = malloc(strlen(finalresult) + 2);
        for (i = 0; i < strlen(finalresult) - strlen(DecimalNum1); i++)
            Temp[i] = finalresult[i];
        Temp[i++] = '.';

        while (finalresult[i - 1] != '\0')
        {
            Temp[i] = finalresult[i - 1];
            i++;
        }
        Temp[i] = '\0';

        if (Temp[0] == '.') {
            strcpy(finalresult, "0");
            strcat(finalresult, Temp);
            free(Temp);
        }
        else {
            strcpy(finalresult, Temp);
            free(Temp);

        }

    }

    //There may be useless 0s in the decimal places, we need to get rid of them
    for (i = strlen(finalresult) - 1; i >= 0; i--) {
        if (finalresult[i] != '0')//If the digit we find is non-zero, we know that everything after that are 0s and should be eliminated
        {
            finalresult[i + 1] = '\0';//Simply putting '\0' behind the first non-zero digit will eliminate the zeros
            if (finalresult[i] == '.')//If the first non-zero digit is the '.', it means the answer is a whole number
                finalresult[i] = '\0';	//We can ignore '.' as well
            break;
        }
    }
    //Finally, don't forget to free those variables!
    free(Number1);
    free(Number2);
    free(Decimal_Whole1);
    free(Decimal_Whole2);
    return finalresult;
}

/*
 * This is the grade school subtraction function.
 * Subtraction can be tricky because the result can be negative; the solution is to compare two inputs first, figure out which sign the result will have;
 * then do the subtraction properly.
 */
char* WholeNumberSubtraction(char* number1, char* number2)
{
    char* Big = NULL;	//Stores big number
    char* Small = NULL;	//Opposite
    char* finalresult = NULL;
    int isNegative = 0;
    int i = 0;

    //First we need to eliminate 0s (if any) at the front of each number.(Sometimes users can be a pain in the ass....)
    //Similiar method used in the addition function
    int length1 = strlen(number1), length2 = strlen(number2);
    for (i = 0; i < length1; i++)
    {
        if (number1[i] != '0')
        {
            number1 = &number1[i];	//This is like string.substring(i) in java
            break;
        }
    }
    if (i == length1)	//If the result is just 0, we change the number1 to 0 as well
    {
        number1 = "0";
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
    if (i == length2)	//If the result is just 0, we change the *finalresult to 0 as well
    {
        number2 = "0";
    }

    /*
     * This part checks if the result has a negative sign.
     * The idea is to compare the length of two numbers. If one number is longer than the other then we know the longer number has to be bigger.
     * If two number have the same length, then we have to compare each corresponding digit and figure out which number is bigger
     */
    if (strlen(number1) > strlen(number2))
    {
        NumberArrayLength = strlen(number1);	//Set the NumberArrayLength be the length of larger number
        //Be aware that you need to dynamic allocate Big and Small first (if not, then the program will crash)
        Big = strdup(number1);
        Small = strdup(number2);
    }
    else if (strlen(number1) < strlen(number2))
    {
        NumberArrayLength = strlen(number2);
        Big = strdup(number2);
        Small = strdup(number1);
        isNegative = 1;
    }
    else
    {
        NumberArrayLength = strlen(number1);	//Since the length is the same, we can set NumberArrayLength ahead
        for (i = 0; i < strlen(number1); i++)	//Compare each digit
        {
            if (number1[i] > number2[i])
            {
                Big = strdup(number1);
                Small = strdup(number2);
                break;
            }
            else if (number1[i] < number2[i])
            {
                Big = strdup(number2);
                Small = strdup(number1);
                isNegative = 1;
                break;
            }
        }
        //There is a chance that two numbers are exactly the same, in that case we just set *finalresult to "0"
        if (i == strlen(number1))
        {
            finalresult = "0";
            free(Big);
            free(Small);
            return finalresult;
        }
    }

    int* num1 = NULL;
    int* num2 = NULL;
    toWholeNumber(&num1, Big);
    toWholeNumber(&num2, Small);

    int* result = malloc(NumberArrayLength * sizeof(int));	//The length of result has to be at most NumberArrayLength
    finalresult = malloc(NumberArrayLength + 1);
    //Boring Calculation steps
    int digit = 0;
    for (i = NumberArrayLength - 1; i > 0; i--)
    {
        if (num1[i] - num2[i] >= 0)
        {
            digit = num1[i] - num2[i];
            result[i] = digit;
        }
        else
        {
            digit = num1[i] + 10 - num2[i];
            result[i] = digit;
            num1[i - 1] -= 1;
        }
    }
    digit = num1[0] - num2[0];
    result[0] = digit;

    //Now the result array has contained the answer, we just need to transfer the answer to *finalresult
    for (i = 0; i < NumberArrayLength; i++)
        finalresult[i] = result[i] + 48;	//Since *finalresult is char*, we need to change it from int to char by adding 48

    finalresult[i] = '\0';	//Be aware

    //Sometimes there are useless 0s at the front, we need to clear them
    //Simply keep the digits after the last digit of 0s
    for (i = 0; i < strlen(finalresult); i++)
    {
        if (finalresult[i] != '0')
        {
            finalresult = &finalresult[i];
            if (isNegative)	//if the result is negative, we have to manually add "-" sign
            {
                char* Temp = strdup(finalresult);	//We duplicate *finalrsult to Temp
                strcpy(finalresult, "-");
                strcat(finalresult, Temp);
                free(Temp);
            }

            break;
        }
    }
    //Finally, we free those dynamic arrays
    free(Big);
    free(Small);
    free(num1);
    free(num2);
    free(result);
    return finalresult;

}

/*
 * This function combines DecimalWholeSubtraction and DecimalNumberSubtraction.
 * In addition, we separate them apart because there is a trick to do DecimalWholeAddition. In subtraction however, the trick remains, but only works in one case (1.05-1), so it's
 * not worth to make an separated function. The idea is basically the same as DecimalNumberAddition, we eliminate the decimal and treat them as two whole numbers subtracting.
 */
char* DecimalNumberSubtraction(char* number1, char* number2)
{
    //First, we assume that both numbers have decimal numbers
    char* WholeNum1 = NULL;
    char* DecimalNum1 = NULL;
    char* WholeNum2 = NULL;
    char* DecimalNum2 = NULL;
    char* Number1 = strdup(number1);
    char* Number2 = strdup(number2);
    WholeNum1 = strtok(Number1, ".");
    DecimalNum1 = strtok(NULL, ".");
    WholeNum2 = strtok(Number2, ".");
    DecimalNum2 = strtok(NULL, ".");
    int i;
    char* Decimal_Whole1 = NULL;
    char* Decimal_Whole2 = NULL;
    char* TempResult = NULL;	//Contains some temporary string, mostly for *finalresult
    char* Temp1 = NULL;		//Contains other miscellaneous strings
    char* finalresult = NULL;

    /*
     * There are three cases but we treat them as two cases ONLY. First case is the first number is a whole number and the second one is a decimal number, OR both of them are
     * decimal numbers but the length of decimal digits of the first number is LESS than the length of decimal digits of the second number;
     * second case is the first number is a decimal number and the second one is a whole number, OR both of them are decimal numbers but the length of decimal digits
     * of the first number is MORE than the length of decimal digits of the second number;
     * The third case is both numbers are decimal numbers and they have the same length of decimal digits, but this case can be combined into any of the cases above.
     */
    if (DecimalNum1 == NULL || (DecimalNum2 != NULL && (strlen(DecimalNum1) < strlen(DecimalNum2))))	//If the first number is a whole number and the second one is a decimal number
    {
        if (DecimalNum1 != NULL)	//If the first number has decimal
        {
            Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum2));	//Be aware that the length of decimals should be equal to the larger decimal digits
            strcpy(Decimal_Whole1, WholeNum1);
            strcat(Decimal_Whole1, DecimalNum1);

            Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum2));
            strcpy(Decimal_Whole2, WholeNum2);
            strcat(Decimal_Whole2, DecimalNum2);

            for (i = 0; i < strlen(DecimalNum2) - strlen(DecimalNum1); i++)		//Add 0s to the back of the first number
                strcat(Decimal_Whole1, "0");

        }
        else	//If the first number is a whole number
        {
            Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum2));
            strcpy(Decimal_Whole2, WholeNum2);
            strcat(Decimal_Whole2, DecimalNum2);

            Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum2));
            strcpy(Decimal_Whole1, WholeNum1);

            for (i = 0; i < strlen(DecimalNum2); i++)
                strcat(Decimal_Whole1, "0");
        }

        //Now do the Subtraction
        finalresult = WholeNumberSubtraction(Decimal_Whole1, Decimal_Whole2);

        /*
         * This is important! Now we need to add decimal to the correct position. There are several cases.
         * Case 1: If the length of *finalresult is less than the length of DecimalNum2 (ex. 1-0.9996=0.0004, but right now *finalresult shows 4)
         * Case 2: If the length of *finalresult is equal to the length of DecimalNum2 (ex. 1-0.5346=0.4654, but right now *finalresult shows 4654)
         * Case 3: See Case 3
         * Case 4: General Case (ex. 456-123.05=332.95)
         */
        if (strlen(finalresult) < strlen(DecimalNum2))		//Case 1
        {
            if (finalresult[0] == '-')	//If *finalresult is a negative number, we have to remove the "-" sign first and then do the operation
            {
                finalresult = &finalresult[1];
                TempResult = malloc(strlen(finalresult) + strlen(DecimalNum2));
                strcpy(TempResult, "");
                for (i = 0; i < strlen(DecimalNum2); i++)	//The idea is we add 0s to the front of *finalresult, it's okay if we add more 0s than we need
                    strcat(TempResult, "0");
                strcat(TempResult, finalresult);	//Now TempResult will look like 000000+*finalresult

                //Now we add the decimal, this method is from DecimalNumberAddition
                Temp1 = malloc(strlen(TempResult) + 2);
                for (i = 0; i < strlen(TempResult) - strlen(DecimalNum2); i++)
                    Temp1[i] = TempResult[i];
                Temp1[i++] = '.';
                while (TempResult[i - 1] != '\0')
                {
                    Temp1[i] = TempResult[i - 1];
                    i++;
                }
                Temp1[i] = '\0';
                //Since the answer is negative, we have to put "-" sign back
                strcpy(finalresult, "-");
                strcat(finalresult, Temp1);
            }
            else	//If *finalresult is positive, then we do the same thing except removing "-" sign
            {
                TempResult = malloc(strlen(finalresult) + strlen(DecimalNum2));
                strcpy(TempResult, "");
                for (i = 0; i < strlen(DecimalNum2); i++)
                    strcat(TempResult, "0");
                strcat(TempResult, finalresult);

                Temp1 = malloc(strlen(TempResult) + 2);
                for (i = 0; i < strlen(TempResult) - strlen(DecimalNum2); i++)
                    Temp1[i] = TempResult[i];
                Temp1[i++] = '.';
                while (TempResult[i - 1] != '\0')
                {
                    Temp1[i] = TempResult[i - 1];
                    i++;
                }
                Temp1[i] = '\0';
                strcpy(finalresult, Temp1);
            }
        }
            //Case 2
        else if (strlen(finalresult) == strlen(DecimalNum2))
        {
            if (finalresult[0] == '-')	//Ex. 1-1.0534=-0.0534, but *finalresult is -534, which length is equal to the length of DecimalNum2
            {
                finalresult = &finalresult[1];
                //basically do *fianlresult = "-0.0" + *finalresult in Java
                TempResult = strdup(finalresult);
                strcpy(finalresult, "-0.0");
                strcat(finalresult, TempResult);
            }
            else
            {
                TempResult = strdup(finalresult);
                strcpy(finalresult, "0.");
                strcat(finalresult, TempResult);
            }
        }
            //Case 3: Ex. 1-1.978=-0.978, but *finalresult is -978
        else if (strlen(finalresult) == (strlen(DecimalNum2) + 1) && finalresult[0] == '-')
        {
            finalresult = &finalresult[1];
            TempResult = strdup(finalresult);
            strcpy(finalresult, "-0.");
            strcat(finalresult, TempResult);
        }
            //Case 4: General Case, we use the method in DecimalNumberAddition
        else
        {
            Temp1 = malloc(strlen(finalresult) + 2);
            for (i = 0; i < strlen(finalresult) - strlen(DecimalNum2); i++)
                Temp1[i] = finalresult[i];
            Temp1[i++] = '.';
            while (finalresult[i - 1] != '\0')
            {
                Temp1[i] = finalresult[i - 1];
                i++;
            }
            Temp1[i] = '\0';
            strcpy(finalresult, Temp1);
        }
    }
        //If the second number is a whole number and the first one is a decimal number, plus equal decimal length subtraction
        //The idea is the same as above.
    else if (DecimalNum2 == NULL || (DecimalNum1 != NULL && (strlen(DecimalNum1) >= strlen(DecimalNum2))))
    {
        if (DecimalNum2 != NULL)
        {
            Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum1));
            strcpy(Decimal_Whole1, WholeNum1);
            strcat(Decimal_Whole1, DecimalNum1);

            Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum1));
            strcpy(Decimal_Whole2, WholeNum2);
            strcat(Decimal_Whole2, DecimalNum2);

            for (i = 0; i < strlen(DecimalNum1) - strlen(DecimalNum2); i++)
                strcat(Decimal_Whole2, "0");

        }
        else
        {
            Decimal_Whole1 = malloc(strlen(WholeNum1) + strlen(DecimalNum1));
            strcpy(Decimal_Whole1, WholeNum1);
            strcat(Decimal_Whole1, DecimalNum1);

            Decimal_Whole2 = malloc(strlen(WholeNum2) + strlen(DecimalNum1));
            strcpy(Decimal_Whole2, WholeNum2);

            for (i = 0; i < strlen(DecimalNum1); i++)
                strcat(Decimal_Whole2, "0");
        }

        finalresult = WholeNumberSubtraction(Decimal_Whole1, Decimal_Whole2);

        if(strcmp(finalresult, "0") == 0)
            return "0";

        if(strlen(finalresult) < strlen(DecimalNum1))
        {
            if(finalresult[0] == '-')
            {
                finalresult = &finalresult[1];
                TempResult = malloc(strlen(finalresult) + strlen(DecimalNum1));
                strcpy(TempResult, "");
                for(i=0; i<strlen(DecimalNum1); i++)
                    strcat(TempResult, "0");
                strcat(TempResult, finalresult);

                Temp1 = malloc(strlen(TempResult) + 2);
                for (i = 0; i < strlen(TempResult) - strlen(DecimalNum1); i++)
                    Temp1[i] = TempResult[i];
                Temp1[i++] = '.';
                while (TempResult[i - 1] != '\0')
                {
                    Temp1[i] = TempResult[i - 1];
                    i++;
                }
                Temp1[i] = '\0';
                strcpy(finalresult, "-");
                strcat(finalresult, Temp1);
            }
            else
            {
                TempResult = malloc(strlen(finalresult) + strlen(DecimalNum1));
                strcpy(TempResult, "");
                for (i = 0; i < strlen(DecimalNum1); i++)
                    strcat(TempResult, "0");
                strcat(TempResult, finalresult);

                Temp1 = malloc(strlen(TempResult) + 2);
                for (i = 0; i < strlen(TempResult) - strlen(DecimalNum1); i++)
                    Temp1[i] = TempResult[i];
                Temp1[i++] = '.';
                while (TempResult[i - 1] != '\0')
                {
                    Temp1[i] = TempResult[i - 1];
                    i++;
                }
                Temp1[i] = '\0';
                strcpy(finalresult, Temp1);
            }
        }
        else if(strlen(finalresult) == strlen(DecimalNum1))
        {
            if(finalresult[0] == '-')
            {
                finalresult = &finalresult[1];
                TempResult = strdup(finalresult);
                strcpy(finalresult, "-0.0");
                strcat(finalresult, TempResult);
            }
            else
            {
                TempResult = strdup(finalresult);
                strcpy(finalresult, "0.");
                strcat(finalresult, TempResult);
            }
        }
        else if(strlen(finalresult) == (strlen(DecimalNum1)+1) && finalresult[0] == '-')
        {
            finalresult = &finalresult[1];
            TempResult = strdup(finalresult);
            strcpy(finalresult, "-0.");
            strcat(finalresult, TempResult);
        }
        else
        {
            Temp1 = malloc(strlen(finalresult) + 2);
            for (i = 0; i < strlen(finalresult) - strlen(DecimalNum1); i++)
                Temp1[i] = finalresult[i];
            Temp1[i++] = '.';
            while (finalresult[i - 1] != '\0')
            {
                Temp1[i] = finalresult[i - 1];
                i++;
            }
            Temp1[i] = '\0';
            strcpy(finalresult, Temp1);
        }
    }
    else	//I don't know...Is there other cases?
    {
        printf("WTF?\n");
    }

    //Now we need to check the useless 0s in front, methods are the same
    if(finalresult[0] == '-')
    {
        finalresult = &finalresult[1];
        for(i=0; i<strlen(finalresult); i++)
        {
            if(finalresult[i] != '0')
            {
                finalresult = &finalresult[i];
                if(finalresult[0] == '.')
                {
                    Temp1 = strdup(finalresult);
                    strcpy(finalresult, "0");
                    strcat(finalresult, Temp1);
                }
                break;
            }
        }
        Temp1 = strdup(finalresult);
        strcpy(finalresult, "-");
        strcat(finalresult, Temp1);
    }
    else
    {
        for (i = 0; i < strlen(finalresult); i++)
        {
            if (finalresult[i] != '0')
            {
                finalresult = &finalresult[i];
                if (finalresult[0] == '.')
                {
                    Temp1 = strdup(finalresult);
                    strcpy(finalresult, "0");
                    strcat(finalresult, Temp1);
                }
                break;
            }
        }
    }

    //Now the back
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
    //Free dynamic variables
    free(Number1);
    free(Number2);
    free(Decimal_Whole1);
    free(Decimal_Whole2);
    free(TempResult);
    free(Temp1);
    return finalresult;
}



