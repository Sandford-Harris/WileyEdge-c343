#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n-i; j++){
			if(i%2 == 0){
				cout << j + i + (i/2) + 1 << " ";
			}
			else{
				cout << n + i/2 - j + 1 << " ";
			}
		}
		cout << endl;
	}		
}
