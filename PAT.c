/*
*
*/

//********************************�ɰ���Щ����д��github***************/
//
// 1 //////***************************01-���Ӷ�1 ������к�����
/*
#include <stdio.h>
#define MAXVAL 100000

int Subseqsum(int s[],int n);

int main()
{
	int n,i;
	int s[MAXVAL];
	scanf("%d",&n);
	for (i = 0; i < n; i++)
		scanf("%d",&s[i]);
	printf("%d\n",Subseqsum(s,n));
	return 0;
}

int Subseqsum(int s[],int n)
{
	int i,Thissum,Maxsum = 0;
	for(i = 0; i < n; i++)
	{
		Thissum += s[i];
		if(Thissum > Maxsum)
			Maxsum = Thissum;
		else if(Thissum < 0)
			Thissum = 0;
	}
	return Maxsum;
}
*/

// 2 ///***************************01-���Ӷ�2 Maximum Subsequence Sum
/*
#include <stdio.h>
int main()
{
  int k;
  scanf("%d", &k);
  int head = 0;
  int tail = k - 1;
  int this_sum = 0;
  int max_sum = 0;
  int i,a[k];
  int h = 0;
  int flag = 1;
  for (i = 0; i < k; i++)
  {
    scanf("%d",&a[i]);
    this_sum += a[i];
    if (a[i] >= 0 && flag == 0)
    {
      h = i;
      flag = 1;
    }
    if (this_sum > max_sum ||
        this_sum == 0 && max_sum == 0 && i <= tail)
    {
      max_sum = this_sum;
      head = h;
      tail = i;
    }else if (this_sum < 0)
    {
      this_sum = 0;
      flag = 0;
    }
  }
  printf("%d %d %d\n", max_sum, a[head], a[tail]);
  return 0;
}
*/

// 3 ///***************************02-���Խṹ1 һԪ����ʽ�ĳ˷���ӷ�����
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode{
	int coef;  //ϵ��
	int expon;  //ָ��
	Polynomial link;
};
Polynomial ReadPoly();
Polynomial Mult(Polynomial p1,Polynomial p2);
void PrintPoly(Polynomial p);
Polynomial Add(Polynomial p1,Polynomial p2);

int main()
{
	Polynomial P1,P2,PP,PS;
	P1 = ReadPoly();
	P2 = ReadPoly();
	PP = Mult(P1,P2);
	PrintPoly(PP);
	PS = Add(P1,P2);
	PrintPoly(PS);

	return 0;
}

