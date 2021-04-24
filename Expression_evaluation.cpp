//
// Created by ggfvi on 2021-04-23.
//栈链实现表达式求值

#include <iostream>

using namespace std;
const char oper[7] = {'+', '-', '*', '/', '(', ')', '#'};
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char SElemType;
typedef int Status;
typedef struct SNode {
    char data;
    struct SNode *next;
} SNode, *LinkStack;

Status InitStack(LinkStack &S) {
    S = NULL;
    return OK;
}

bool StackEmpty(LinkStack S) {
    if (!S)
        return true;
    return false;
}

Status Push(LinkStack &S, SElemType e) {
    SNode *p = new SNode;
    if (!p) {
        return OVERFLOW;
    }
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

Status Pop(LinkStack &S, SElemType &e) {
    SNode *p;
    if (!S)
        return ERROR;
    e = S->data;
    p = S;
    S = S->next;
    delete p;
    return OK;
}

Status GetTop(LinkStack &S) {
    if (!S)
        return ERROR;
    return S->data;
}

bool In(char ch) {//判断ch是否为运算符
    for (int i = 0; i < 7; i++) {
        if (ch == oper[i]) {
            return true;
        }
    }
    return false;
}

char Precede(char theta1, char theta2) {//判断运算符优先级
    if ((theta1 == '(' && theta2 == ')') || (theta1 == '#' && theta2 == '#')) {
        return '=';
    } else if (theta1 == '(' || theta1 == '#' || theta2 == '(' ||
               (theta1 == '+' || theta1 == '-') && (theta2 == '*' || theta2 == '/')) {
        return '<';
    } else
        return '>';
}

char Operate(char first, char theta, char second) {//计算两数运算结果
    switch (theta) {
        case '+':
            return (first - '0') + (second - '0') + 48;
        case '-':
            return (first - '0') - (second - '0') + 48;
        case '*':
            return (first - '0') * (second - '0') + 48;
        case '/':
            return (first - '0') / (second - '0') + 48;
    }
    return 0;
}

//算法3.22 表达式求值
char EvaluateExpression() {//算数表达式求值的算符优先算法
    LinkStack OPTR, OPND;
    char ch, theta, a, b, x, top;
    InitStack(OPND);//初始化OPND栈
    InitStack(OPTR);//初始化OPTR栈
    Push(OPTR, '#');
    cin >> ch;
    while (ch != '#' || (GetTop(OPTR) != '#')) {
        if (!In(ch)) {
            Push(OPND, ch);
            cin >> ch;
        }//ch不是运算符则进OPND栈
        else
            switch (Precede(GetTop(OPTR), ch)) {//比较OFTR的栈顶元素和ch的优先级
                case '<':
                    Push(OPTR, ch);
                    cin >> ch;
                    break;
                case '>':
                    Pop(OPTR, theta);
                    Pop(OPND, b);
                    Pop(OPND, a);
                    Push(OPND, Operate(a, theta, b));
                    break;
                case '=':
                    Pop(OPTR, x);
                    cin >> ch;
                    break;
            }//switch
    }//while
    return GetTop(OPND);//OPND栈顶元素即视为表达式求值结果
}

int menu() {
    int c;
    cout << "0-9以内的多项式计算" << endl;
    cout << "1.计算" << endl;
    cout << "0.退出\n" << endl;
    cout << "选择：" << endl;
    cin >> c;
    return c;
}

int main() {
    while (1) {
        switch (menu()) {
            case 1: {
                cout << "请输入要计算的表达式（操作数和结果都在0-9的范围内，以#结束）" << endl;
                char res = EvaluateExpression();//算法3.22 表达式求值
                cout << "计算结果为" << res - 48 << endl << endl;
            }
                break;
            case 0:
                cout << "退出成功\n" << endl;
                exit(0);
            default:
                break;
        }
    }
}
