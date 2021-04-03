//一元多项式的相加.cpp
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
}polynomial;//多项式非零项定义 

typedef struct{
	polynomial *elem;
	int length;
}sqlist;//多项式的顺序存储结构 


status initlist(sqlist &L){
	//顺序表的初始化；建立一个空的数组
	L.elem=new polynomial[MAXSIZE];
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	return OK;
}//时间复杂度O(1) 


status listinsert(sqlist &L,int i,polynomial e){
	//在顺序表L的第i个位置插入e，i从1开始到length+1
	if(i<1||i>L.length+1) return ERROR;
	if(L.length==MAXSIZE) return ERROR;
	for(int j=L.length-1;j>=i-1;j--)
		L.elem[j+1]=L.elem[j];
	L.elem[i-1]=e;
	L.length++;
	return OK;
} //时间复杂度O(n) 

status getelem(sqlist L,int i,polynomial &e){
	//取顺序表L的第i个值，i从1开始到length
	if(i<1||i>L.length+1) return ERROR;
	e=L.elem[i-1];
	return OK;
}//时间复杂度O(1) 

void padd(sqlist &L1,sqlist &L2,sqlist &L3){
	//两个多项式相加：L3=L2+L1
	if(L2.length>L1.length){
		L3.length=L2.length;
		for(int i=1;i<=L1.length;i++){
			L3.elem[i-1].coef=L1.elem[i-1].coef+L2.elem[i-1].coef;
		}
		for(int i=L1.length+1;i<=L2.length;i++){
			L3.elem[i-1]=L2.elem[i-1];
		}
	}else{
		for(int i=1;i<=L2.length;i++){
			L3.elem[i-1].coef=L1.elem[i-1].coef+L2.elem[i-1].coef;
		}
		for(int i=L2.length+1;i<=L1.length;i++){
			L3.elem[i-1]=L1.elem[i-1];
		}
		L3.length=L1.length;
	}
}//时间复杂度O(n) 

int main(int argc, char *argv[])
{
	sqlist L1;
	initlist(L1);
	cout<<"请输入第一个多项式的最高次幂：";
	int n;
	cin>>n;
	cout<<"请输入该多项式的系数（包含0项）：";
	for(int i=1;i<=n+1;i++){
		polynomial e;
		cin>>e.coef;
		listinsert(L1,i,e);
	} 
	cout<<"该多项式是：";
	for(int i=1;i<=n+1;i++){
		polynomial e;
		getelem(L1,i,e);
		cout<<e.coef<<"x^"<<(i-1)<<"+";
	} 
	cout<<endl;
	sqlist L2;
	initlist(L2);
	cout<<"请输入第二个多项式的最高次幂：";
	int m;
	cin>>m;
	cout<<"请输入该多项式的系数（包含0项）：";
	for(int i=1;i<=m+1;i++){
		polynomial e;
		cin>>e.coef;
		listinsert(L2,i,e);
	} 
	cout<<"该多项式是：";
	for(int i=1;i<=m+1;i++){
		polynomial e;
		getelem(L2,i,e);
		cout<<e.coef<<"x^"<<(i-1)<<"+";
	} 
	cout<<endl;
	sqlist L3;
	initlist(L3);
	padd(L1,L2,L3);
	cout<<"这两个多项式的和：";
	for(int i=1;i<=L3.length;i++){
		polynomial e;
		getelem(L3,i,e);
		cout<<e.coef<<"x^"<<(i-1)<<"+";
	} 
	cout<<endl;
	return 0;
}
