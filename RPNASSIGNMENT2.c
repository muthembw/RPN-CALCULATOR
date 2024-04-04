#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 256

// Stack for characters (for conversion)
typedef struct {
    int top;
    char items[MAX];
} CharStack;

// Stack for double (for evaluation)
typedef struct {
    int top;
    double items[MAX];
} DoubleStack;

void pushChar(CharStack *s, char value) {
    if (s->top < (MAX - 1)) {
        s->items[++(s->top)] = value;
    } else {

    }
}

char popChar(CharStack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {

        return -1; // Return a value that indicates the stack is empty
    }
}

void pushDouble(DoubleStack *s, double value) {
    if (s->top < (MAX - 1)) {
        s->items[++(s->top)] = value;
    } else {

    }
}

double popDouble(DoubleStack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {

        return -1; // Return a value that indicates the stack is empty
    }
}

int isOperator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%';
}

int precedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    CharStack stack;
    stack.top = -1;
    int k = 0;

    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            pushChar(&stack, '(');
        } else if (infix[i] == ')') {
            while (stack.top != -1 && stack.items[stack.top] != '(') {
                postfix[k++] = popChar(&stack);
            }
            popChar(&stack); // Pop '('
        } else if (isOperator(infix[i])) {
            while (stack.top != -1 && precedence(infix[i]) <= precedence(stack.items[stack.top])) {
                postfix[k++] = popChar(&stack);
            }
            pushChar(&stack, infix[i]);
        }
    }

    while (stack.top != -1) {
        postfix[k++] = popChar(&stack);
    }

    postfix[k] = '\0';
}

double evaluatePostfix(char* postfix) {
    DoubleStack stack;
    stack.top = -1;

    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) {
            pushDouble(&stack, (double)(postfix[i] - '0'));
        } else {
            double val1 = popDouble(&stack);
            double val2 = popDouble(&stack);
            switch (postfix[i]) {
                case '+': pushDouble(&stack, val2 + val1); break;
                case '-': pushDouble(&stack, val2 - val1); break;
                case '*': pushDouble(&stack, val2 * val1); break;
                case '/': pushDouble(&stack, val2 / val1); break;
                case '%': pushDouble(&stack, (int)val2 % (int)val1); break;
            }
        }
    }

    return popDouble(&stack);
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}
