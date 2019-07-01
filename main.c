#include "Stack.h"
#include "Queue.h"
#include "Grade_School_Addition_Subtraction.h"
#include "Faster_Multiplication_Division.h"

void InputNumber(char* (*pStr));
int priority(char operator);	//Return the priority of the operator
char* evaluatePostfix(LinkQueue* queue, int OperandAmount, char* previous, int Decimals);		//Calculate the final answer
int isRight(char*number1, char* number2);
int CalculateStatus(char* number1, char* number2);
int CheckSign(char* number1, char* number2);

int main(void)
{
    char* finalresult = NULL;
    int MaxNumberofOperands=50;  //set a max number of operands in each input, say 50
    int NumberofDecimals;
    printf("Ultimate Calculator\n");
    printf("How many decimal places, if any, do you want? \n");
    scanf("%d", &NumberofDecimals);
    getchar();
    /*
    printf("Ultimate Calculator\n");
    printf("How many operands are there in the expression? \n");
    scanf("%d", &MaxNumberofOperands);

   */
    while(1)
    {
        printf("Input:");
        char* input = NULL;
        InputNumber(&input);    //Attention!! There must be "=" at the back!!

        if(strcmp(input, "over")==0)
            break;
        if(input[strlen(input)-1] != '=')
        {
            printf("Incorrect Input! You have to type '=' at the end. Program ends.");
            exit(EXIT_FAILURE);
        }

        LinkStack* OperatorStack = createStack();	//Create a stack that has operators
        LinkQueue* PostfixQueue = createQueue();	//Create a queue that can transform expression to Postfix

        int i=0;	//Records the subscripts of the expression, basically the location, like input[i]
        int j=0;	//Records the subscripts of each operands, that is, the location of a number in this operand
        int k=0;	//Records the amount of operands
        int l=0;	//Records the amount of operators

        /*
         * This is a 2 dimensional array recording each operand, be aware that the operands here are char*, not int
         * this array can be written as numberdata[MaxNumberoOperands][]
         * the first [] is the amount of operands, that is MaxNumberoOperands, recorded by k
         * the second [] is the amount of numbers in each operands, that varies, recorded by j
         */
        char** numberdata = (char**)malloc(MaxNumberofOperands * sizeof(char*));


        /*
         * This is a 2 dimensional array recording each operator, be aware that the operators here are char*, not char
         */
        char** operatordata = (char**)malloc(MaxNumberofOperands * sizeof(char*));
        for(i=0; i<MaxNumberofOperands; i++)     //Initialize elements to 0
        {
            operatordata[i] = (char*)malloc(2 * sizeof(char));
            //memset(ProductResult[i], 0, MaxLength*sizeof(int));
        }
        i=0;

        char* operator = NULL;
        char* TempOperand = NULL;
        TempOperand = strdup("");
        while(input[i]!='\0')
        {

            if(input[i]!='+' && input[i]!='-' && input[i]!='*' && input[i]!='/' && input[i]!='(' && input[i]!=')' && input[i]!='=')
            {
                char a[2] = {input[i], '\0'};
                strcat(TempOperand, a);
                j++;
            }
                //If input[i] is a operator, then do the following
            else
            {
                numberdata[k] = strdup(TempOperand);
                if(strcmp(numberdata[k], "") != 0)
                {
                    TempOperand = strdup("");
                    EnQueue(PostfixQueue, numberdata[k]);
                    k++;
                }

                operator = &input[i];

                if(isStackEmpty(OperatorStack))		//Èç¹ûÕâÊÇµÚÒ»¸öÔªËØ£¬ÄÇÃ´Ö±½Ó½øÕ»
                {
                    push(OperatorStack, operator);
                }
                else//Èç¹û²»ÊÇ£¬ÄÇÃ´¾ÍÒª±È½ÏÓÅÏÈ¼¶
                {
                    if(*operator=='(')	//Èç¹ûÓöµ½×óÀ¨ºÅ£¬ÄÇÃ´Ö±½ÓÈëÕ»
                    {
                        push(OperatorStack, operator);
                    }
                    else if(*operator==')')		//Èç¹ûÓöµ½ÓÒÀ¨ºÅ£¬ÄÇÃ´ÔÚ×óÀ¨ºÅÖ®ºóµÄÔªËØÈ«²¿³öÕ»
                    {
                        while(*(char*)(OperatorStack->top->data)!='(')	//¼ì²éÏÂÒ»¸öÔªËØÊÇ·ñÊÇ×óÀ¨ºÅ
                        {
                            //ÕâÀïÊÇÄÑµã
                            char c = *(char*)pop(OperatorStack);	//ÒòÎªpopµÄ·µ»ØÖµÊÇvoid*£¬void*²»¿ÉÒÔÖ±½Ódereference
                            //Òò´ËÒªÇ¿ÖÆ×ª»»void*±ä³ÉËùÐèÒªµÄÖ¸Õë±äÁ¿£¬ÕâÒ²ÊÇÎªÊ²Ã´Òª¼Ó(char*)
                            //×ª»»Ö®ºóËü»¹ÊÇÒ»¸öÖ¸Õë±äÁ¿£¬ÏÖÔÚ¾Í¿ÉÒÔdereference£¬ÔÚÇ°Ãæ¼Ó*£¬ÄÃµ½operator
                            operatordata[l][0]=c;	//½«operator·Åµ½operatordataÖÐÏàÓ¦Êý×éµÄµÚÒ»¸öÎ»ÖÃ
                            operatordata[l][1]='\0';	//µÚ¶þ¸öÎ»ÖÃÊÇ'\0'
                            EnQueue(PostfixQueue, operatordata[l]);		//Õâ¸öÊ±ºòoperator¾Í±ä³ÉÁË×Ö·û´®£¬Ö±½ÓEnQueue
                            l++;	//ÕâÀï±ðÍüÁË×Ô¼Ó
                        }

                        pop(OperatorStack);	//Õâ¸öÔªËØÊÇ×óÀ¨ºÅ£¬Òª°ÑËüÈÓ³öÈ¥
                    }
                    else	//Èç¹ûÖ»ÊÇÆÕÍ¨·ûºÅ£¬ÄÇÃ´¾Í°´ÏÈºóË³Ðò½øÕ»»ò³öÕ»
                    {
                        while(!isStackEmpty(OperatorStack) && priority(*operator)<=priority(*(char*)(OperatorStack->top->data)))	//¼ÆËã¹«Ê½
                        {
                            //Í¬ÉÏ£¬ÏàÍ¬µÄµÀÀí
                            char c = *(char*)pop(OperatorStack);
                            operatordata[l][0]=c;
                            operatordata[l][1]='\0';
                            EnQueue(PostfixQueue, operatordata[l]);
                            l++;
                        }

                        push(OperatorStack, operator);	//Èç¹ûµ±Ç°ÔªËØµÄÓÅÏÈÈ¨´óÓÚÉÏÒ»¸öÔªËØ£¬ÔòÈëÕ»
                    }
                }
                j=0;	//jÖµ³õÊ¼»¯Îª0
            }
            i++;
        }
        pop(OperatorStack);	//×îºóÒ»¸öÔªËØÊÇÒ»¸öµÈºÅ£¬Òò´ËÒª°ÑËüÈ¥µô

        while(!isStackEmpty(OperatorStack))	//½«Õ»ÀïµÄÊ£ÓàÔªËØÒÀ´Î³öÕ»
        {
            char c = *(char*)pop(OperatorStack);
            operatordata[l][0]=c;
            operatordata[l][1]='\0';
            EnQueue(PostfixQueue, operatordata[l]);
            l++;
        }



        //µ½ÏÖÔÚÎªÖ¹£¬±í´ïÊ½ÒÑ¾­±ä³ÉpostfixÐÎÊ½²¢´æ´¢ÔÚ¶ÓÁÐÖÐ
        // finalresult = "-9750.9216349";
        finalresult = evaluatePostfix(PostfixQueue, k, finalresult, NumberofDecimals);		//¼ÆËã±í´ïÊ½µÄ×îÖÕÖµ
        printf("%s%s\n", input, finalresult);
        /*char* Temp = strdup(finalresult);
        char* Whole = strtok(Temp, ".");
        char* Decimal = strtok(NULL, ".");
        if(Decimal == NULL)
        {
            free(Temp);
            printf("%s%s\n", input, finalresult);
        }
        else
        {
            if(strlen(Decimal) <= NumberofDecimals)
            {
                free(Temp);
                printf("%s%s\n", input, finalresult);
            }
            else
            {
                Decimal[NumberofDecimals] = '\0';
                strcpy(finalresult, Whole);
                strcat(finalresult, ".");
                strcat(finalresult, Decimal);
                free(Temp);
                printf("%s%s\n", input, finalresult);
            }
        }*/
        k--;
        l--;
        while(k>=0)
        {
            free(numberdata[k]);
            k--;
        }
        free(numberdata);
        while(l>=0)
        {
            free(operatordata[l]);
            l--;
        }
        free(operatordata);
        DestroyStack(OperatorStack);
        DestroyQueue(PostfixQueue);
        free(TempOperand);
        free(input);
    }

    return EXIT_SUCCESS;
}



