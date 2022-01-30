#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int val;
	struct Node* next;
} Node;

Node* new_node(int val){
	Node* n = malloc(sizeof(Node));
	if(n == NULL){
		fprintf(stderr, "Could not allocate enough memory for a new node!\n");
	}
	n->val = val;
	n->next = NULL;

	return n;
}

void print(Node* root){
	if(root == NULL){
		printf("NULL\n");
		exit(0);
	}
	printf("%d ----> ", root->val);
	print(root->next);
}

int main(){
	Node* root = new_node(1);
	Node* n1 = new_node(2);
	Node* n2 = new_node(3);
	Node* n3 = new_node(4);
	Node* n4 = new_node(5);
	Node* n5 = new_node(6);

	// Add next pointers
	root->next = n1;
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;

	print(root);

	free(root);
	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);

	return 0;
}
