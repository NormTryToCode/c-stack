#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <ctype.h>
#include <math.h>
typedef struct Node NodeObject;

struct Node{
    void* info; // for generalization
    char type;
    NodeObject* next;
};

int normalPower(int x, int y){
    // x is the base, y is the power
    int normalResult = 1;

    for (int iteration = 0; iteration < y; iteration++){
        normalResult *= x; 
    }
    return normalResult;
}

double power(double x, double y){
    double powerrResult = 1.0;
    if (trunc(y) == y){
        for (int iteration = 0; iteration < y; iteration++){
            powerrResult *= x; 
        }
    return powerrResult;
    }
    else {
        printf("Sorry, the fractional part of y cannot be a non-zero!");
        return -1;
    }
}


void* peekTop(NodeObject* yourTop){
    if (yourTop == NULL){
        return NULL;
    }
    return yourTop->info;
}

void push(NodeObject** top_of_stack, void* e, char type){
    NodeObject* newNode = (NodeObject*)malloc(sizeof(NodeObject));
    newNode->info = e;
    newNode->type = type;
    newNode->next = *top_of_stack;
    *top_of_stack = newNode;


}
int countStackElements(NodeObject* top_of_stack){
    NodeObject* currentNode = top_of_stack;
    int result = 0;
    if (currentNode == NULL){
        return result;
    }
    else {
        while (currentNode != NULL){
            currentNode = currentNode->next;
            result += 1;
        }
    }
    return result;
}

void pop(NodeObject** top_of_stack, NodeObject** back_of_stack){
    NodeObject* placeholder = *top_of_stack;
    if (placeholder == NULL) {
        return;
    }
    *top_of_stack = (*top_of_stack)->next;
    *back_of_stack = *top_of_stack;
    free(placeholder->info);
    free(placeholder);
    placeholder = NULL;
}

void printStack(NodeObject* top_of_stack){
    NodeObject* currentNode = top_of_stack;
    int elementCount = countStackElements(top_of_stack);
    
    if (currentNode == NULL){
        printf("[]\n");
        return;
    }
    printf("[");
    while (currentNode != NULL){
        if (currentNode->next != NULL){
            if (currentNode->type == 'i') {
                int intValue = (*(int*)currentNode->info);
                printf("%d, ", intValue);
            }
            else if (currentNode->type == 'f') {
                float floatValue = (*(float*)currentNode->info);
                printf("%f, ", floatValue);
            }
            else if (currentNode->type == 'c') {
                char charValue = (*(char*)currentNode->info);
                printf("'%c', ",charValue);
            }
            else if (currentNode->type == 's') {
                char* stringValue = (char*)currentNode->info;
                printf("\"%s\", ",stringValue);
            }
            else if (currentNode->type == 'd') {
                double doubleValue = (*(double*)currentNode->info);
                printf("'%f', ", doubleValue);
            }
        }
        else {
            if (currentNode->type == 'i') {
                int intValue = *((int*)currentNode->info);
                printf("%d]\n", intValue);
            }
            else if (currentNode->type == 'f') {
                float floatValue = (*(float*)currentNode->info);
                printf("%f]\n", floatValue);
            }
            else if (currentNode->type == 'c'){
                char charValue = (*(char*)currentNode->info);
                printf("'%c']\n", charValue);
            }
            else if (currentNode->type == 's') {
                char* stringValue = (char*)currentNode->info;
                printf("\"%s\"]\n",stringValue);
            }
             else if (currentNode->type == 'd') {
                double doubleValue = (*(double*)currentNode->info);
                printf("%f]\n", doubleValue);
            }
        }
        currentNode = currentNode->next;
    }
}

