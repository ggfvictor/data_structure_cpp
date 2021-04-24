//
// Created by ggfvi on 2021-04-24.
//舞伴问题
#include <iostream>
#include <string>

#define MAXQSIZE 100//列队可能达到的最大长度
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;

typedef struct {
    char name[20];
    char sex;//性别，‘F’表示女性，‘M’表示男性
} Person;

typedef struct {
    Person *base;//列队中的数据元素类型为Person
    int front;//头指针
    int rear;//尾指针
} SqQueue;

SqQueue Mdancers, Fdancers;//分别存放男士和女士入队者列队

int InitQueue(SqQueue &Q) {//构造一个空列队Q
    Q.base = new Person[MAXQSIZE];//为列队分配一个最大容量
    if (!Q.base)
        exit(OVERFLOW);//存储分配失败
    Q.front = Q.rear = 0;//头指针和尾指针置为零，列队为空
    return OK;
}

int EnQueue(SqQueue &Q, Person e) {//插入元素e为Q的新的队列
    if ((Q.rear + 1) % MAXQSIZE == Q.front)//尾指针再循环
        return ERROR;
    Q.base[Q.rear] = e;//新元素插入队尾
    Q.rear = (Q.rear + 1) % MAXQSIZE;//队尾指针+1
    return OK;
}

int QueueEmpty(SqQueue &Q) {
    if (Q.front == Q.rear)//队空
        return OK;
    else
        return ERROR;
}

int DeQueue(SqQueue &Q, Person &e) {//删除Q的队头元素，用e返回
    if (Q.front == Q.rear)
        return ERROR;//队空
    e = Q.base[Q.front];//保存队头元素
    Q.front = (Q.front + 1) % MAXQSIZE;//队头指针+1
    return OK;
}

Person GetHead(SqQueue Q) {//返回Q的队头元素，不修改队头指针
    if (Q.front != Q.rear)//列队非空
        return Q.base[Q.front];//返回队头元素的值
}


void DancePartner(Person dancer[], int num) {
    InitQueue((Mdancers));//男士列队初始化
    InitQueue((Fdancers));//女士列队初始化
    Person p;
    for (int i = 0; i < num; i++) {//依次将跳舞者根据其性别插入
        p = dancer[i];
        if (p.sex == 'F')
            EnQueue(Fdancers, p);//插入女队
        else
            EnQueue(Mdancers, p);//插入男队
    }
    cout << "The dancing partners are:" << endl;
    while (!QueueEmpty(Fdancers) && !QueueEmpty(Mdancers)) {
        DeQueue(Fdancers, p);//女士出队
        cout << p.name << "   ";//输出出队女士姓名
        DeQueue(Mdancers, p);//男士出队
        cout << p.name << endl;//输出出队男士姓名
    }
    if (QueueEmpty(Fdancers)) {
        p = GetHead(Fdancers);
        cout << "The first woman to get a partner is:" << p.name << endl;
        cout << p.name << endl;
    } else if (!QueueEmpty(Mdancers)) {
        p = GetHead(Mdancers);
        cout << "The first man to get a partner is:" << p.name << endl;
    }
}

int main() {
    Person dancer[MAXQSIZE];
    cout << "请输入跳舞的人数：";
    int num;
    cin >> num;
    cout << "请输入跳舞者的姓名和性别（男M,女F）:" << endl;
    for (int i = 1; i <= num; i++) {
        cin >> dancer[i - 1].name >> dancer[i - 1].sex;
        DancePartner(dancer, num);
        return 0;
    }
}
