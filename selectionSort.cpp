#include <iostream>

using namespace std;


void input(int[], int);
void output(int[], int);
void selectionSort(int[], int);

int main(){
	
	int n;
	cout << "enter array length: ";
	cin >> n;
	int *a = new int[n];
	
	cout << "enter array elements: ";
	input(a, n);
	
	selectionSort(a, n);
	output(a, n);
	
}

void input(int a[], int n){
	for(int i = 0; i < n; i++)
		cin >> a[i];
}


void output(int a[], int n){
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
}

void selectionSort(int a[], int n){
	
	for(int i = 0; i < n; i++){
		int minind = i;
		int min = a[i];
		for(int j = i+1; j < n; j++){
			if(a[j] < min){
				min = a[j];
				minind = j;	
			}
		}
		int temp = a[i];
		a[i] = a[minind];
		a[minind] = temp;
	}
}
