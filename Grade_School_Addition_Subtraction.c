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

