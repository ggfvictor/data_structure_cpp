//
// Created by ggfvi on 2021-04-02.
//
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
#define OK 1
#define ERROR 0

typedef int status;

typedef struct {
    char num[10];
    char name[20];
    float price;
} Elemtype;

typedef struct Lnode {
    Elemtype data;
    struct Lnode *next;
} Lnode, *Linklist;

status initlist(Linklist &L) {
    L = new Lnode;
    L->next = nullptr;
    return OK;
}

status listinsert(Linklist &L, int i, Elemtype e) {//在单链表L的第i位置（从i开始）插入值为e的新节点
    Linklist p = L;
    int j = 0;
    while (p && j < (i - 1)) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) return ERROR;
    Linklist s;
    s = new Lnode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}//时间复杂度0(n)

void output(Linklist &L) {//输出单链表
    Linklist p = L->next;
    while (p) {
        printf("%s %s %.2f\n", p->data.num, p->data.name, p->data.price);
        p = p->next;
    }
}//时间复杂度0(n)

status listdelete(Linklist &L, int i) {//删除单链表L第i个元素
    Linklist p = L;
    int j = 0;
    while ((p->next) && (j < i - 1)) {
        p = p->next;
        j++;
    }
    if (!(p->next) || (j > i - 1)) return ERROR;
    Linklist q = p->next;
    p->next = q->next;
    delete q;
    return OK;
}

Lnode *locatename(Linklist L, Elemtype e) {//在单链表L中查找值为e的节点
    Linklist p = L->next;
    while (p && strcmp(p->data.name, e.name) != 0)
        p = p->next;
    return p;
}

int main() {
    Linklist L;
    initlist(L);
    Elemtype e;
    int x = 1;
    while (x) {
        cout << "----图书信息管理系统----" << endl;
        cout << "1：输入图书信息" << endl;
        cout << "2：插入图书信息" << endl;
        cout << "3：删除图书信息" << endl;
        cout << "4：查询图书信息" << endl;
        cout << "5：退出系统" << endl;
        cout << "请输入要执行的操作：" << endl;
        cin >> x;
        switch (x) {
            case 1:
                //输入图书信息
                cout << "请输入图书的数目：";
                int n;
                cin >> n;
                for (int i = 1; i <= n; i++) {
                    cout << "请输入第" << i << "本图书的书号，书名，价格：";
                    cin >> e.num >> e.name >> e.price;
                    listinsert(L, i, e);
                }
                cout << "计算机中已经保存的图书信息" << endl;
                cout << "书号  书名  价格" << endl;
                output(L);
                cout << endl;
                break;

            case 2:
                //插入图书信息
                cout << "请输入插入位置：";
                int k;
                cin >> k;
                cout << "请输入插入值（书号 书名 价格）：";
                cin >> e.num >> e.name >> e.price;
                listinsert(L, k, e);
                cout << "计算机中已经保存的图书信息：" << endl;
                cout << "书号  书名  价格" << endl;
                output(L);
                cout << endl;
                break;

            case 3:
                //删除图书信息
                cout << "删除第几个元素？";
                cin >> k;
                listdelete(L, k);
                cout << "计算机中已经保存的图书信息：" << endl;
                cout << "书号  书名  价格" << endl;
                output(L);
                cout << endl;
                break;

            case 4:
                //根据书名查询图书信息
                cout << "请输入要查询的书名：";
                cin >> e.name;
                Linklist p = locatename(L, e);
                if (p)
                    printf("%s %s %.2f\n", p->data.num, p->data.name, p->data.price);
                else
                    cout << "没找到！" << endl;
                cout << endl;
                break;
        }

    }

    return 0;
}
