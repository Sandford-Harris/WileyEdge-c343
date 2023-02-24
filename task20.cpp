#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	for(int i = 0; i < n*2-1; i++){
		for(int j = 0; j < n*2-1; j++){
			if(j <= n-(i+1) || j >= n+(i-1) || i-j >= n-1 || i+j >= 3*(n-1)){
				cout << "* ";
			}
			else{
				cout << "  ";
			}
			
		}
		cout << endl;
	}
}
