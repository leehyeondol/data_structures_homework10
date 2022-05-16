#include <stdio.h>
#include <stdlib.h>

typedef struct node {//노드 구조체 생성
	int key;//키 입력 받을 변수
	struct node *left;//왼쪽 노드
	struct node *right;//오른쪽 노드
} Node;

/* for stack */
#define MAX_STACK_SIZE		20//맥스스택사이즈 20
Node* stack[MAX_STACK_SIZE];//포인터 구조체 20칸생성
int top = -1;//top을 표현하는 변수 생성

Node* pop();//pop하는 함수
void push(Node* aNode);//push하는 함수

/* for queue */
#define MAX_QUEUE_SIZE		20//맥스큐사이즈 20
Node* queue[MAX_QUEUE_SIZE];//포이터 구조체 큐 20칸 생성
int front = -1;//front를 가리키는 변수
int rear = -1;//rear를 가리키는 변수

Node* deQueue();//큐 삭제하는 함수
void enQueue(Node* aNode);//큐에 입력하는 함수


int initializeBST(Node** h);//초기화하는 함수


void recursiveInorder(Node* ptr);//재귀적 중위 순회 함수
void iterativeInorder(Node* ptr);//반복적 중위 순회 함수
void levelOrder(Node* ptr);//레벨 순서 순회 함수
int insert(Node* head, int key);//입력
int deleteNode(Node* head, int key);//삭제 
int freeBST(Node* head);//메모리 초기화

void printStack();//스텍 출력

int main()
{
    printf("[----- [Lee hyeondo]  [2019038085] -----]\n");//이름 학번 출력
	char command;//커멘드 입력변수
	int key;//키 입력 변수
	Node* head = NULL;// 헤드노드 초기화

	do{//while의 조건에 따라 반복
		printf("\n\n");//메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//커멘드 입력

		switch(command) {//커멘드에 따라 동작
		case 'z': case 'Z'://z면
			initializeBST(&head);//이진 트리 초기화
			break;
		case 'q': case 'Q'://q면
			freeBST(head);//메모리 해제
			break;
		case 'i': case 'I'://u면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력받아서
			insert(head, key);//노드로 입력
			break;
		case 'd': case 'D'://d면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력받아서
			deleteNode(head, key);//키값에 해당하는 노드 삭제
			break;

		case 'r': case 'R'://r면
			recursiveInorder(head->left);//재귀적 중위순회 함수 호출
			break;
		case 't': case 'T'://t면
			iterativeInorder(head->left);//반복적 중위 순회 함수 호출
			break;

		case 'l': case 'L'://l면
			levelOrder(head->left);//레벨 순회 함수 호출
			break;

		case 'p': case 'P'://p면
			printStack();
			break;

		default://모두 아니면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//집중 출력
			break;
		}

	}while(command != 'q' && command != 'Q');//q가 아니면 다시 반복

	return 1;//종료
}

int initializeBST(Node** h) {//초기화 함수

	if(*h != NULL)//비어있지 않으면
		freeBST(*h);//초기화

	*h = (Node*)malloc(sizeof(Node));//헤드노드 동적할당
	(*h)->left = NULL;	/* root *///왼쪽은 NULL
	(*h)->right = *h;//오른쪽은 헤드노드
	(*h)->key = -9999;//키는 -9999

	top = -1;//탑은 -1

	front = rear = -1;//front와 rear은 -1

	return 1;
}



void recursiveInorder(Node* ptr)//재귀적 중위 순회 함수
{
	if(ptr) {//ptr이 NULL이 아니면
		recursiveInorder(ptr->left);//왼쪽 노드를 입력하고 다시 함수 호출
		printf(" [%d] ", ptr->key);//키 출력
		recursiveInorder(ptr->right);//오른쪽 노드를 입력하고 다시 함수 호출
	}
}

void iterativeInorder(Node* node)//반족적 중위 순회 함수
{
	for(;;)//반복
	{
		for(; node; node = node->left)//node를 왼쪽으로 한칸씩 이동하며 반복
			push(node);//노드 입력
		node = pop();//왼쪽노드가 빈 노드까지 입력했으면 마지막 노드 하나 pop

		if(!node) break;//노드가 없으면
		printf(" [%d] ", node->key);//노드 출력

		node = node->right;//노드 오른쪽으로 이동
	}
}
 

void levelOrder(Node* ptr)//레벨 순회 방식
{

	if(!ptr) return;//ptr이 비어있으면

	enQueue(ptr);//ptr입력

	for(;;)//반복
	{
		ptr = deQueue();//ptr 하나 삭제
		if(ptr) {//ptr이 없지 않은동안
			printf(" [%d] ", ptr->key);//ptr의 키 출력

			if(ptr->left)//ptr의 왼쪽이 있으면
				enQueue(ptr->left);//ptr의 왼쪽 입력
			if(ptr->right)//ptr의 왼쪽이 있으면
				enQueue(ptr->right);//ptr의 왼쪽 입력
		}
		else//아니면
			break;//종료

	}

}


int insert(Node* head, int key)//노드 입력 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));//노드 동적할당
	newNode->key = key;//노드의 키 입력
	newNode->left = NULL;//노드의 왼쪽 노드 0
	newNode->right = NULL;//오른쪽 노드 0

	if (head->left == NULL) {//왼쪽노드가 없으면
		head->left = newNode;//왼쪽노드에 새 노드 입력
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr은 헤드의 왼쪽 노드

	Node* parentNode = NULL;//부모노드는 0
	while(ptr != NULL) {//ptr이 0이 아닌동안

	
		if(ptr->key == key) return 1;//키가 입력받은 키와 같으면 리턴
		parentNode = ptr;//부모노드에 ptr 입력

		if(ptr->key < key)//키가 입력받은 키보다 작으면
			ptr = ptr->right;//ptr은 오른쪽으로 이동
		else
			ptr = ptr->left;//아니면 왼쪽으로 이동
	}

	if(parentNode->key > key)//부모노드의 키보다 입력받은 키가 작으면
		parentNode->left = newNode;//왼쪽에 입력받은 노드 입력
	else//아니면
		parentNode->right = newNode;//오른쪽에 입력받은 노드 입력
	return 1;
}


