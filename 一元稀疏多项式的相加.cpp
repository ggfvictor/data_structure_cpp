//一元稀疏多项式的相加.cpp
#include <iostream>
using namespace std;
#define MAXSIZE 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int status;

typedef struct{
	int coef;
	int expn;
}ElemType;//多项式非零项定义 

typedef struct{
	ElemType *elem;
	int length;
}sqlist;//多项式的顺序存储结构 


status initlist(sqlist &L){
	//顺序表的初始化；建立一个空的数组
	L.elem=new ElemType[MAXSIZE];
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	return OK;
}//时间复杂度O(1) 


status listinsert(sqlist &L,int i,ElemType e){
	//在顺序表L的第i个位置插入e，i从1开始到length+1
	if(i<1||i>L.length+1) return ERROR;
	if(L.length==MAXSIZE) return ERROR;
	for(int j=L.length-1;j>=i-1;j--)
		L.elem[j+1]=L.elem[j];
	L.elem[i-1]=e;
	L.length++;
	return OK;
} //时间复杂度O(n) 

status getelem(sqlist L,int i,ElemType &e){
	//取顺序表L的第i个值，i从1开始到length
	if(i<1||i>L.length+1) return ERROR;
	e=L.elem[i-1];
	return OK;
}//时间复杂度O(1) 

void padd(sqlist &L1,sqlist &L2,sqlist &L3){
	//两个多项式相加：L3=L2+L1
	int i=0,j=0,k=0;
	while(i<=L1.length-1&&j<=L2.length-1){
		if(L1.elem[i].expn==L2.elem[j].expn){
			L3.elem[k].coef=L1.elem[i].coef+L2.elem[j].coef;
			L3.elem[k].expn=L1.elem[i].expn;
			L3.length++;
			i++;
			j++;
			k++;
		}else{
			if(L1.elem[i].expn<L2.elem[j].expn){
				L3.elem[k].coef=L1.elem[i].coef;
				L3.elem[k].expn=L1.elem[i].expn;
				L3.length++;
				i++;
				k++;
			}else{
				L3.elem[k].coef=L2.elem[j].coef;
				L3.elem[k].expn=L2.elem[j].expn;
				L3.length++;
				j++;
				k++;
			}
		}
	}
	if(i==L1.length&&j<=L2.length-1){//L1已经结束，L2还没结束 
		for(int n=j;n<=L2.length-1;n++){//把L2的剩余部分追加到L3 
			L3.elem[k].expn=L2.elem[n].expn;
			L3.elem[k].coef=L2.elem[n].coef;
			L3.length++;
			k++;
		}
	}
	if(j==L2.length&&i<=L1.length-1){//L2已经结束，L1还没结束 
		for(int m=i;m<=L1.length-1;m++){//把L1的剩余部分追加到L3 
			L3.elem[k].expn=L1.elem[m].expn;
			L3.elem[k].coef=L1.elem[m].coef;
			L3.length++;
			k++;
		}
	}
} //时间复杂度O(n) 

int main(int argc, char *argv[])
{
	sqlist L1;
	initlist(L1);
	cout<<"请输入第一个多项式的项数：";
	int n;
	cin>>n;
	cout<<"请输入该多项式的系数和指数（不包含0项）：";
	for(int i=1;i<=n;i++){
		ElemType e;
		cin>>e.coef>>e.expn;
		listinsert(L1,i,e);
	} 
	cout<<" 该多项式是：";
	for(int i=1;i<=n;i++){
		ElemType e;
		getelem(L1,i,e);
		cout<<e.coef<<"x^"<<e.expn<<"+";
	} 
	cout<<endl;
	
	sqlist L2;
	initlist(L2);
	cout<<"请输入第二个多项式的项数：";
	int m;
	cin>>m;
	cout<<"请输入该多项式的系数和指数（不包含0项）：";
	for(int i=1;i<=m;i++){
		ElemType e;
		cin>>e.coef>>e.expn;
		listinsert(L2,i,e);
	} 
	cout<<"该多项式是：";
	for(int i=1;i<=m;i++){
		ElemType e;
		getelem(L2,i,e);
		cout<<e.coef<<"x^"<<e.expn<<"+";
	} 
	cout<<endl;
	
	sqlist L3;
	initlist(L3);
	padd(L1,L2,L3);
	cout<<"这两个多项式的和：";
	for(int i=1;i<=L3.length;i++){
		ElemType e;
		getelem(L3,i,e);
		cout<<e.coef<<"x^"<<e.expn<<"+";
	} 
	cout<<endl;
	return 0;
}
