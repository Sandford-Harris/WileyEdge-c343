#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	char shift;
	int rot, length;
	
	cout << "Enter array length:\n";
	cin  >> length;
	
	int *a = new int[length];
	cout << "Enter array values:\n";
	for(int i = 0; i < length; i++)
		cin >> a[i];
	
	
	cout << "Enter shift dir(l/r) and rotation amount:\n";
	cin >> shift >> rot;
	
	if(shift == 'l'){
		for(int i = 0; i < rot; i++){
			int temp = a[0];
			for(int j = 0; j < length; j++){
				a[j] = a[j+1];
			}
			a[length-1] = temp;
		}
	}
	else{
		for(int i = 0; i < rot; i++){
			int temp = a[length-1];
			for(int j = length-1; j >= 0; j--){
				a[j] = a[j-1];
			}
			a[0] = temp;
		}
	}
	
	
	for(int i = 0; i < length; i++)
		cout << a[i] << " ";
}
