#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	int digits = int(log10(n)+1);
	
	int num;
	for(int i = 1; i <= digits; i++){
		
		int r = n % 10;
		num += r * int(pow(10,digits-i));
		n = n / 10;
	}
	
	cout << num;
}
