#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	//close but not quite
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	
	for(int i = 0; i < n*2-1; i++){
		for(int j = 0; j < n*4-3; j++){
			if(j < n-(i+1) || j > n + (i-1) || (i+j >= n && j < n+i-1)){
				cout << "  ";
			}
			else{
				cout << "* ";
			}
		}
		cout << endl;
	}
	
}
