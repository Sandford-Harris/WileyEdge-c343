#include <iostream>
using namespace std;

int main(){
	
	int n;
	cout << "enter a number\n";
	cin >> n;
	
	for(int i=n; i > n/2; i--){
		cout<<i<<" ";
	}
	
	for(int i=1; i < (n/2) + 1; i++){
		cout<<i<<" ";
	}
}
