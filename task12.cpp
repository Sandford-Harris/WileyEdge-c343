#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n*2; j++){
			if(j <= i || n*2 - j < i){
				if(j <= n){
					cout << j;
				}
				else{
					cout << (n*2 - j) + 1;
				}
			}
			else{
				cout << " ";
			}
		}
		cout << endl;
	}
	
}
