#include <iostream>

using namespace std;

int main(){
	
	cout << "enter array size: ";
	int size;
	cin >> size;
	
	int *a = new int[size];
	int max;
	
	for(int i =0; i < size; i++){
		cin >> a[i];
	}
	
	bool found = false;
	int smallest = 0;
	
	while(!found && smallest < size){
		smallest += 1;
		bool present = false;
		for(int i=0; i < size; i++){
			if(a[i] == smallest){
				present = true;
				break;
			}
		}
		if(!present) found = true;
	}
	if(found) cout << smallest;
	else cout << 1;
}
