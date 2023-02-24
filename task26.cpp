#include <iostream>

using namespace std;

void bubbleSort(int[], int);
void output(int[], int);

int main(){
	
	int capacity = 20, currentCount = 0, ch;
	int *a = new int[capacity];
	
	do{
		cout << "\nWhat would you like to do?\n 1 - Add element\n 2 - Delete element\n 3 - Exit\n";
		cin >> ch;
		switch(ch){
			
			case 1: //Add Element
			{
				
				if(currentCount == capacity){
					cout << "Array full, Sorry!\n";
					break;
				}
				int val, pos;
				do{
					cout << "Enter Element and the position to insert it: ";
					cin >> val >> pos;
					pos -= 1; //make the postion into the index
					if(pos < 0 || pos > currentCount)
						cout << "\nThat position is invalid, enter a position <= " << currentCount+1 << endl;
						
				}while(pos < 0 || pos > currentCount);
				
				int temp = a[currentCount];
				for(int i = currentCount; i >= pos; i--){
					a[i] = a[i-1];
				}
				
				a[currentCount+1] = temp;
				a[pos] = val;
				currentCount++;
				break;
			}
			case 2: //Delete Element
				if(currentCount == 0){
					cout << "There are no elements to Delete\n";
					break;
				}
				int pos;
				do{
					cout << "Enter the position to remove: ";
					cin >> pos;
					pos -= 1; //make the postion into the index
					if(pos < 0 || pos > currentCount)
						cout << "\nThat position is invalid, enter a position <= " << currentCount+1 << endl;
				}while(pos < 0 || pos > currentCount);
				
				
				for(int i = pos; i < currentCount; i++){
					a[i] = a[i+1];
				}
				currentCount--;
				break;
			case 3:
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "Invalid input\n";
				break;
		}
		
		cout << "\nCurrent array is: \n";
		output(a, currentCount);	
	}while(ch!=3);	
}



void output(int a[], int n){
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
}