bool parenthesisChecking(char** input){
    char* parenthesisOpen = "([{";
    char* parenthesisClose = ")]}";

    char* alphabetLower = "abcdefghijklmnopqrstuvwxyz";
    char* alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* operator = "+-*/^";

    int parenthesisOpenAmount = 0;
    int parenthesisCloseAmount = 0;

    int parenthesisPopAmount = 0;
    int parenthesisPushAmount = 0;


    NodeObject* parenthesisTop = NULL;
    NodeObject* parenthesisBottom = NULL;   
    for (int inputIndex = 0; inputIndex < strlen(*input); inputIndex++){
        char currentChar = (*input)[inputIndex];
        char* sameOnOpen = strchr(parenthesisOpen, currentChar); // checks if there's same character from the input compared to the open parenthesis
        char* sameOnClose = strchr(parenthesisClose, currentChar); // checks if there's same character from the input compared to the closed parenthesis
        if (sameOnOpen != NULL){
            // printf("open parenthesis detected!\n");
            if ('(' == currentChar){
                char* openNormalBrackets = (char*)malloc(sizeof(char));
                *openNormalBrackets = currentChar;
                push(&parenthesisTop, openNormalBrackets, 'c');
                
            }
            else if ('[' == currentChar){
                char* openSquareBrackets = (char*)malloc(sizeof(char));
                *openSquareBrackets = currentChar;
                push(&parenthesisTop, openSquareBrackets, 'c');
            }
            else {
                char* openCurlyBrackets = (char*)malloc(sizeof(char));
                *openCurlyBrackets = currentChar;
                push(&parenthesisTop, openCurlyBrackets, 'c');
            }
            parenthesisOpenAmount += 1;
            parenthesisPushAmount += 1;
        }
        else if (sameOnClose != NULL) {
            // printf("close parenthesis detected!\n");
            parenthesisCloseAmount += 1;
            if ((char*)peekTop(parenthesisTop) == NULL) { // this means, there isn't any opening parenthesis before the closing parenthesis
                 return false;
            }
            char previousChar = (*(char*)peekTop(parenthesisTop)); // calls peekTop(parenthesisTop) cast it to char* and dereference it
            char* isAlphabetLower = strchr(alphabetLower, previousChar);
            char* isAlphabetUpper = strchr(alphabetUpper, previousChar);
            char* isOperator = strchr(operator, previousChar);
            if (')' == currentChar){
                if ('(' == previousChar) { 
                    pop(&parenthesisTop, &parenthesisBottom);
                }
            }
            else if (']' == currentChar){
                if ('[' == previousChar) {
                    pop(&parenthesisTop, &parenthesisBottom);
                }
            }
            else if ('}' == currentChar) {
                if ('{' == previousChar){
                    pop(&parenthesisTop, &parenthesisBottom);
                }
            }
            // else if (isAlphabetLower != NULL) {
            //     continue;
            // }
            // else if (isAlphabetUpper != NULL) {
            //     continue;
            // }
            // else if (isOperator != NULL) {
            //     continue;
            // }
            else {
                while (parenthesisTop != NULL){
                    pop(&parenthesisTop, &parenthesisBottom);
                }
                return false;
            }

        }
        // printf("Parenthesis open amount: %d\n", parenthesisOpenAmount);
        // printf("Parenthesis close amount: %d\n", parenthesisCloseAmount);
    }
    if (parenthesisTop == NULL) {
        return true;    
    }
    else {
        return false;
    }
}



