#include <iostream>

using namespace std;

void oddSum(int &sum, int n);

int main(){
	
	int n, sum = 0; 
	cin >> n;
	
	oddSum(sum, n);
	cout << sum << endl;
}

void oddSum(int &sum, int n){
	
	if(n == 0) return;
	else{
		int last = n%10;
		if(last%2 != 0){
			sum += last;
		}
		n /= 10;
		return oddSum(sum, n);
	}
}
