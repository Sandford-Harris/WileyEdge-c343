#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	int x = n/2;
	if(n%2 == 0){
		x = n/2 - 1;
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= x; j++){
			
			if(j == 0 || j == i || j == n-i-1){
				cout << "* ";
			}
			else{
				cout << "  ";
			}
		}
		cout << endl;
	}
	
}
