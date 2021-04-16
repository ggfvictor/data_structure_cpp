//
// Created by ggfvi on 2021-04-16.
//十进制数转换的栈链实现
#include <iostream>

using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int SElemType;

typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

//栈的初始化
Status InitStack(LinkStack &S) {
    //构造一个空栈
    S = NULL;
    return OK;
}

//栈链的入栈
Status Push(LinkStack &S, SElemType e) {
    LinkStack p;
    p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

//栈链的出栈
Status Pop(LinkStack &S, SElemType &e) {
    LinkStack p;
    if (S == NULL)
        return ERROR;
    e = S->data;
    p = S;
    S = S->next;
    delete p;
    return OK;
}

//取栈链的栈顶元素
SElemType GetTop(LinkStack S) {
    if (S != NULL)
        return S->data;
}

//数制的转换(栈链实现)
void conversion(int N) {
    int e;
    LinkStack S;
    InitStack(S);
    while (N) {
        Push(S, N % 8);
        N = N / 8;
    }
    while (S) {
        Pop(S, e);
        cout << e;
    }
}

int main() {
    int n, e;
    cout << "请输入一个非负十进制数：" << endl;
    cin >> n;
    conversion(n);
    cout << endl;
    return 0;
}
