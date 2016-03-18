/*
*
*/

//********************************可把这些程序写入github***************/
//
// 1 //////***************************01-复杂度1 最大子列和问题
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

// 2 ///***************************01-复杂度2 Maximum Subsequence Sum
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

// 3 ///***************************02-线性结构1 一元多项式的乘法与加法运算
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode{
	int coef;  //系数
	int expon;  //指数
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
	P->coef = c;  //对新结点赋值
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
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //链表头空结点/
	P->link = NULL;
	Rear = P;
	while(N--){
		scanf("%d %d",&c,&e);
		Attach(c,e,&Rear);  //将当前项插入到多项式尾部/
	}
	t = P; P = P->link; free(t);  //删除临时生成的头结点/
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
	while(t2){  //先用P1的第一项乘以P2，得到P/
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

// 4 ///02-线性结构2 Reversing Linked List

// 5 ///02-线性结构3 Pop Sequence

// 6 ///********************************03-树1 树的同构****************
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
	if (R1 == Null && R2 == Null)   //两个树都为空
		return 1;
	if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null))  //其中一个为空
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

// 7 ///********************************03-树2 List Leaves*****
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

int BuildTree(struct TreeNode T[])  //构建树
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
		for (i = 0; i < N; i++)  //找到根结点
			if (!check[i]) break;
		Root = i;
	}
	return Root;
}

void LevelOrderTraversal(int RNode)  //采用队列层次遍历树
{
	int Queue[MaxTree],head,rear;
	int leaves = 0;
	head = rear = 0;
	Queue[rear++] = RNode;  //根结点入队
	while (rear - head){
		int node = Queue[head++];  //队首结点出队			
		if (T[node].left == -1 && T[node].Right == -1) {  //输出叶子结点
			if (leaves)
				printf(" ");
			printf("%d",node);
			leaves++;
		}
		if (T[node].left != -1) {  //如果存在，左儿子入队
			Queue[rear++] = T[node].left;
		}
		if (T[node].Right != -1) {  //如果存在，右儿子入队
			Queue[rear++] = T[node].Right;
		}
	}
}
*/

// 8 ///********************************03-树3 Tree Traversals Again*****

#include <stdio.h>

struct TNode{
	int tag;    //标记节点是第几次进栈
	int num;
};

//先序遍历对应进栈顺序，中序遍历对应出栈顺序；  
//后序遍历与中序遍历不同的是节点出栈后要马上再入栈（tag做第二次入栈标记），等右儿子遍历完后再出栈;  
//具体实现上，每次中序遍历的pop时，如果栈顶是标记过的节点（tag=2），循环弹出；如果没有标记过（tag=1）
//，做标记，即弹出再压栈,栈顶tag=2的节点对应中序遍历中已弹出的节点；循环弹出
//后碰到的第一个tag=1的节点才对应中序遍历当前pop的节点

int main()
{
	int N;
	int i,flag = 0;
	int size = 0; //栈元素大小，指向栈顶的下一个位置
	struct TNode stack[30]; 
	scanf("%d",&N);

	for (i = 0; i < (2 * N); i++) {
		char s[10];
		scanf("%s",s);
		if (s[1] == 'u') {  //push
			scanf("%d",&stack[size].num);  //入栈		
			stack[size].tag = 1;  //标记第一次入栈
			++size;
		}
		else {   //pop
			while (size > 0 && stack[size - 1].tag == 2) {   //循环弹出栈顶tag=2的节点
				if (flag)
					printf(" ");
				flag = 1;
				printf("%d",stack[--size].num);
			}
			if (size > 0)  //将中序遍历中应该要弹出的节点弹出再压栈，做标记即可
				stack[size - 1].tag = 2;
		}
	}
	while (size) {  //将栈中剩余节点依次弹出
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
