#include <iostream>
#define max 5

using namespace std;

void enqueue(int a[], int &front, int &rear);
void dequeue(int a[], int &front, int &rear);
void display(int a[], int front, int rear);

int main(){

	int *a = new int[max], front = 0, rear = -1;
	int ch;
	do{
		cout << "\n 1 - ENQUEUE 2 - DEQUEUE 3 - DISPLAY 4 - EXIT\nEnter choice= ";
		cin >> ch;
		switch(ch){
			
			case 1:
				enqueue(a, front, rear);
				break;
			case 2:
				dequeue(a, front, rear);
				break;
			case 3:
				display(a, front, rear);
				break;
			case 4:
				cout << "Goodbye" << endl;
				break;
			default:
				cout << "Invalid input";
				break;
		}
		
	}while(ch!=4);
	
}

void enqueue(int a[], int &front, int &rear){
	
	if(rear == max-1){
		cout << "queue overflow" << endl;
	}
	else{
		
		int element;
		cin >> element;
		rear++;
		a[rear] = element;
	}
}

void dequeue(int a[], int &front, int &rear){
	
	if(front > rear){
		cout << "queue underflow" << endl;
	}
	else{
		
		cout << "element deleted = " << a[front] << endl;
		front++;
	}
}

void display(int a[], int front, int rear){
	
	if(front > rear){
		cout << "queue empty" << endl;	
	}
	for(int i = front; i <= rear; i++){
		cout << a[i] << "\t";
	}
	
}
