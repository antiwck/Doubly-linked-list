#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
Template of node with a head pointer being initialized as global
*/
struct node {
	struct node* prev;
	int data;
	struct node* next;
}*head;

struct node* addNode(int);
void insertBeginNode(int);
void append();
void insertBetweenNode();
int delFirstNode();
int delLastNode();
void delCertainNode();
void reverseList();
void display();

int main() {
	char opt;
	head = NULL;

	do {
		system("cls");
		printf("Linked list program\n");
		printf("-------------------\n");
		printf("1. Append new node\n");
		printf("2. Insert new node\n");
		printf("3. Delete node\n");
		printf("4. Reverse list\n");
		printf("5. Display list\n");
		printf("[X to exit]\n");
		printf("\nSelection: ");
		opt = getchar(); while (getchar() != '\n');
		switch (opt) {
		case '1':
			append();
			printf("\nAfter appending:-\n");
			display();
			break;
		case '2':
			insertBetweenNode();
			printf("\nAfter inserting:-\n");
			display();
			break;
		case '3':
			delCertainNode();
			printf("\nAfter deleting:-\n");
			display();
			break;
		case '4':
			reverseList();
			printf("\nAfter reversing:-\n");
			display();
			break;
		case '5':
			display();
			break;
		case 'X':
		case 'x':
			printf("---PROGRAM ENDED---");
			break;
		default:
			printf("Invalid option.\n");
			_getch();
		}
	} while (opt != 'X' && opt != 'x');
	return 0;
}

/*
addNode is used to create the first node
*/
struct node* addNode(int data) {
	struct node* temp = malloc(sizeof(struct node));
	temp->prev = NULL;
	temp->data = data;
	temp->next = NULL;
	head = temp;
	return head;
}

/*
insertBeginNode works by creating a new node and making it the head while the rest nodes append to it
*/
void insertBeginNode(int data) {
	struct node* temp = malloc(sizeof(struct node));
	temp->prev = NULL;		//
	temp->data = data;		//	Declaring new node
	temp->next = NULL;		//
	temp->next = head;		//	Make new node next as head
	head->prev = temp;		//  Make head prev as new node
	head = temp;			//	Let head be the first
}

/*
Append works by creating a new node and traversing to the end of list and append the new node
*/
void append() {
	int data;
	printf("New data: ");
	scanf_s("%d", &data); while (getchar() != '\n');
	
	struct node* temp, * ptr;
	temp = malloc(sizeof(struct node));
	temp->prev = NULL;
	temp->data = data;
	temp->next = NULL;
	ptr = head;
	if (ptr == NULL) {
		head = addNode(data);
		return;
	}
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	ptr->next = temp;
	temp->prev = ptr;
}

/*
insertBetweenNode works by getting the data and position. As it traverse, the position decreases and once reached position, the new node will be inserted
*/
void insertBetweenNode() {
	int data, pos;
	printf("New data: ");
	scanf_s("%d", &data); while (getchar() != '\n');
	printf("Position of node to insert: ");
	scanf_s("%d", &pos); while (getchar() != '\n');

	struct node* ptr1, * ptr2, * temp;
	ptr1 = head;
	ptr2 = NULL;
	temp = NULL;
	temp = malloc(sizeof(struct node*));
	temp->data = data;
	temp->next = NULL;
	temp->prev = NULL;

	while (pos > 2 && ptr1->next != NULL) {
		ptr1 = ptr1->next;
		pos--;
	}

	if (pos == 1) {
		insertBeginNode(data);
	}
	else if (ptr1->next == NULL) {
		ptr1->next = temp;
		temp->prev = ptr1;
	}
	else {
		ptr2 = ptr1->next;
		ptr1->next = temp;
		ptr2->prev = temp;
		temp->prev = ptr1;
		temp->next = ptr2;
	}
}

/*
delFirstNode returns the element in first node and removing the first node
*/
int delFirstNode() {
	int data = head->data;
	head = head->next;
	free(head->prev);
	return data;
}

/*
delLastNode returns the element in last node and removing the last node
*/
int delLastNode() {
	struct node* ptr = head;
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	int data = ptr->data;
	ptr->prev->next = NULL;
	free(ptr);
	return data;
}

/*
delCertainNode gets the position and traverse the list. Once it reaches the position, it removes the node
*/
void delCertainNode() {
	int pos;

	printf("Position of node to delete: ");
	scanf_s("%d", &pos); while (getchar() != '\n');

	struct node* ptr1 = head;
	struct node* ptr2 = NULL;
	int data;
	if (pos == 1) {
		data = delFirstNode(head);
		return data;
	}
	while (pos > 1 && ptr1->next != NULL) {
		ptr1 = ptr1->next;
		pos--;
	}
	if (ptr1->next == NULL) {
		data = delLastNode(head);
	}
	else {
		data = ptr1->data;
		ptr2 = ptr1->prev;
		ptr2->next = ptr1->next;
		ptr1->next->prev = ptr2;
		free(ptr1);
		ptr1 = NULL;
	}

	printf("%d has been deleted.\n", data);
}

/*
reverseList changes the previous and next linkers as it traverse from the head to the end of list
*/
void reverseList() {
	struct node* ptr1 = head;
	struct node* ptr2 = ptr1->next;

	ptr1->next = NULL;
	ptr1->prev = ptr2;

	while (ptr2 != NULL) {
		ptr2->prev = ptr2->next;
		ptr2->next = ptr1;
		ptr1 = ptr2;
		ptr2 = ptr2->prev;
	}

	head = ptr1;
}

/*
Display will traverse all nodes while printing the data
*/
void display() {
	int ctr = 1;
	struct node* ptr;
	ptr = head;
	printf("Linked list:\n");
	if (ptr == NULL) {
		printf("There is no linked list.\n");
	}
	else {
		while (ptr) {
			printf("Node #%d: %d\n", ctr++, ptr->data);
			ptr = ptr->next;
		}
	}
	_getch();
}
