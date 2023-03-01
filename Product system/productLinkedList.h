#include <iostream>
#include <iomanip>
using namespace std;

struct Product{
	
	int PID;
	string pName;
	double price;
	string category;
	
	
	Product(int PID, string pName, double price, string category){
		this->PID = PID;
		this->pName = pName;
		this->price = price;
		this->category = category;
	}
};

struct Node{
	
	Product *product;
	Node *next;

};

Node *head;
int cnt;

void push_back(Product *product){
	
	Node *n = new Node();
	n->product = product;
	n->next = NULL;
	if(head == NULL){
		head = n;
	}
	else{
		Node *temp = head;
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next = n;
	}
	cnt++;
}

Product* pop_back(){
	
	if(head == NULL){
		return NULL;
	}
	else if(head->next == NULL){
		Product *p = head->product;
		delete head;
		head = NULL;
		cnt--;
		return p;
	}
	else{
		Node *temp = head, *prev = head;
		while(temp->next!=NULL){
			prev = temp;
			temp = temp->next;
		}
		prev->next = NULL;
		Product *p = temp->product;
		//delete temp->product;
		delete temp;
		cnt--;
		return p;
	}	
}

void displayProduct(int PID){
	
	Node *temp = head;
	while(temp!=NULL){
		if(temp->product->PID == PID){
			cout << "\nProduct Name: " << temp->product->pName;
			cout << fixed << setprecision(2);
			cout << "\nProduct Price: $" << temp->product->price ;
			cout << "\nProduct Category: " << temp->product->category << endl;
			return;
		}
		temp = temp->next;
	}
	cout << "\nNo product with that id found" << endl;
}

void displayAll(){
	
	if(head == NULL){
		cout << "\nNo products in the list\n";
		return;
	}
	Node *temp = head;
	while(temp != NULL){
		cout << "\nProduct ID: " << temp->product->PID;
		cout << "\nProduct Name: " << temp->product->pName;
		cout << fixed << setprecision(2);
		cout << "\nProduct Price: $" << temp->product->price ;
		cout << "\nProduct Category: " << temp->product->category << endl;
		temp = temp->next;
	}
}

double calculateTotal(){
	
	double total = 0.0;
	if(head == NULL){
		cout << "\nNo products in the list\n";
		return total;
	}
	else{
		cout << "\nTotaling...\n";
		Node *temp = head;
		while(temp != NULL){
			total += temp->product->price;
			temp = temp->next;
		}
		return total;
	}
}

void sortByCategory(){
	
	if(head == NULL){
		cout << "\nNo products in the list\n";
	}
	else{
		Node *start = head, *iter;
		
		for(int i = 1; i <= cnt; i++){
			iter = start->next;
			for(int j = 0; j<cnt-i; j++){
				if(iter->product->category < start->product->category){
					Product *temp = iter->product;
					iter->product = start->product;
					start->product = temp;
				}
				iter = iter->next;
			}
			start = start->next;
		}
	}
}
