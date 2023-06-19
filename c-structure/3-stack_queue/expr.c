/* evaluation from expressions (using stack)
 * 20200128
 * infix to postfix는 operator 스택, postfix evaluation은 operand 스택
 */

#include <stdio.h>
#include <stdbool.h>

#define MAXSZ 100

typedef int Element;

/* stack */

Element _stack[MAXSZ];
int _top = -1;

void init()
{
    _top = -1;
}
bool empty()
{
    return _top == -1;
}
Element top()
{
    return _stack[_top];
}
void push(int e)
{
    if (_top == MAXSZ - 1)
        return;
    _stack[++_top] = e;
}
void pop()
{
    if (_top == -1)
        return;
    _top--;
}

/*
void printStack()
{
    int i;
    for (i = 0; i <= _top; i++)
        printf("%c ", _stack[i]);
}
*/

/* infix to postfix */
void inToPost(char dst[], const char *src)
{
    char c;
    init();
    for (; *src; src++) {
        switch (*src) {
        case '+':
            while (!empty()) {
                if ((c = top()) == '(')
                    break;
                *dst++ = c;
                pop();
            }
            push(*src);
            break;
        case '-':
            while (!empty()) {
                if ((c = top()) == '(')
                    break;
                *dst++ = c;
                pop();
            }
            push(*src);
            break;
        case '*':
            while (!empty()) {
                if ((c = top()) == '(')
                    break;
                switch (c) {
                case '*':
                case '/':
                case '%':
                    *dst++ = c;
                    pop();
                }
            }
            push(*src);
            break;
        case '/':
            while (!empty()) {
                if ((c = top()) == '(')
                    break;
                switch (c) {
                case '*':
                case '/':
                case '%':
                    *dst++ = c;
                    pop();
                }
            }
            push(*src);
            break;
        case '%':
            while (!empty()) {
                if ((c = top()) == '(')
                    break;
                switch (c) {
                case '*':
                case '/':
                case '%':
                    *dst++ = c;
                    pop();
                }
            }
            push(*src);
            break;
        case '(':
            push(*src);
            break;
        case ')':
            while (!empty()) {
                if ((c = top()) == '(') {
                    pop();
                    break;
                }
                *dst++ = c;
                pop();
            }
            break;
        default:
            *dst++ = *src;
        }
        /*
        printf("insert %c : ", *src);
        printStack();
        printf("\n");
        */
    }
    while (!empty())
        *dst++ = top(), pop();
    *dst = '\0';
}

/* postfix evaluation */
int postEval(char *str)
{
    char c;
    int l, r, ret;
    init();
    for (; *str; str++) {
        switch (*str) {
        case '+':
            r = top(), pop();
            l = top(), pop();
            push(l + r);
            break;
        case '-':
            r = top(), pop();
            l = top(), pop();
            push(l - r);
            break;
        case '*':
            r = top(), pop();
            l = top(), pop();
            push(l * r);
            break;
        case '/':
            r = top(), pop();
            l = top(), pop();
            push(l / r);
            break;
        case '%':
            r = top(), pop();
            l = top(), pop();
            push(l % r);
            break;
        default:
            push(*str - '0');
        }
    }
    ret = top(), pop();
    if (!empty())
        fprintf(stderr, "invalid postfix notation\n");
    return ret; 
}

/* main */

int main()
{
    char *infix = "5*(2+3)%4+2";
    char postfix[MAXSZ];
    int answer;
    
    printf("infix : %s\n", infix);
    inToPost(postfix, infix);
    printf("postfix : %s\n", postfix);
    answer = postEval(postfix);
    printf("answer : %d\n", answer);
}

