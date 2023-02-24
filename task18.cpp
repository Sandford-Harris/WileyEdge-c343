#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	for(int i = 0; i < n*2; i++){
		for(int j = 1; j <= n*2-1; j++){
			if(j == n || j == n-i || j == n+i || i+1 == n){
				cout << "* ";
			}
			else{
				cout << "  ";
			}
		}
		cout << endl;
	}
		
}
