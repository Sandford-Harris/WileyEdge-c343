#include <iostream>
using namespace std;

int main(){
	
	int n;
	cout << "enter a number\n";
	cin >> n;
	
	int count = 0;
	int total = 0;
	while(n > 0){
		
		int r = n % 10;
		n = n / 10;
		
		total += r;
		count++;
	}
	
	cout << "number of digits = " << count << "\n";
	cout << "sum of digits = " << total << "\n";
	
}
