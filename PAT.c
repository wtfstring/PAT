/*
*
*/
//********************************å¯æŠŠè¿™äº›ç¨‹åºå†™å…¥github***************/
//
// 1 //////***************************01-å¤æ‚åº¦1 æœ€å¤§å­åˆ—å’Œé—®é¢˜
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

// 2 ///***************************01-å¤æ‚åº¦2 Maximum Subsequence Sum
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

// 3 ///***************************02-çº¿æ€§ç»“æ„1 ä¸€å…ƒå¤šé¡¹å¼çš„ä¹˜æ³•ä¸åŠ æ³•è¿ç®—
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode{
	int coef;  //ç³»æ•°
	int expon;  //æŒ‡æ•°
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
	P->coef = c;  //å¯¹æ–°ç»“ç‚¹èµ‹å€¼
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
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //é“¾è¡¨å¤´ç©ºç»“ç‚¹/
	P->link = NULL;
	Rear = P;
	while(N--){
		scanf("%d %d",&c,&e);
		Attach(c,e,&Rear);  //å°†å½“å‰é¡¹æ’å…¥åˆ°å¤šé¡¹å¼å°¾éƒ¨/
	}
	t = P; P = P->link; free(t);  //åˆ é™¤ä¸´æ—¶ç”Ÿæˆçš„å¤´ç»“ç‚¹/
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
	while(t2){  //å…ˆç”¨P1çš„ç¬¬ä¸€é¡¹ä¹˜ä»¥P2ï¼Œå¾—åˆ°P/
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

<<<<<<< HEAD
// 4 ///***************************02-ÏßĞÔ½á¹¹2 Reversing Linked List.......
//...³ö×Ôhttp://blog.csdn.net/ice_camel/article/details/45156245
//³éÏóµÄÁ´±í°üÀ¨Á½²¿·Ö£ºÓĞ¿éµØ·½´æÊı¾İ£¬ÓĞ¿éµØ·½´æÖ¸Õë¡ª¡ªÏÂÒ»¸ö½áµãµÄµØÖ·
/*
#include <stdio.h>
#define MAX 100000
typedef struct {
	int data;
	int next;
}Node;
int CountNodes(Node *list,int pList);  
int ReverseK(Node *list,int pList,int n,int k);  //Äæ×ªÁ´±í£¬·µ»Øµ¥Á´±íµÄÍ·½áµã
void printfList(Node *list,int pNewList);  //´òÓ¡µ¥Á´±í

int main()
{
	int num,pNewList;
	int pList,n,k,i;  //pList´æ·ÅµÚÒ»¸ö½áµãµÄµØÖ·
	int addr,data,next;  //´æ·ÅÊı×éÏÂ±ê(±¾½áµãµÄµØÖ·)£¬½áµãÖĞµÄÊı¾İ¡¢ÏÂÒ»¸ö½áµãµØÖ·
	Node list[MAX];

	scanf("%d%d%d",&pList,&n,&k);
	for (i = 0; i < n; i++) {
		scanf("%d%d%d",&addr,&data,&next);
		list[addr].data = data;
		list[addr].next = next;
	}
	num = CountNodes(list,pList);  //ÒòÊäÈëÖĞÓĞÎŞĞ§µÄ½áµã£¬ĞèÒªÏÈ¼ÆËãµ¥Á´±íµÄ×Ü½áµãÊı
	pNewList = ReverseK(list,pList,num,k);
	printfList(list,pNewList);

	return 0;
}
//¼ÇÂ¼µ¥Á´±íµÄ½áµãÊı
int CountNodes(Node *list,int pList)
{
	int cnt = 1;
	while ((pList = list[pList].next) != -1)
		cnt++;
	return cnt;
}
//Äæ×ªÁ´±í£¬·µ»Øµ¥Á´±íµÄÍ·½áµãµÄµØÖ·
int ReverseK(Node *list,int pList,int n,int k)
{
	int prevNode,currNode,nextNode;  //ĞèÒªÁ¬½ÓµÄÇ°Ò»¸ö½áµã¡¢µ±Ç°½áµã¡¢ºóÒ»¸ö½áµã
	int i,j,lastHead,head = -1;
	prevNode = -1;
	currNode = pList;
	nextNode = list[currNode].next;
	for (i = 0; i < n / k; i++) {  //·ÖÎªn/k¶Î·Ö±ğÄæ×ª£¬Ã¿¶ÎK¸ö½Úµã
		lastHead = head;  //¼ÇÂ¼Ç°Ò»¶ÎµÄ£¨Î´Äæ×ªµÄ£©Í·½áµã£¬ÒÔ±ãÁ¬½Óµ½µ±Ç°¶ÎµÄ£¨Î´Äæ×ªµÄ)Î²½Úµã
		head = currNode;  //¼ÇÂ¼µ±Ç°¶ÎµÄÍ·½áµã
		for (j = 0; j < k; j++) {
			list[currNode].next = prevNode;
			prevNode = currNode;
			currNode = nextNode;
			nextNode = list[nextNode].next;
		}
		if (i == 0)  //µÚÒ»¶ÎÄæ×ªºóµÄÍ·½áµã½«×÷Îª±íÍ··µ»Ø
			pList = prevNode;
		else  //Á¬½ÓÄæ×ªºóµÄÇ°ºóÁ½¶Î
			list[lastHead].next = prevNode;
	}
	list[head].next = currNode;

	return pList;
}
//´òÓ¡Á´±í
void printfList(Node *list,int p)
{
	while((p = list[p].next) != -1) {
		printf("%05d %d %d\n",p,list[p].data,list[p].next);
	}
	printf("05%d %d %d\n",p,list[p].data,list[p].next);
}
*/
=======
// 4 ///02-çº¿æ€§ç»“æ„2 Reversing Linked List
>>>>>>> 01cd58e18f2e6151da3c58cda226fe5a571806a4

// 5 ///02-çº¿æ€§ç»“æ„3 Pop Sequence

// 6 ///********************************03-æ ‘1 æ ‘çš„åŒæ„****************
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
	if (R1 == Null && R2 == Null)   //ä¸¤ä¸ªæ ‘éƒ½ä¸ºç©º
		return 1;
	if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null))  //å…¶ä¸­ä¸€ä¸ªä¸ºç©º
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