int priority(char operator)
{
    if(operator == '+' || operator == '-')	//¼Ó¼õÎª1
        return 1;
    else if(operator == '*' || operator == '/')	//³Ë³ýÎª2
        return 2;
    else if(operator == '(' || operator == ')')	//À¨ºÅÎª0£¬ÓÐ×¨ÃÅ¶ÔÓÚÀ¨ºÅµÄ²½Öè
        return 0;
    else return 0;
}

/*
 * ¸üÐÂ£ºÕâ¸öº¯ÊýÏÖÔÚ¿ÉÒÔÊ¹ÓÃÉÏÒ»¸öËãÊ½µÄ×îÖÕÖµ£¬Ïàµ±ÓÚ¼ÆËãÆäÖÐµÄ¡°ans¡±¼ü
 * ·½·¨ÊÇÔÚº¯ÊýÀï´«µÝÖ¸Õë
 */
char* evaluatePostfix(LinkQueue* queue, int OperandAmount, char* previous, int Decimals)
{
    LinkStack* stack = createStack();	//´´ÔìÒ»¸öÕ»£¬·ÅÖÃoperand
    char** number = (char**) malloc(sizeof(char*)*OperandAmount);
    int i=0, j=0;
    char** result = (char**) malloc(sizeof(char*)*(OperandAmount-1));

    while(!isQueueEmpty(queue))
    {
        char* temp = (char*)DeQueue(queue);		//µÚÒ»¸öÔªËØ³ö¶ÓÁÐ
        if(!(strcmp(temp, "+")==0 || strcmp(temp, "-")==0 || strcmp(temp, "*")==0 || strcmp(temp, "/")==0))
            //Èç¹ûÔªËØ²»ÊÇoperator£¬ËüÒ»¶¨ÊÇÊý×Ö
        {
            if(strcmp(temp, "ans")==0)
                //Èç¹ûÕâ¸öÔªËØÊÇ¡°ans¡±µÄ»°£¬½«Ö¸ÏòÉÏÒ»¸ö×îÖÕÖµµÄÖ¸Õëdereference£¬È»ºó¸³¸ønumber[i]
            {
                number[i]=strdup(previous);
                push(stack, number[i]);
                i++;
            }
            else
            {
                number[i] = strdup(temp);
                push(stack, number[i]);		//operandÈëÕ»
                i++;
            }

        }
            //Èç¹ûÔªËØÊÇoperator
        else
        {
            //Õ»¶¥¶ËµÄÁ½¸öÊý³öÕ»£¬×öÔËËã
            char* number2 = (char*)pop(stack);
            char* number1 = (char*)pop(stack);

            if(strcmp(temp, "+")==0)	//¼Ó·¨ÔËËã
            {
                if (isRight(number1, number2))
                {
                    //char* result = NULL;
                    int Status = CalculateStatus(number1, number2);
                    int Sign = CheckSign(number1, number2);

                    switch (Status)
                    {
                        case 1:
                            switch (Sign)
                            {
                                case 1:
                                    result[j] = WholeNumberAddition(number1, number2);
                                    break;
                                case 2:
                                    result[j] = WholeNumberSubtraction(number2, &number1[1]);
                                    break;
                                case 3:
                                    result[j] = WholeNumberSubtraction(number1, &number2[1]);
                                    break;
                                case 4:
                                    result[j] = WholeNumberAddition(&number1[1], &number2[1]);
                                    char* Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                            }
                            break;
                        case 2:
                            switch (Sign)
                            {
                                case 1:
                                    result[j] = WholeDecimalAddition(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberSubtraction(number2, &number1[1]);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberSubtraction(number1, &number2[1]);
                                    break;
                                case 4:
                                    result[j] = WholeDecimalAddition(&number1[1], &number2[1]);
                                    char* Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                            }
                            break;
                        case 3:
                            switch (Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberAddition(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberSubtraction(number2, &number1[1]);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberSubtraction(number1, &number2[1]);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberAddition(&number1[1], &number2[1]);
                                    char* Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                            }
                            break;
                    }
                    j++;
                }
                else
                {
                    printf("Incorrect Input! Please make sure that your input is valid. Program ends.");
                    exit(EXIT_FAILURE);
                }
                //printf("%d+%d=%d\n", operand1, operand2, result[j]);

            }

            else if (strcmp(temp, "-")==0)	//¼õ·¨ÔËËã
            {
                if (isRight(number1, number2))
                {
                    //char* result = NULL;
                    int Status = CalculateStatus(number1, number2);
                    int Sign = CheckSign(number1, number2);

                    switch (Status)
                    {
                        case 1:
                            switch (Sign)
                            {
                                case 1:
                                    result[j] = WholeNumberSubtraction(number1, number2);
                                    break;
                                case 2:
                                    result[j] = WholeNumberAddition(&number1[1], number2);
                                    char* Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = WholeNumberAddition(number1, &number2[1]);
                                    break;
                                case 4:
                                    result[j] = WholeNumberSubtraction(&number2[1], &number1[1]);
                                    break;
                            }
                            break;
                        case 2:
                            switch (Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberSubtraction(number1, number2);
                                    break;
                                case 2:
                                    result[j] = WholeDecimalAddition(&number1[1], number2);
                                    char* Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = WholeDecimalAddition(number1, &number2[1]);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberSubtraction(&number2[1], &number1[1]);
                                    break;
                            }
                            break;
                        case 3:
                            switch (Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberSubtraction(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberAddition(&number1[1], number2);
                                    char* Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberAddition(number1, &number2[1]);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberSubtraction(&number2[1], &number1[1]);
                                    break;
                            }
                            break;
                    }
                    j++;
                }
                else
                {
                    printf("Incorrect Input! Please make sure that your input is valid. Program ends.");
                    exit(EXIT_FAILURE);
                }
            }
            else if (strcmp(temp, "*")==0)	//³Ë·¨ÔËËã
            {
                if(isRight(number1, number2))
                {
                    //char* result = NULL;
                    char* Temp = NULL;
                    int Status = CalculateStatus(number1, number2);
                    int Sign = CheckSign(number1, number2);

                    switch(Status)
                    {
                        case 1:
                            switch(Sign)
                            {
                                case 1:
                                    result[j] = WholeNumberMultiplication(number1, number2);
                                    break;
                                case 2:
                                    result[j] = WholeNumberMultiplication(&number1[1], number2);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = WholeNumberMultiplication(number1, &number2[1]);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 4:
                                    result[j] = WholeNumberMultiplication(&number1[1], &number2[1]);
                                    break;
                            }
                            break;
                        case 2:
                            switch(Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberMultiplication(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberMultiplication(&number1[1], number2);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberMultiplication(number1, &number2[1]);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberMultiplication(&number1[1], &number2[1]);
                                    break;
                            }
                            break;
                        case 3:
                            switch(Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberMultiplication(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberMultiplication(&number1[1], number2);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberMultiplication(number1, &number2[1]);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberMultiplication(&number1[1], &number2[1]);
                                    break;
                            }
                            break;
                    }
                    j++;
                }
                else
                {
                    printf("Incorrect Input! Please make sure that your input is valid. Program ends.");
                    exit(EXIT_FAILURE);
                }
            }
            else	//³ý·¨ÔËËã
            {
                if(isRight(number1, number2))
                {
                    //char* result = NULL;
                    char* Temp = NULL;
                    int Status = CalculateStatus(number1, number2);
                    int Sign = CheckSign(number1, number2);

                    switch(Status)
                    {
                        case 1:
                            switch(Sign)
                            {
                                case 1:
                                    result[j] = WholeNumberDivision(number1, number2);
                                    break;
                                case 2:
                                    result[j] = WholeNumberDivision(&number1[1], number2);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = WholeNumberDivision(number1, &number2[1]);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 4:
                                    result[j] = WholeNumberDivision(&number1[1], &number2[1]);
                                    break;
                            }
                            break;
                        case 2:
                            switch(Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberDivision(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberDivision(&number1[1], number2);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberDivision(number1, &number2[1]);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberDivision(&number1[1], &number2[1]);
                                    break;
                            }
                            break;
                        case 3:
                            switch(Sign)
                            {
                                case 1:
                                    result[j] = DecimalNumberDivision(number1, number2);
                                    break;
                                case 2:
                                    result[j] = DecimalNumberDivision(&number1[1], number2);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 3:
                                    result[j] = DecimalNumberDivision(number1, &number2[1]);
                                    Temp = strdup(result[j]);
                                    strcpy(result[j], "-");
                                    strcat(result[j], Temp);
                                    free(Temp);
                                    break;
                                case 4:
                                    result[j] = DecimalNumberDivision(&number1[1], &number2[1]);
                                    break;
                            }
                            break;
                    }
                    j++;
                }
                else
                {
                    printf("Incorrect Input! Please make sure that your input is valid. Program ends.");
                    exit(EXIT_FAILURE);
                }
            }
            push(stack, result[j-1]);	//°ÑÔËËãºÃµÄresultÔÙÈëÕ»
        }
    }
    char* finalresult = (char*)pop(stack);	//×öµ½×îºóÒ»¶¨Ö»Ê£ÏÂÒ»¸öÊý£¬ÄÇ¸öÊý¾ÍÊÇ×îÖÕ´ð°¸
//If there is any chance, create a round method
/*
    char* WholeNum = NULL;
    char* DecimalNum = NULL;
    char* Finalresult = strdup(finalresult);    //Make a copy of the inputs Really Important!

    WholeNum = strtok(Finalresult, ".");
    DecimalNum = strtok(NULL, ".");

    if(DecimalNum != NULL && strlen(DecimalNum)>Decimals)
    {
        if(DecimalNum[Decimals] < '5')
            DecimalNum[Decimals] = '\0';
        else
        {
            DecimalNum[Decimals] = '\0';
            char* Temp = malloc(Decimals+3);
            strcpy(Temp, "0.");

            strcpy(result, Temp);
        }
    }*/

    i--;
    j--;
    DestroyStack(stack);
    while(i>=0)
    {
        free(number[i]);
        i--;
    }
    free(number);
    while(j>=0)
    {
        free(result[j]);
        j--;
    }
    free(result);
    return finalresult;
}


/*
 * This is a function that has no return but takes a pointer pointing to char* as input.
 * Very Important: say InputNumber(&number) where number is char* type, printf("%p", &number) should be
 * the same as printf("%p", pStr).
 * Call by reference, check https://www.youtube.com/watch?v=LW8Rfh6TzGg&t=690s for more info
 * Basically, let the pointers do the job so that we don't have to return anything.
 * The good thing about this function is that there is no input limit, which means that readers can type
 * any many digits as they want.
 */
void InputNumber(char* (*pStr))
{
    unsigned int MaxLength = 5;	//initially set the char array to be 50 unit long
    unsigned int CurrentSize = 0;
    *pStr = malloc(MaxLength);	//Caution: pStr is a pointer to pointer, you have to dereference
    //to get the real char array
    CurrentSize = MaxLength;

    if(*pStr != NULL)	//If everything is working perfectly
    {
        char c;
        unsigned int i =0;
        //accept user input until hit enter or end of file
        while ((c = getchar()) != '\n')
        {
            (*pStr)[i++]=c;
            //if i reached maximize size then realloc size
            if(i == CurrentSize)
            {
                CurrentSize = i+MaxLength;
                *pStr = realloc(*pStr, CurrentSize);
            }
        }
        //If c='\n', it means that input has finished
        if(i == CurrentSize)	//there is a small chance that the array is full after \n
            *pStr = realloc(*pStr, CurrentSize+1);	//we have to realloc again, but this time by 1, just for '\0'
        (*pStr)[i] = '\0';
    }
}


int isRight(char*number1, char* number2)
{
    int i = 0, j = 0;
    char c = '.';
    //First we need to check if input has more than one '.'
    //We use while loop to do that.
    //We only need to check digits before '\0' so we can do it using while loop
    while(number1[i] != '\0')
    {
        if(c == number1[i])	//If there is a '.' in the input, j++
            j++;
        if(j == 2)	//If there are two '.', it means the input is invalid, so we just return 0
            return 0;
        i++;
    }
    //initialize variables
    i = 0;
    j = 0;
    while(number2[i] != '\0')	//do the same thing for the second input
    {
        if (c == number2[i])
            j++;
        if (j == 2)
            return 0;
        i++;
    }
    //Inputs can have negative sign, so the first digit can be either a number or '-'
    //If the first digit is '.', it is invalid
    if (!(number1[0] == '-' || (number1[0] >= '0' && number1[0] <= '9')))
        return 0;
    i = 1;
    //Now we check the rest digits and see if there is any letters or strange symbols
    while (number1[i] != '\0')
    {
        if (!(number1[i] == '.' || (number1[i] >= '0' && number1[i] <= '9')))	//If a digit is not a number or '.'
            return 0;															//just return 0
        i++;
    }
    //do the same thing for the second input
    if (!(number2[0] == '-' || (number2[0] >= '0' && number2[0] <= '9')))
        return 0;
    i = 1;
    while (number2[i] != '\0')
    {
        if (!(number2[i] == '.' || (number2[i] >= '0' && number2[i] <= '9')))
            return 0;
        i++;
    }
    //If both inputs pass the test, then we return 1, meaning true
    return 1;
}


int CalculateStatus(char* number1, char* number2)
{
    //Initialize two Strings
    char* temp1 = NULL;
    char* temp2 = NULL;

    /*
     * Although this is obvious and not hard, it took me a long time to figure out this bug (I was using eclipse and didn't use debugger)
     * This is the main bug (to me)
     * When you do strtok(), it really splits the string, which means that your original string has been modified
     * Unlike Java, you have to make a copy of your original string if you need it later
     * Otherwise you will get runtime error all the time like I did
     */
    char* Number1 = strdup(number1);
    char* Number2 = strdup(number2);

    //Since each number has a whole number part, we can simply ignore it.
    //We are focusing the decimal part ONLY
    strtok(Number1, ".");	//this is the whole number part, simply ignore it
    temp1 = strtok(NULL, ".");	//this is the decimal part, stored in temp1.
    //If there is no decimal part, temp1 will be NULL
    strtok(Number2, ".");
    temp2 = strtok(NULL, ".");

    free(Number1);
    free(Number2);
    //This is how we check the status, basically checking if Temp1 is NULL or temp2 is NULL
    if (temp1 == NULL && temp2 == NULL)	//two whole numbers, return 1
        return 1;
    else if (temp1 == NULL && temp2 != NULL)	//one whole number, one decimal number, return 2
        return 2;
    else if (temp1 != NULL && temp2 == NULL)	//one whole number, one decimal number, return 2
        return 2;
    else 	//two decimal numbers, return 3
        return 3;
}

/*
 * This function checks if input has a '-' sign.
 * Different signs mean different calculation in addition and subtraction.
 * Notice that there is a difference between first number is + and second is - versus first is - and second is +
 * So we need to deal with it separately.
 */
int CheckSign(char* number1, char* number2)
{
    if (number1[0] != '-' && number2[0] != '-')		//two positive numbers, return 1
        return 1;
    else if (number1[0] == '-' && number2[0] != '-')	//one positive, one negative, return 2
        return 2;
    else if (number1[0] != '-' && number2[0] == '-')	//one negative, one positive, return 3
        return 3;
    else
        return 4;	//two negative numbers, return 4
}
