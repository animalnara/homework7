/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("                     2021041098 강태광                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}




/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key; // 입력된 키 값을 새로운 노드에 설정합니다.
    newNode->link = NULL; // 새로운 노드의 링크를 NULL로 설정합니다.

    // 리스트가 비어있거나 입력된 키 값이 첫 번째 노드의 키 값보다 작을 때
    if (h->first == NULL || key < h->first->key) {
        newNode->link = h->first; // 새로운 노드의 링크를 첫 번째 노드로 설정합니다.
        h->first = newNode; // 헤드 노드를 새로운 노드로 갱신합니다.
        return 0; // 정상적으로 삽입되었으므로 0을 반환합니다.
    }

    // 리스트의 중간이나 끝에 삽입해야 할 경우
    listNode* current = h->first;
    while (current->link != NULL && key >= current->link->key) {
        current = current->link; // 입력된 키 값보다 큰 값을 찾을 때까지 리스트를 탐색합니다.
    }

    newNode->link = current->link; // 새로운 노드의 링크를 현재 노드의 다음 노드로 설정합니다.
    current->link = newNode; // 현재 노드의 링크를 새로운 노드로 설정합니다.

    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key; // 입력된 키 값을 새로운 노드에 설정합니다.
    newNode->link = NULL; // 새로운 노드의 링크를 NULL로 설정합니다.

    // 리스트가 비어있을 때
    if (h->first == NULL) {
        h->first = newNode; // 헤드 노드를 새로운 노드로 설정합니다.
        return 0; // 정상적으로 삽입되었으므로 0을 반환합니다.
    }

    // 리스트의 마지막 노드를 찾습니다.
    listNode* current = h->first;
    while (current->link != NULL) {
        current = current->link; // 다음 노드로 이동합니다.
    }

    current->link = newNode;  // 마지막 노드의 링크를 새로운 노드로 설정합니다.

    return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    listNode* temp = h->first;

    // 헤드 노드를 두 번째 노드로 변경합니다.
    h->first = h->first->link;

    // 첫 번째 노드를 해제합니다.
    free(temp);

    return 0;
}



/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    // 현재 노드와 이전 노드를 저장할 포인터를 선언
    listNode* current = h->first;
    listNode* prev = NULL;

    // 삭제할 노드가 첫 번째 노드인 경우
    if (current->key == key) {
        h->first = current->link; // 첫 번째 노드를 다음 노드로 변경합니다.
        free(current); // 첫 번째 노드를 해제합니다.
        return 0; // 정상적으로 삭제되었으므로 0을 반환합니다.
    }

    // 삭제할 노드가 첫 번째 노드가 아닌 경우
    while (current != NULL && current->key != key) {
        prev = current; // 현재 노드를 이전 노드로 설정합니다.
        current = current->link; // 다음 노드로 이동합니다.
    }

    // 삭제할 노드를 찾지 못한 경우
    if (current == NULL) {
        return -1; // 키가 존재하지 않으므로 -1을 반환합니다.
    }

    // 이전 노드와 현재 노드를 연결합니다.
    prev->link = current->link;

    // 현재 노드를 해제합니다.
    free(current);

    return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    // 현재 노드와 이전 노드를 저장할 포인터를 선언
    listNode* current = h->first;
    listNode* prev = NULL;

    // 리스트에 노드가 하나만 있는 경우
    if (current->link == NULL) {
        h->first = NULL; // 헤드 노드를 NULL로 설정하여 리스트를 비웁니다.
        free(current); // 첫 번째 노드를 해제합니다.
        return 0; // 정상적으로 삭제되었으므로 0을 반환합니다.
    }

    // 현재 노드를 마지막 노드로 이동합니다.
    while (current->link != NULL) {
        prev = current; // 현재 노드를 이전 노드로 설정합니다.
        current = current->link; // 다음 노드로 이동합니다.
    }

    // 이전 노드의 링크를 NULL로 설정하여 마지막 노드를 삭제합니다.
    prev->link = NULL;

    // 현재 노드를 해제합니다.
    free(current);

    return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    // 현재, 이전, 다음 노드를 저장할 포인터를 선언
    listNode* current = h->first;
    listNode* prev = NULL;
    listNode* next = NULL;

    // 현재 노드를 순회하면서 링크를 역순으로 재배치합니다.
    while (current != NULL) {
        next = current->link; // 다음 노드를 임시로 저장합니다.
        current->link = prev;  // 현재 노드의 링크를 이전 노드로 설정합니다.
        prev = current;  // 이전 노드를 현재 노드로 설정합니다.
        current = next;  // 다음 노드를 현재 노드로 설정합니다.
    }

    // 헤드 노드를 마지막 노드로 설정합니다.
    h->first = prev;

    return 0;
}



void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