// 7 ///********************************03-æ ‘2 List Leaves*****
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

int BuildTree(struct TreeNode T[])  //æ„å»ºæ ‘
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
		for (i = 0; i < N; i++)  //æ‰¾åˆ°æ ¹ç»“ç‚¹
			if (!check[i]) break;
		Root = i;
	}
	return Root;
}

void LevelOrderTraversal(int RNode)  //é‡‡ç”¨é˜Ÿåˆ—å±‚æ¬¡éå†æ ‘
{
	int Queue[MaxTree],head,rear;
	int leaves = 0;
	head = rear = 0;
	Queue[rear++] = RNode;  //æ ¹ç»“ç‚¹å…¥é˜Ÿ
	while (rear - head){
		int node = Queue[head++];  //é˜Ÿé¦–ç»“ç‚¹å‡ºé˜Ÿ			
		if (T[node].left == -1 && T[node].Right == -1) {  //è¾“å‡ºå¶å­ç»“ç‚¹
			if (leaves)
				printf(" ");
			printf("%d",node);
			leaves++;
		}
		if (T[node].left != -1) {  //å¦‚æœå­˜åœ¨ï¼Œå·¦å„¿å­å…¥é˜Ÿ
			Queue[rear++] = T[node].left;
		}
		if (T[node].Right != -1) {  //å¦‚æœå­˜åœ¨ï¼Œå³å„¿å­å…¥é˜Ÿ
			Queue[rear++] = T[node].Right;
		}
	}
}
*/

<<<<<<< HEAD
// 8 ///********************************03-Ê÷3 Tree Traversals Again*****
/*
=======
// 8 ///********************************03-æ ‘3 Tree Traversals Again*****

>>>>>>> 01cd58e18f2e6151da3c58cda226fe5a571806a4
#include <stdio.h>

struct TNode{
	int tag;    //æ ‡è®°èŠ‚ç‚¹æ˜¯ç¬¬å‡ æ¬¡è¿›æ ˆ
	int num;
};

//å…ˆåºéå†å¯¹åº”è¿›æ ˆé¡ºåºï¼Œä¸­åºéå†å¯¹åº”å‡ºæ ˆé¡ºåºï¼›  
//ååºéå†ä¸ä¸­åºéå†ä¸åŒçš„æ˜¯èŠ‚ç‚¹å‡ºæ ˆåè¦é©¬ä¸Šå†å…¥æ ˆï¼ˆtagåšç¬¬äºŒæ¬¡å…¥æ ˆæ ‡è®°ï¼‰ï¼Œç­‰å³å„¿å­éå†å®Œåå†å‡ºæ ˆ;  
//å…·ä½“å®ç°ä¸Šï¼Œæ¯æ¬¡ä¸­åºéå†çš„popæ—¶ï¼Œå¦‚æœæ ˆé¡¶æ˜¯æ ‡è®°è¿‡çš„èŠ‚ç‚¹ï¼ˆtag=2ï¼‰ï¼Œå¾ªç¯å¼¹å‡ºï¼›å¦‚æœæ²¡æœ‰æ ‡è®°è¿‡ï¼ˆtag=1ï¼‰
//ï¼Œåšæ ‡è®°ï¼Œå³å¼¹å‡ºå†å‹æ ˆ,æ ˆé¡¶tag=2çš„èŠ‚ç‚¹å¯¹åº”ä¸­åºéå†ä¸­å·²å¼¹å‡ºçš„èŠ‚ç‚¹ï¼›å¾ªç¯å¼¹å‡º
//åç¢°åˆ°çš„ç¬¬ä¸€ä¸ªtag=1çš„èŠ‚ç‚¹æ‰å¯¹åº”ä¸­åºéå†å½“å‰popçš„èŠ‚ç‚¹

int main()
{
	int N;
	int i,flag = 0;
	int size = 0; //æ ˆå…ƒç´ å¤§å°ï¼ŒæŒ‡å‘æ ˆé¡¶çš„ä¸‹ä¸€ä¸ªä½ç½®
	struct TNode stack[30]; 

	scanf("%d",&N);
	for (i = 0; i < (2 * N); i++) {
		char s[10];
		scanf("%s",s);
		if (s[1] == 'u') {  //push
			scanf("%d",&stack[size].num);  //å…¥æ ˆ		
			stack[size].tag = 1;  //æ ‡è®°ç¬¬ä¸€æ¬¡å…¥æ ˆ
			++size;
		}
		else {   //pop
			while (size > 0 && stack[size - 1].tag == 2) {   //å¾ªç¯å¼¹å‡ºæ ˆé¡¶tag=2çš„èŠ‚ç‚¹
				if (flag)
					printf(" ");
				flag = 1;
				printf("%d",stack[--size].num);
			}
			if (size > 0)  //å°†ä¸­åºéå†ä¸­åº”è¯¥è¦å¼¹å‡ºçš„èŠ‚ç‚¹å¼¹å‡ºå†å‹æ ˆï¼Œåšæ ‡è®°å³å¯
				stack[size - 1].tag = 2;
		}
	}
	while (size) {  //å°†æ ˆä¸­å‰©ä½™èŠ‚ç‚¹ä¾æ¬¡å¼¹å‡º
		if (flag)
			printf(" ");
		flag = 1;
		printf("%d",stack[--size].num);
	}
	return 0;
}
*/

