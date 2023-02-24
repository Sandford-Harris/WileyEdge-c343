#include <iostream>

using namespace std;

int main(){
	
	int length;
	cout << "Enter array length:\n";
	cin  >> length;
	
	int *a = new int[length];
	cout << "Enter sorted array:\n";
	for(int i = 0; i < length; i++)
		cin >> a[i];
	
	int sk;
	cout << "Enter search key:\n";
	cin  >> sk;
	
	int low = 0, high = length-1;
	bool found = false;
	for(int i = 0; i <= length/2; i++){
		
		int mid = (low + high)/2;
		//if search key is found
		if(sk == a[mid]){
			cout << "Search key found at index " << mid << "\n";
			//search right for other instances of sk
			int i = mid + 1;
			while(i < length && a[i] == sk){
				cout << "Search key found at index " << i << "\n";
				i++;
			}
			//search left for other instances of sk
			i = mid - 1;
			while(i >= 0 && a[i] == sk){
				cout << "Search key found at index " << i << "\n";
				i--;
			}
			found = true;
			break;
		}
		else if(sk > a[mid]){
			low = mid + 1;
		}
		else{
			high = mid;
		}
	}
	
	if(!found){
		cout << "Element not found in list" << endl;
	}
}

