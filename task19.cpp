#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	
	for(int i = 0; i < n*2-1; i++){
		for(int j = 1; j <= n*2-1; j++){
			if(j == n+i || j == 2*n - (i-1) || j-i == n || (j<n && (i == 0 || i == 2*n-2))){
				cout << "* ";
			}
			else{
				cout << "  ";
			}
		}
		cout << endl;
	}	
}
