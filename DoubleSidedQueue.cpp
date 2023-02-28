#include <iostream>
#define max 5

using namespace std;

void enqueue(int a[], int &front1, int &rear1, int &front2, int &rear2, int dir);
void dequeue(int a[], int &front1, int &rear1, int &front2, int &rear2, int dir);
void display(int a[], int front1, int rear1, int front2, int rear2);

int main(){

	int *a = new int[max], front1 = 0, rear1 = -1, front2 = max-1, rear2 = max;
	int ch;
	do{
		cout << "\n 1 - ENQUEUE 2 - DEQUEUE 3 - DISPLAY 4 - EXIT\nEnter choice= ";
		cin >> ch;
		int ch2;
		switch(ch){
			
			case 1:
				cout << "From which side? 1-LEFT 2-RIGHT\n Enter choice=";
				cin>> ch2;
				if(ch2 == 1 || ch2 == 2)
					enqueue(a, front1, rear1, front2, rear2, ch2);	
				else 
					cout << "Invalid input"<< endl;
				break;
			case 2:
				cout << "From which side? 1-LEFT 2-RIGHT\n Enter choice=";
				cin>> ch2;
				if(ch2 == 1 || ch2 == 2)
					dequeue(a, front1, rear1, front2, rear2, ch2);	
				else 
					cout << "Invalid input"<< endl;
				break;
			case 3:
				display(a, front1, rear1, front2, rear2);
				break;
			case 4:
				cout << "Goodbye" << endl;
				break;
			default:
				cout << "Invalid input" << endl;
				break;
		}
		
	}while(ch!=4);
	
}

void enqueue(int a[], int &front1, int &rear1, int &front2, int &rear2, int dir){
	
	if(rear1+1 == rear2){
		cout << "queue overflow" << endl;
	}
	else{
		int element;
		cin >> element;
		if(dir == 1){
			rear1++;
			a[rear1] = element;
		}
		else{
			rear2--;
			a[rear2] = element;
		}
	}
}

void dequeue(int a[], int &front1, int &rear1, int &front2, int &rear2, int dir){
	
	if(front1 > rear1){
		cout << "queue underflow on left" << endl;
		front1 = 0;
		rear1 = -1;
	}
	else if(front2 < rear2){
		cout << "queue underflow on right" << endl;
		front2 = max-1;
		rear2 = max;
	}
	else{
		if(dir == 1){
			cout << "element deleted = " << a[front1] << endl;
			a[front1] = -1;
			front1++;
		}
		else{
			cout << "element deleted = " << a[front2] << endl;
			a[front2] = -1;
			front2--;
		}	
	}
}

void display(int a[], int front1, int rear1, int front2, int rear2){
	
	if(front1 > rear1 && front2 < rear2){
		cout << "queue empty" << endl;	
	}
	cout << "left rear is " << rear1 << "||| right rear is " << rear2 << endl;
	cout << "left front is " << front1 << "||| right front is " << front2 << endl;
	for(int i = 0; i < max; i++){
		cout << a[i] << "\t";
	}
	
}
