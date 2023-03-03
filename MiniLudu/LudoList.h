#include <iostream>
#include <vector>

using namespace std;

struct Node{
	
	bool safe;
	Node *next;
	Node *prev;
	
};

Node *head;
int cnt;

Node* createNode(bool safe){
	
	Node *n = new Node();
	n->safe = safe;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

void addFirst(bool safe){
	
	Node *n = createNode(safe);
	if(head == NULL){
		head = n;
	}
	else{
		head->prev = n;
		n->next = head;
		head = n;
	}
	cnt++;
	
}

void addLast(bool safe){
	
	if(head == NULL){
		addFirst(safe);
	}
	else{
		Node *n = createNode(safe);
		Node *temp = head;
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next = n;
		n->prev = temp;
		cnt++;
	}
}

void initialiseBoard(int size, int *safeSpots, int safeCount){
	
	for(int i = 1; i <= size; i++){
		bool safe = false;
		for(int j = 0; j < safeCount; j++){
			if(safeSpots[j] == i){
				safe = true;
				break;
			}
		}
		addLast(safe);
	}
}

Node* getBoardTile(int pos){
	
	Node *temp = head;
	if(temp != NULL){
		int i = 1;
		while(temp!=NULL && i < pos){
			temp = temp->next;
			i++;
		}
		return temp;
	}
}


