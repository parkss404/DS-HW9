#include <stdio.h>
#include <stdlib.h>

//노드의 구성값 
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
//구조체 선언
} Node;

int initializeBST(Node** h);

//함수 종류
void inorderTraversal(Node* ptr);	
void preorderTraversal(Node* ptr);   
void postorderTraversal(Node* ptr);	  
int insert(Node* head, int key); 
int deleteLeafNode(Node* head, int key); 
Node* searchRecursive(Node* ptr, int key); 
Node* searchIterative(Node* head, int key);
int freeBST(Node* head);


int main()
{
	char command;
	int key;
    //head,ptr 노드
	Node* head = NULL;
	Node* ptr = NULL;	

	do{
		printf("[----- [박성준] [2021040026] -----]\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	//비어있을 시 할당된 트리정보 초기화
	if(*h != NULL)
		freeBST(*h);

	//헤드노드 만들기
	*h = (Node*)malloc(sizeof(Node)); //메모리 할당
	(*h)->left = NULL;	//루트노드
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

//중위순회
void inorderTraversal(Node* ptr)
{ 
	if(ptr) {  //재귀함수를 통해 순회 
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}
//전위순회
void preorderTraversal(Node* ptr)
{
	if(ptr) { //재귀함수를 통해 순회
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}
//후위순회
void postorderTraversal(Node* ptr)
{
	if(ptr) {//재귀함수를 통해 순회
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}
//노드 삽입
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//newNode 메모리 할당
	newNode->key = key; //받은 키값 대입
	//자식 노드는 비어있는 상태로
    newNode->left = NULL;
	newNode->right = NULL;
    
    //기존 연결에 left 비어있을 경우, 주소값지정
	if (head->left == NULL) { 
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;

	while(ptr != NULL) { //ptr이 NULL이 아닐때까지

		//해당값이 중복되면,리턴
		if(ptr->key == key) return 1;

		//부모 주소값을 계속 저장하면서 이동하기 위해
		parentNode = ptr;

        //입력한 키값이 현재 키값보다 더 큰경우,
		if(ptr->key < key)
			ptr = ptr->right; //오른쪽으로 
		else
			ptr = ptr->left; //왼쪽으로 
	}

    //부모노드의 키값이 입력한 값보다 더 큰 경우 
	if(parentNode->key > key)
		parentNode->left = newNode; //왼쪽으로 
	else
		parentNode->right = newNode;//오른쪽으로 
	return 1;
}

//노드 삭제
int deleteLeafNode(Node* head, int key)
{
    //비어있는경우
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    //헤드 왼쪽 비어있는경우
	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	//위가 아니면, head->left에서 시작
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */

    //부모노드 기록위해서 
	Node* parentNode = head;

    //ptr이 null이 아닐때까지
	while(ptr != NULL) {

        //입력한 키값으로 해당 키값을 만나면
		if(ptr->key == key) {
            //만약 그 아래로 주소가 비어있다면
			if(ptr->left == NULL && ptr->right == NULL) {

				//부모노드가 헤드일때(처음)
				if(parentNode == head)
                    //헤드의 값자체 제거
					head->left = NULL;

				//부모노드의 왼쪽이 ptr
				if(parentNode->left == ptr)
                    //부모노드의 연결 끊기
					parentNode->left = NULL;
				else
                    //오른쪽의 경우 부모노드와 연결끊기
					parentNode->right = NULL;
                //ptr 프리
				free(ptr);
			}
			else {
                //그 아래에 값이 있으므로 프린트 
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		//부모노드 ptr로 업데이트 
		parentNode = ptr;

        //키값이랑 비교해가면서 오른쪽,왼쪽으로 이동한다.
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}
    //끝까지 탐색했는데 못찾은경우,
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}
//재귀로 노드찾기 
Node* searchRecursive(Node* ptr, int key)
{
	//ptr이 비어있으면
    if(ptr == NULL)
        //리턴
		return NULL;
    //재귀함수이용
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
    //재귀함수이용
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	//찾았을 때, 해당 주소 리턴
	return ptr;

}

//Iterative방식으로 노드찾기
Node* searchIterative(Node* head, int key)
{
	//처음 설정
	Node* ptr = head->left;

    //널이 아닐때까지 반복
	while(ptr != NULL)
	{
        //맞으면
		if(ptr->key == key)
            //주소 리턴
			return ptr;
        //ptr 이동
		if(ptr->key < key) 
            ptr = ptr->right;
		else
			ptr = ptr->left;
	}
    //없으면 널 
	return NULL;
}

//노드 프리 
void freeNode(Node* ptr)
{
    //ptr있으면
	if(ptr) {
        //재귀함수로 노드 프리
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}
//이진탐색 프리
int freeBST(Node* head)
{
    //처음일경우
	if(head->left == head)
	{
		free(head);
		return 1;
	}

    //처음 값 가져오기
	Node* p = head->left;
    //p 프리노드
	freeNode(p);
    //헤드 프리
	free(head);
	return 1;
}

