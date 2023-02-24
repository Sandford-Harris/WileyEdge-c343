#include <iostream>
using namespace std;

int main(){
	
	int n;
	cout << "enter a number\n";
	cin >> n;
	
	for(int i = 0; i < n; i++){
		if(i%2 == 0){
			cout << n-(i/2) << " ";
		}
		else{
			cout << i-(i/2) << " ";
		}
	}
}
