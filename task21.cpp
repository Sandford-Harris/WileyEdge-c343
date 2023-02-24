#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if((j >= i && j < n-i) || (j >= n-(i+1) && j <= i)) {
				cout << "* ";
			}
			else{
				cout << "  ";
			}
		}	
		cout << endl;
	}	
}
