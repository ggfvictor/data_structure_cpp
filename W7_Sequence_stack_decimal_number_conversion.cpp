//
// Created by ggfvi on 2021-04-16.
//顺序栈实现十进制数转换
#include <iostream>

using namespace std;

#define OK 1
#define  ERROR 0
#define OVERFLOW -2
#define N 2

typedef int selemtype;

#define MAXSIZE 100

typedef struct {
    selemtype *base;
    selemtype *top;
    int stacksize;
} sqstack;

typedef int status;

status initstack(sqstack &s) {
    //初始化，构造一个空栈
    s.base = new selemtype[MAXSIZE];
    if (!s.base) exit(OVERFLOW);
    s.top = s.base;
    s.stacksize = MAXSIZE;
    return OK;
}

status Push(sqstack &s, selemtype e) {
    //把e压入栈顶，栈顶指针+1
    if (s.top - s.base == s.stacksize) return ERROR;
    *s.top = e;
    s.top++;
    return OK;
}

status Pop(sqstack &s, selemtype &e) {
    //栈首元素出栈赋给e
    if (s.top == s.base) return ERROR;
    s.top--;
    e = *s.top;
    return OK;
}

int main() {
    sqstack s;
    initstack(s);
    cout << "请输入一个十进制的数：";
    int num;
    cin >> num;
    while (num) {
        Push(s, num % N);
        num = num / N;
    }
    cout << endl;
    cout << "对应的" << N << "进制数：";
    while (s.top != s.base) {
        selemtype e;
        Pop(s, e);
        cout << e;
    }
    cout << endl;
    return 0;
}