void infixToPostfix(char** stringToChange){
    // If only with this logic, it cannot change the expression that uses more than one digit, for example
    //(10 + 8) / 9

    NodeObject* stack = NULL;
    NodeObject* bottom_stack = NULL;
    char* parenthesisOpen = "([{";
    char* parenthesisClose = ")]}";
    char* operator = "+-*/^";
    char* alphabetLowerPost = "abcdefghijklmnopqrstuvwxyz";
    char* alphabetUpperPost = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* digits = "0123456789";
    bool validation = parenthesisChecking(stringToChange);
    int priorityArray[] ={3, 3, 2, 2, 1}; // the lower the greater the priority

    if (!validation) {
        printf("Maaf, kurung nya tidak valid!\n");
        return;
    }

    for (int currentIndex = 0; currentIndex < strlen(*stringToChange); currentIndex++){
        char currentChar = (*stringToChange)[currentIndex];
        char* isOperator = strchr(operator, currentChar);
        char* isOpenParenthesis = strchr(parenthesisOpen, currentChar);
        char* isCloseParenthesis = strchr(parenthesisClose, currentChar);
        char* isAlphabetLower = strchr(alphabetLowerPost, currentChar);
        char* isAlphabetUpper = strchr(alphabetUpperPost, currentChar);
        char* isDigit = strchr(digits, currentChar);
        if (isOperator != NULL) { // this will not return null if the string is found
            char* currentOperator = (char*)malloc(sizeof(char));
            *currentOperator = currentChar;
            if (stack == NULL) {
                push(&stack, currentOperator, 'c');
                continue; // there's nothing to do after this
            }
            
            int index = (int)(isOperator - operator); // to retrieve the index, isOperator pointer - operator pointer, where operator pointer points to index 0, and isOperator is what index on the operator points to
            int priority = priorityArray[index];
            bool isPreviousOperatorNULL = false;
            while (stack != NULL) { 
                char previousOperator = (*(char*)peekTop(stack));
                char* isOperatorPrevious = strchr(operator, previousOperator);
                if (isOperatorPrevious == NULL) {
                    isPreviousOperatorNULL = true;
                    break;
                }
                int indexOfPreviousOperator = (int)(isOperatorPrevious - operator);
                int priorityOfPreviousOperator = priorityArray[indexOfPreviousOperator];
                if (priorityOfPreviousOperator <= priority) {
                    pop(&stack, &bottom_stack); 
                    printf("%c", previousOperator);
                }
                else {
                    break;
                }
            }

            push(&stack, currentOperator, 'c');
        }
        else if (isOpenParenthesis != NULL) {
            char* currentOpen = (char*)malloc(sizeof(char));
            *currentOpen = currentChar;
            push(&stack, currentOpen, 'c');
            // printStack(stack);
        }
        else if (isCloseParenthesis != NULL) {
            while ((char*)peekTop(stack) != NULL) {
                char* isParentOpen = strchr(parenthesisOpen, *(char*)peekTop(stack));
                
                
                if (isParentOpen == NULL){
                    printf("%c", *(char*)peekTop(stack));
                    pop(&stack, &bottom_stack);
                }
                else {
                    break;
                }
                
            }
            pop(&stack, &bottom_stack);
        }
        else if (isAlphabetLower != NULL || isAlphabetUpper != NULL || isDigit != NULL){
            printf("%c", currentChar);
        }
    }
    // mengecek apakah masih ada operator yang masih belum terpanggil karena kurang n
    while (stack != NULL){
        printf("%c", *(char*)peekTop(stack));
        pop(&stack, &bottom_stack);
    }
    printf("\n");

    // A + B / C, ABC/+
    // 10 8+9/
}

