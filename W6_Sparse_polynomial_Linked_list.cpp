//
// Created by ggfvi on 2021-04-09.
//

#include <iostream>

using namespace std;

#define OK 1
#define ERROR 0

typedef int status;

typedef struct {
    int coef;
    int expn;
} Elemtype;

typedef struct Lnode {
    Elemtype data;
    struct Lnode *next;
} Lnode, *Linklist;

status initlist(Linklist &L) {//初始化，构造一个空的单链表L（只有一个头结点）
    L = new Lnode;
    L->next = NULL;
    return OK;
}

status listinsert(Linklist &L, int i, Elemtype e) {//在单链表L的第i个位置（从1开始）插入值为e的新结点
    Linklist p = L;
    int j = 0;
    while (p && j < (i - 1)) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) return ERROR;
    Linklist s = new Lnode;
    s->data.coef = e.coef;
    s->data.expn = e.expn;
    s->next = p->next;
    p->next = s;
    return OK;
}//时间复杂度O(n)

status getelem(Linklist L, int i, Elemtype &e) {//在单链表L中取序号为i的结点值放到e中
    Linklist p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;
    e.coef = p->data.coef;
    e.expn = p->data.expn;
    return OK;
}//时间复杂度O(n)

void output(Linklist &L) {//输出单链表多项式L
    Linklist p = L->next;
    while (p) {
        cout << p->data.coef << "x^" << p->data.expn << "+";
        p = p->next;
    }
}//时间复杂度O(n)

void padd(Linklist &L1, Linklist &L2, Linklist &L3) {//两个多项式相加，L3=L1+L2
    Linklist p1 = L1->next, p2 = L2->next, p3 = L3;
    while (p1 && p2)//L1,L2均未结束
    {
        if (p1->data.expn == p2->data.expn) {
            int sum = p1->data.coef + p2->data.coef;
            if (sum != 0) {//生成新的和结点，插入到L3中
                Linklist s = new Lnode;
                s->data.coef = sum;
                s->data.expn = p1->data.expn;
                s->next = p3->next;
                p3->next = s;
                p1 = p1->next;
                p2 = p2->next;
                p3 = s;
            } else {//和L3中没有该节点，p1，p2移到下一个结点
                p1 = p1->next;
                p2 = p2->next;
            }
        } else {
            if (p1->data.expn > p2->data.expn) {//把p2结点插入到L3中，p1不动
                Linklist s = new Lnode;
                s->data.coef = p2->data.coef;
                s->data.expn = p2->data.expn;
                s->next = p3->next;
                p3->next = s;
                p3 = s;
                p2 = p2->next;
            } else {//把p1结点插入到L3中，p2不动
                Linklist s = new Lnode;
                s->data.coef = p1->data.coef;
                s->data.expn = p1->data.expn;
                s->next = p3->next;
                p3->next = s;
                p3 = s;
                p1 = p1->next;

            }
        }
    }
    if (!p1)//L1先结束，把L2剩余段插入到L3中
    {
        while (p2) {
            Linklist s = new Lnode;
            s->data.coef = p2->data.coef;
            s->data.expn = p2->data.expn;
            s->next = p3->next;
            p3->next = s;
            p3 = s;
            p2 = p2->next;
        }
    } else//L2先结束，把L1剩余段插入L3中
    {
        while (p1) {
            Linklist s = new Lnode;
            s->data.coef = p1->data.coef;
            s->data.expn = p1->data.expn;
            s->next = p3->next;
            p3->next = s;
            p3 = s;
            p1 = p1->next;
        }
    }
}//时间复杂度O(n+m)

int main() {
    Linklist L1;
    initlist(L1);
    cout << "请输入多项式的项数：";
    int m;
    cin >> m;
    cout << "请输入多项式的系数和指数：";
    for (int i = 1; i <= m; i++) {
        Elemtype e;
        cin >> e.coef >> e.expn;
        listinsert(L1, i, e);
    }
    cout << "该多项式是：";
    for (int i = 1; i <= m; i++) {
        Elemtype e;
        getelem(L1, i, e);
        cout << e.coef << "x^" << e.expn << "+";
    }
    cout << endl;
    Linklist L2;
    initlist(L2);
    cout << "请输入第二个多项式的项数：";
    int n;
    cin >> n;
    cout << "请输入第二个多项式的系数和指数：";
    for (int i = 1; i <= n; i++) {
        Elemtype e;
        cin >> e.coef >> e.expn;
        listinsert(L2, i, e);
    }
    cout << "该多项式是：";
    output(L2);
    cout << endl;
    Linklist L3;
    initlist(L3);
    padd(L1, L2, L3);
    cout << "这两个多项式的和是：";
    output(L3);
    cout << endl;
    return 0;
}
