#include <iostream>

using namespace std;

void bubbleSort(int[], int);
void input(int[], int);
void output(int[], int);

int main(){
	
	int length;
	cout << "Enter array length:\n";
	cin  >> length;
	
	int *a = new int[length];
	cout << "Enter array elements:\n";
	
	
	input(a, length);
	cout << "Pre sorted list: \n";
	output(a, length);
	bubbleSort(a, length);
	cout << "\nSorted list is:\n";
	output(a, length);
	
	
}

void input(int a[], int n){
	for(int i = 0; i < n; i++)
		cin >> a[i];
}

void output(int a[], int n){
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
}

void bubbleSort(int a[], int length){
	
	for(int i= 0; i < length-1; i++){
		bool swapped = false;
		for(int j= 0; j < length-i-1; j++){
			if(a[j] > a[j+1]){
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				swapped = true;
			}
		}
		if(!swapped){
			break;
		}	
	}
}