int deleteNode(Node* head, int key)//삭제 함수
{
	if (head == NULL) {//헤드가 비어있으면
		printf("\n Nothing to delete!!\n");//삭제할게 없음 출력
		return -1;
	}

	if (head->left == NULL) {//헤드 뿐이면
		printf("\n Nothing to delete!!\n");//삭제 할게 없음
		return -1;
	}

	Node* root = head->left;//루트 노드 생성 및 헤드의 왼쪽노드로 초기화

	Node* parent = NULL;//parent 초기화
	Node* ptr = root;//ptr노드에 루트 노드 입력

	while((ptr != NULL)&&(ptr->key != key)) {//ptr이 비어있고 ptr의 키가 입력받은 키가 아닐때까지
		if(ptr->key != key) {//ptr의 키가  입력받은 키가 아니면

			parent = ptr;//parent에 ptr입력

			if(ptr->key > key)//ptr의 키가 입력받은 키보다 크면
				ptr = ptr->left;//ptr은 왼쪽 노드로 이동
			else//아니면
				ptr = ptr->right;//ptr의 오른쪽으로 이동
		}
	}


	if(ptr == NULL)//ptr이 비어있ㅇ,면
	{
		printf("No node for key [%d]\n ", key);//키가 없음 출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)//ptr의 자식노드가 비어있으면
	{
		if(parent != NULL) { // parent가 비어있지 않으면/* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)//parant의 왼쪽 노드가 ptr이면
				parent->left = NULL;//삭제
			else//아니면
				parent->right = NULL;//오른쪽 삭제
		} else {//parent가 비어있으면
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;//첫 노드 삭제

		}

		free(ptr);//ptr 메모리 초기화
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))//ptr의 왼쪽이 비어있거나 오른쪽이 비어있으면
	{
		Node* child;//자식노드 생성
		if (ptr->left != NULL)//ptr의 왼쪽노드가 비어있으면
			child = ptr->left;//자식노드에 ptr의 왼쪽 노드 입력
		else//아니면
			child = ptr->right;//자식노드에 오른쪽 노드 입력

		if(parent != NULL)//만약 parent가 비어있지 않으면
		{
			if(parent->left == ptr)//만약 parent의 왼쪽 노드가 ptr이면
				parent->left = child;//왼쪽 노드에 자식노드 입력
			else//아니면
				parent->right = child;//오른쪽 노드에 자식노드 입력
		} else {//parent가 비어있지 않으면
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;//루트노드에 자식노드 입력
		}

		free(ptr);//ptr 초기화
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;//candidate 생성
	parent = ptr;//부모노드에 ptr입력


	candidate = ptr->right;//candidate에 ptr의 오른쪽 노드 입력

	while(candidate->left != NULL)//candidate의 왼쪽 노드가 비어있지 않은동안
	{
		parent = candidate;//부모노드에 candidate노드 입력
		candidate = candidate->left;//candidate노드 한칸 이동
	}

	if (parent->right == candidate)//부모의 오른쪽 노드가 candidate이면
		parent->right = candidate->right;//부모의 오른쪽 노드에 candidate의 오른쪽 노드 입력
	else//아니면
		parent->left = candidate->right;//왼쪽에 입력

	ptr->key = candidate->key;//ptr의 키에 candidate의 키 입력

	free(candidate);//candidate 메모리 초기화
	return 1;
}


void freeNode(Node* ptr)//노드 메모리 초기화 함수
{
	if(ptr) {//ptr에 값이 있으면
		freeNode(ptr->left);//ptr의 왼쪽노드 메모리 해제
		freeNode(ptr->right);//ptr의 오른쪽 노드 메모리 해제
		free(ptr);//ptr의 메모리 해제
	}
}

int freeBST(Node* head)//메모리 해제 함수
{

	if(head->left == head)//헤드 하나뿐이면
	{
		free(head);//헤드노드의 메모리 해제
		return 1;
	}

	Node* p = head->left;//노드 p는 헤드노드의 다음노드

	freeNode(p);//p의 메모리 해제

	free(head);//헤드 메모리 해제
	return 1;
}



Node* pop()//pop 함수
{
	if (top < 0) return NULL;//top이 0보다작으면 종료
	return stack[top--];//아니면 스텍의 탑 한칸 빼기
}

void push(Node* aNode)//push함수
{
	stack[++top] = aNode;//스택에 top을 한칸 올린후 그위치에 입력받은 노드 입력
}

//사용하지 않는 스텍 출력 함수
void printStack()//스택 출력함수
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)//스텍의 탑이 i보다 작거나 같을때까지
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);//스텍의 인덱스 번호와 키 출력
	}
}


Node* deQueue()//큐 노드 삭제 함수
{
	if (front == rear) {//비어있으면
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;//종료
	}

	front = (front + 1) % MAX_QUEUE_SIZE;//맥스 큐 사이즈를 넘어가지 않게fornt +1 
	return queue[front];//리턴 뮤

}

void enQueue(Node* aNode)//큐 입력 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;//맥스 큐사이즈를 넘어가지 않게 rear +1
	if (front == rear) {//만약 꽉 차있으면
		// printf("\n....Now Queue is full!!\n");
		return;//리턴
	}

	queue[rear] = aNode;//큐의 rear부분에 입력받은 노드 입력
}