// 9 ///********************************04-Ê÷4 ÊÇ·ñÍ¬Ò»¿Ã¶ş²æËÑË÷Ê÷
//ËÑË÷Ê÷µÄ±íÊ¾£¬½¨ËÑË÷Ê÷£¬ÅĞ±ğÒ»ĞòÁĞÊÇ·ñÓëËÑË÷Ê÷TÒ»ÖÂ
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode {
	int v;
	Tree Left,Right;
	int flag;
};

Tree MakeTree(int N);
int Judge(Tree T,int N);
int check(Tree T,int V);
Tree NewNode(int V);
Tree Insert(Tree T,int V);
void ResetT(Tree T);
void FreeTree(Tree T);

int main()
{
	int N,L,i;  //NºÍL£¬·Ö±ğÊÇÃ¿¸öĞòÁĞ²åÈëÔªËØµÄ¸öÊıºÍĞèÒª¼ì²éµÄĞòÁĞ¸öÊı
	Tree T;

	scanf("%d",&N);
	while (N) {
		scanf("%d",&L);
		T = MakeTree(N);
		for (i = 0; i < L; i++) {
			if (Judge(T,N)) printf("Yes\n");
			else printf("No\n");
			ResetT(T);  //Çå³ıTÖĞµÄ±ê¼Çflag
		}
		FreeTree(T);
		scanf("%d",&N);
	}
	return 0;
}

Tree MakeTree(int N)
{
	Tree T;
	int i,V;
	scanf("%d",&V);
	T = NewNode(V);
	for (i = 1; i < N; i++) {
		scanf("%d",&V);
		T = Insert(T,V);
	}
	return T;
}

Tree NewNode(int V)
{
	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->v = V;
	T->Left = T->Right = NULL;
	T->flag = 0;
	return T;
}

Tree Insert(Tree T,int V)
{
	if (!T)  T = NewNode(V);
	else {
		if (V > T->v)
			T->Right = Insert(T->Right,V);
		else
			T->Left = Insert(T->Left,V);
	}
	return T;
}

int Judge(Tree T,int N)
{
	int i,V,flag = 0;  //flag:0´ú±íÄ¿Ç°»¹Ò»ÖÂ,1´ú±íÒÑ¾­²»Ò»ÖÂ
	scanf("%d",&V);
	if (V != T->v) flag = 1;
	else T->flag = 1;
	for (i = 1; i < N; i++) {
		scanf("%d",&V);
		if ((!flag) && (!check(T,V))) flag = 1;
	}
	if (flag) return 0;
	else return 1;
}

int check(Tree T,int V)
{
	if (T->flag) {
		if (V < T->v) return check(T->Left,V);
		else if (V > T->v) return check(T->Right,V);
		else return 0;
	}
	else {
		if (V == T->v) {
			T->flag = 1;
			return 1;
		}
		else return 0;
	}
}

void ResetT(Tree T) //Çå³ıTÖĞ¸÷½áµãµÄflagµÄ±ê¼Ç
{
	if (T->Left) ResetT(T->Left);
	if (T->Right) ResetT(T->Right);
	T->flag = 0;
}

void FreeTree(Tree T)  //ÊÍ·ÅTµÄ¿Õ¼ä
{
	if (T->Left) FreeTree(T->Left);
	if (T->Right) FreeTree(T->Right);
	free(T);
}
