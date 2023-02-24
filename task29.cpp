#include <iostream>

using namespace std;


void input(int[], int);

int main(){
	
	int n;
	cout << "enter array length: ";
	cin >> n;
	int *a = new int[n];
	
	cout << "enter array elements: ";
	input(a, n);
	
	for(int i = 0; i < n; i++){
		int key = a[i];
		int counter = 1;
		
		bool checked = false;
		for(int j = 0; j < i; j++){
			if(a[j] == key)
				checked = true;
				break;
		}
		if(checked)
			continue;
			
		for(int j = i+1; j < n; j++){
			if(a[j] == key){
				counter++;
			}
		}
		if(counter == key){
			cout << "the number " <<  key << " is equal to its frequency" << endl;
		}
	}
	
}

void input(int a[], int n){
	for(int i = 0; i < n; i++)
		cin >> a[i];
}

