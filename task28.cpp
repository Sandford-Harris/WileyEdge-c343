#include <iostream>

using namespace std;


void input(int[], int);
void output(int[], int);
void insertionSort(int[], int);

int main(){
	
	int n;
	cout << "enter array length: ";
	cin >> n;
	int *a = new int[n];
	
	cout << "enter array elements: ";
	input(a, n);
	
	insertionSort(a, n);
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

void insertionSort(int a[], int n){
	
	int i,j,key;
	
	for(int i = 1; i < n; i++){
		key = a[i];
		j = i-1;
		while(j>=0 && a[j]>key){
			
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
	}
}