void Attach(int c,int e,Polynomial *pRear)
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;  //���½�㸳ֵ
	P->expon = e;
	P->link = NULL;
	(*pRear)->link = P;
	*pRear = P;
}
Polynomial ReadPoly()
{
	Polynomial P,Rear,t;
	int c,e,N;

	scanf("%d",&N);
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //����ͷ�ս��/
	P->link = NULL;
	Rear = P;
	while(N--){
		scanf("%d %d",&c,&e);
		Attach(c,e,&Rear);  //����ǰ����뵽����ʽβ��/
	}
	t = P; P = P->link; free(t);  //ɾ����ʱ���ɵ�ͷ���/
	return P;
}
Polynomial Add(Polynomial P1,Polynomial P2)
{
	Polynomial t1,t2,Rear,P;
	int sum;
	t1 = P1; t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while(t1 && t2){
		if (t1->expon == t2->expon){
			sum = t1->coef + t2->coef;
			if(sum)
				Attach(sum,t1->expon,&Rear);
			t1 = t1->link;
			t2 = t2->link;
			
		}
		else if(t1->expon > t2->expon){
			Attach(t1->coef,t1->expon,&Rear);
			t1= t1->link;
		}
		else{
			Attach(t2->coef,t2->expon,&Rear);
			t2 = t2->link;
		}
	}
	while(t1){
		Attach(t1->coef,t1->expon,&Rear);
		t1 = t1->link;
	}
	while(t2){
		Attach(t2->coef,t2->expon,&Rear);
		t2 = t2->link;
	}
	t2 = P; P = P->link; free(t2);
	return P;
}
Polynomial Mult(Polynomial P1,Polynomial P2)
{
	Polynomial P,Rear,t1,t2,t;
	int e,c;

	if(!P1 || !P2) return NULL;

	t1 = P1; t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while(t2){  //����P1�ĵ�һ�����P2���õ�P/
		Attach(t1->coef * t2->coef,t1->expon + t2->expon,&Rear);
		t2 = t2->link;
	}
	t1 = t1->link;
	while(t1){
		t2 = P2; Rear = P;
		while(t2){
			e = t1->expon + t2->expon;
			c = t1->coef * t2->coef;
			while(Rear->link && Rear->link->expon > e)
				Rear = Rear->link;
			 if(Rear->link && Rear->link->expon == e){
			 	if(Rear->link->coef + c)
					Rear->link->coef += c;
				else{
					t = Rear->link;
					Rear->link = t->link;
					free(t);
				}
			 }
			 else {
			 	t = (Polynomial)malloc(sizeof(struct PolyNode));
			 	t->coef = c; t->expon = e;
			 	t->link = Rear->link;
			 	Rear->link = t; Rear = Rear->link;
			 }
			t2 = t2->link;
		}
		t1 = t1->link;
	}
	t2 = P; P = P->link; free(t2);
	return P;
}
void PrintPoly(Polynomial P)
{
	int flag;
	flag = 0;
	if(!P) { printf("0 0\n"); return; }

	while(P){
		if(!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d",P->coef,P->expon);
		P = P->link;
	}
	printf("\n");
}
*/

// 4 ///02-���Խṹ2 Reversing Linked List

// 5 ///02-���Խṹ3 Pop Sequence

// 6 ///********************************03-��1 ����ͬ��****************
/*
#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode{
	ElementType Element;
	Tree left;
	Tree Right;
}T1[MaxTree], T2[MaxTree];




int main()
{
	int BuildTree(struct TreeNode T[]);
	int Isomorphic(Tree, Tree);

	Tree R1;
	Tree R2;

	R1 = BuildTree(T1);
	R2 = BuildTree(T2);
	if(Isomorphic(R1,R2))
		printf("Yes\n");
	else 
		printf("No\n");
	return 0;
}

int BuildTree(struct TreeNode T[])
{
	char cl,cr;
	int N,i;
	int check[MaxTree];
	int Root = Null;
	scanf("%d\n",&N);
	if(N){
		for ( i = 0; i < N; i++) check[i] = 0;
		for ( i = 0; i < N; i++){
			scanf("%c %c %c\n",&T[i].Element,&cl,&cr);
			if (cl != '-'){
				T[i].left = cl - '0';
				check[T[i].left] = 1;
			}
			else 
				T[i].left = Null;
			if (cr != '-'){
				T[i].Right = cr - '0';
				check[T[i].Right] = 1;
			}
			else 
				T[i].Right = Null;
		}
		for (i = 0; i < N; i++)
			if (!check[i]) break;
		Root = i;
	}
	return Root;
}

int Isomorphic(Tree R1, Tree R2)
{
	if (R1 == Null && R2 == Null)   //��������Ϊ��
		return 1;
	if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null))  //����һ��Ϊ��
		return 0;
	if (T1[R1].Element != T2[R2].Element)
		return 0;
	if (T1[R1].left == Null && T2[R2].left == Null)
		return Isomorphic(T1[R1].Right,T2[R2].Right);
	if ( ((T1[R1].left != Null) && (T2[R2].left != Null)) &&
		((T1[T1[R1].left].Element) == (T2[T2[R2].left].Element)) )
		return (Isomorphic(T1[R1].left,T2[R2].left) && Isomorphic(T1[R1].Right,T2[R2].Right));
	else
		return (Isomorphic(T1[R1].left,T2[R2].Right) && Isomorphic(T1[R1].Right,T2[R2].left));
}
*/

// 7 ///********************************03-��2 List Leaves*****
/*
#include <stdio.h>

#define MaxTree 10
//#define ElementType int
#define Tree int
#define Null -1

struct TreeNode{
	Tree left;
	Tree Right;
}T[MaxTree];

int main()
{
	int BuildTree(struct TreeNode T[]);
	void LevelOrderTraversal(int RNode);

	Tree R1;
	R1 = BuildTree(T);
	LevelOrderTraversal(R1);
	return 0;
}

int BuildTree(struct TreeNode T[])  //������
{
	char cl,cr;
	int N,i;
	int check[MaxTree];
	int Root = Null;
	scanf("%d",&N);
	if(N){
        for ( i = 0; i < N; i++) check[i] = 0;
		for ( i = 0; i < N; i++){
			scanf("\n%c %c",&cl,&cr);
			if (cl != '-'){
				T[i].left = cl - '0';
				check[T[i].left] = 1;
			}
			else 
				T[i].left = Null;
			if (cr != '-'){
				T[i].Right = cr - '0';
				check[T[i].Right] = 1;
			}
			else 
				T[i].Right = Null;
		}
		for (i = 0; i < N; i++)  //�ҵ������
			if (!check[i]) break;
		Root = i;
	}
	return Root;
}

void LevelOrderTraversal(int RNode)  //���ö��в�α�����
{
	int Queue[MaxTree],head,rear;
	int leaves = 0;
	head = rear = 0;
	Queue[rear++] = RNode;  //��������
	while (rear - head){
		int node = Queue[head++];  //���׽�����			
		if (T[node].left == -1 && T[node].Right == -1) {  //���Ҷ�ӽ��
			if (leaves)
				printf(" ");
			printf("%d",node);
			leaves++;
		}
		if (T[node].left != -1) {  //������ڣ���������
			Queue[rear++] = T[node].left;
		}
		if (T[node].Right != -1) {  //������ڣ��Ҷ������
			Queue[rear++] = T[node].Right;
		}
	}
}
*/

// 8 ///********************************03-��3 Tree Traversals Again*****

#include <stdio.h>

struct TNode{
	int tag;    //��ǽڵ��ǵڼ��ν�ջ
	int num;
};

//���������Ӧ��ջ˳�����������Ӧ��ջ˳��  
//������������������ͬ���ǽڵ��ջ��Ҫ��������ջ��tag���ڶ�����ջ��ǣ������Ҷ��ӱ�������ٳ�ջ;  
//����ʵ���ϣ�ÿ�����������popʱ�����ջ���Ǳ�ǹ��Ľڵ㣨tag=2����ѭ�����������û�б�ǹ���tag=1��
//������ǣ���������ѹջ,ջ��tag=2�Ľڵ��Ӧ����������ѵ����Ľڵ㣻ѭ������
//�������ĵ�һ��tag=1�Ľڵ�Ŷ�Ӧ���������ǰpop�Ľڵ�

int main()
{
	int N;
	int i,flag = 0;
	int size = 0; //ջԪ�ش�С��ָ��ջ������һ��λ��
	struct TNode stack[30]; 
	scanf("%d",&N);

	for (i = 0; i < (2 * N); i++) {
		char s[10];
		scanf("%s",s);
		if (s[1] == 'u') {  //push
			scanf("%d",&stack[size].num);  //��ջ		
			stack[size].tag = 1;  //��ǵ�һ����ջ
			++size;
		}
		else {   //pop
			while (size > 0 && stack[size - 1].tag == 2) {   //ѭ������ջ��tag=2�Ľڵ�
				if (flag)
					printf(" ");
				flag = 1;
				printf("%d",stack[--size].num);
			}
			if (size > 0)  //�����������Ӧ��Ҫ�����Ľڵ㵯����ѹջ������Ǽ���
				stack[size - 1].tag = 2;
		}
	}
	while (size) {  //��ջ��ʣ��ڵ����ε���
		if (flag)
			printf(" ");
		flag = 1;
		printf("%d",stack[--size].num);
	}
	return 0;
}

/*
#include <stdio.h>
int main()
{
	int i = 0;
	printf("%d",i);
	return 0;
}
*/