void infixToPostfixGeneral(char** stringToChange){
    NodeObject* stack = NULL;
    NodeObject* bottom_stack = NULL;
    char* parenthesisOpen = "([{";
    char* parenthesisClose = ")]}";
    char* operator = "+-*/^";
    char* alphabetLowerPost = "abcdefghijklmnopqrstuvwxyz";
    char* alphabetUpperPost = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* digits = "0123456789";
    bool validation = parenthesisChecking(stringToChange);
    int priorityArray[] ={3, 3, 2, 2, 1}; // the lower the greater the priority

    if (!validation) {
        printf("Maaf, kurung nya tidak valid!\n");
        return;
    }
    int strLength = strlen(*stringToChange);
    for (int currentIndex = 0; currentIndex < strLength; currentIndex++){
        char currentChar = (*stringToChange)[currentIndex];

        int currentTokenIndex = 0;
        char* isOperator = strchr(operator, currentChar);
        char* isOpenParenthesis = strchr(parenthesisOpen, currentChar);
        char* isCloseParenthesis = strchr(parenthesisClose, currentChar);

        char* isAlphabetLower = strchr(alphabetLowerPost, currentChar);
        char* isAlphabetUpper = strchr(alphabetUpperPost, currentChar);
        char* isDigit = strchr(digits, currentChar);
        if (isOperator != NULL) { // this will not return null if the string is found
            char* currentOperator = (char*)malloc(sizeof(char));
            *currentOperator = currentChar;
            if (currentChar == '-'){
                bool unary = currentIndex == 0 || strchr("+-*/(", (*stringToChange)[currentIndex-1]) != NULL; //unary means we treat it as operand, not operator
                if (currentIndex == 0){
                    printf("%c", *currentOperator);
                    free(currentOperator);
                    continue;
                }
                if (currentIndex + 1 < strLength && isdigit((*stringToChange)[currentIndex+1])){
                
                    if (!unary){
                        currentChar = (*stringToChange)[currentIndex];
                        *currentOperator = currentChar;
                        push(&stack, currentOperator, 'c');
                        continue;
                    }
                    printf("%c", *currentOperator);
                    currentIndex++;
                    while (currentIndex + 1 < strLength && isdigit((*stringToChange)[currentIndex+1])){
                        printf("%c", (*stringToChange)[currentIndex]);
                        currentIndex += 1;
                    } 
                    currentIndex--;
                    free(currentOperator);
                    continue;
                }
            }
            if (stack == NULL) {
                push(&stack, currentOperator, 'c');
                continue; // there's nothing to do after this
            }
            
            int index = (int)(isOperator - operator); // to retrieve the index, isOperator pointer - operator pointer, where operator pointer points to index 0, and isOperator is what index on the operator points to
            int priority = priorityArray[index];
            bool isPreviousOperatorNULL = false;
            while (stack != NULL) { 
                char previousOperator = (*(char*)peekTop(stack));
                char* isOperatorPrevious = strchr(operator, previousOperator);
                if (isOperatorPrevious == NULL) {
                    isPreviousOperatorNULL = true;
                    break;
                }
                int indexOfPreviousOperator = (int)(isOperatorPrevious - operator);
                int priorityOfPreviousOperator = priorityArray[indexOfPreviousOperator];
                if (priorityOfPreviousOperator <= priority) {
                    pop(&stack, &bottom_stack); 
                    printf("%c ", previousOperator);
                }
                else {
                    break;
                }
            }

            push(&stack, currentOperator, 'c');
        }
        else if (isOpenParenthesis != NULL) {
            char* currentOpen = (char*)malloc(sizeof(char));
            *currentOpen = currentChar;
            push(&stack, currentOpen, 'c');
            // printStack(stack);
        }
        else if (isCloseParenthesis != NULL) {
            while ((char*)peekTop(stack) != NULL) {
                char* isParentOpen = strchr(parenthesisOpen, *(char*)peekTop(stack));
                
                
                if (isParentOpen == NULL){
                    printf("%c ", *(char*)peekTop(stack));
                    pop(&stack, &bottom_stack);
                }
                else {
                    break;
                }
                
            }
            pop(&stack, &bottom_stack);
        }
        else if (isAlphabetLower != NULL || isAlphabetUpper != NULL){
            printf("%c ", currentChar);
        }
        
        else if (isdigit((*stringToChange)[currentIndex]) || ((*stringToChange)[currentIndex]) == '.'){
            while (isdigit((*stringToChange)[currentIndex]) || ((*stringToChange)[currentIndex]) == '.'){
                printf("%c", (*stringToChange)[currentIndex]);
                currentIndex += 1;
        }
            printf(" ");
            currentIndex--;
        }
    }
    // mengecek apakah masih ada operator yang masih belum terpanggil karena kurang n
    while (stack != NULL){
        printf("%c ", *(char*)peekTop(stack));
        pop(&stack, &bottom_stack);
    }
    printf("\n");

    // A + B / C, ABC/+
    // 10 8+9/
}

double evaluatePostFix(char* expression){
    int elementNumber = strlen(expression);
    // printf("\nelement number: %d", elementNumber);
    NodeObject* numberStack = NULL;
    NodeObject* backNumberStack = NULL;
    char* operator = "+-*/^";
    int stringLen = strlen(expression);
    // printf("\nCode running...");
    for (int currentIndex = 0; currentIndex < stringLen; currentIndex++){
        // printf("\nCurrent index: %d", currentIndex);
        // printf("\nInside for loop...");   
        // printf("\ncurrent char: %c", expression[currentIndex]);
        char* isOperator = strchr(operator, expression[currentIndex]); 
        if (isdigit(expression[currentIndex]) || ( currentIndex + 1 < stringLen && expression[currentIndex] == '-' && isdigit(expression[currentIndex + 1])) ){ // currentIndex + 1 < stringLen to ensure that it won't go out of index
            // printf("\nIs a digit...");
            char* operandStored = (char*)malloc(elementNumber + 1);
            operandStored[0] = '\0';
            int position = 0;
            while (isdigit(expression[currentIndex]) || ( currentIndex + 1 < stringLen && expression[currentIndex] == '-' && isdigit(expression[currentIndex + 1])) || (expression[currentIndex] == '.') ){
                operandStored[position++] = expression[currentIndex]; // append the digits on the char*
                currentIndex++;
            }
            operandStored[position] = '\0';
            // printf("\nCurrent index: %d", currentIndex);
            
            double* currentNum = (double*)malloc(sizeof(double));
            if (strlen(operandStored) == 1 && operandStored[0] == '0'){
                printf("Maaf angka mu tidak valid!");
                free(operandStored);
                operandStored = NULL;
                return -1;
            }
            currentIndex--;
            *currentNum = atof(operandStored); // converting string to number
            push(&numberStack, currentNum, 'd');
            free(operandStored);
            operandStored = NULL;
        }
        else if (isOperator != NULL){
            // printf("Operator here\n");
            
            if (numberStack != NULL){
                    double secondNumber = *(double*)peekTop(numberStack);
                    pop(&numberStack, &backNumberStack);
                    double firstNumber = *(double*)peekTop(numberStack);
                    double* resultPointer = (double*)malloc(sizeof(double));
                    if (expression[currentIndex] == '+'){
                        *resultPointer = firstNumber + secondNumber;
                    }
                    else if (expression[currentIndex] == '-'){
                        *resultPointer = firstNumber -  secondNumber;
                    }
                    else if (expression[currentIndex] == '*'){
                        *resultPointer = firstNumber * secondNumber;
                    }
                    else if (expression[currentIndex] == '/'){
                        *resultPointer = firstNumber / secondNumber;
                    }
                    else if (expression[currentIndex] == '^'){
                        *resultPointer = power(firstNumber, secondNumber);
                    }
                    pop(&numberStack, &backNumberStack);
                    push(&numberStack, resultPointer, 'd');
            }
        }
        else if (expression[currentIndex] == ' '){
            continue;
        }
        else {
            printf("Maaf ekspresi ini tidak valid!");
            return -1;
        }
    }
    double finalResult = *(double*)peekTop(numberStack);
    pop(&numberStack, &backNumberStack);
    return finalResult;
}

