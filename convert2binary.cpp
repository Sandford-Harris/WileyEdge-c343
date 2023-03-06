#include <iostream>

using namespace std;

int convert2Bin(int n){
	
	if(n == 0){
		return n;
	}
	else{
		return (n%2) + (10 * convert2Bin(n/2));
	}
}

int main(){
	
	int n;
	cin >> n;
	
	int bin = convert2Bin(n);
	cout << bin;
	cout << char(7);
}
