#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < (n*2)-i; j++){
			if(j < n-i){
				cout << " ";
			}
			else{
				cout << "*";
			}	
		}
		cout << endl;
	}
}