int main(){
    NodeObject* top_of_stack = NULL;
    NodeObject* bottom_of_stack = NULL;
    char type = 'i';
    // char* myString = "Hello";
    char* myFirstString = (char*)malloc(strlen("test") + 1); // It's actually a good convention to use const to a char pointer, even though you cannot 
    strcpy(myFirstString, "test");
    // change it by indexing
    int* first_number = (int*)malloc(sizeof(int));
    *first_number = 1;
    int* second_number = (int*)malloc(sizeof(int));
    *second_number = 2;
    int* third_number = (int*)malloc(sizeof(int));
    *third_number = 3;
    float* my_float = (float*)malloc(sizeof(float));
    *my_float = 4.32f;
    char* myString = (char*)malloc(strlen("my string") + 1);
    strcpy(myString, "my string");
    char* testParenthesis = (char*)malloc(strlen("()[][[]][{{}}]") + 1);
    strcpy(testParenthesis, "()[][[]][{{}}]");
    char* expression = (char*)malloc(strlen("(a + b * (c / (d- e))) + f / g") + 1);
    strcpy(expression, "3.2*-3.4");
    printStack(top_of_stack);


    push(&top_of_stack, myFirstString, 's');
    push(&top_of_stack, first_number, 'i');
    push(&top_of_stack, second_number, 'i');
    push(&top_of_stack, third_number, 'i');
    // push(&top_of_stack, &my_float, 'f');
    push(&top_of_stack, myString, 's');

    // push(&top_of_stack, myString);

    printStack(top_of_stack);
    // infixToPostfix(&myString);
    pop(&top_of_stack, &bottom_of_stack);
    printStack(top_of_stack);
    // printStack(top_of_stack);
    // pop(&top_of_stack, &bottom_of_stack);

    // printStack(top_of_stack);
    // char* myString = "Hello";
    // puts(myString);
    // changeStr(&myString);
    // puts(myString);
    
    parenthesisChecking(&testParenthesis);
    printf("Ekspresi infix: %s\n", expression);
    printf("Ekspresi postfix: ");
    infixToPostfixGeneral(&expression);
    printf("\n");
    char* postfixToEvaluate = "3.14159 22 7 / *";
    printf("Normal power: %d\n", normalPower(-2, 5));
    double postfixResult = evaluatePostFix(postfixToEvaluate);
    printf("Postifx expression %s\n", postfixToEvaluate);
    // %g is handy, it switches between %d, %f, and scientific notation, soo instead of this
    // if (trunc(postfixResult) == postfixResult) {
    //     int postfixIntegerResult = (int)postfixResult;
    //     printf("The postfix result : %d\n", postfixIntegerResult);
    // }
    // else {
    //     printf("The postfix result : %.4f\n", postfixResult);
    // }
    // you could do this
    printf("The postfix result: %.100g\n", postfixResult);
}
