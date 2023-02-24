#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout << "enter a number\n";
	cin >> n;

	int digits = int(log10(n)+1);
	
	int x = n / 10;
	int y = n % 10;
	
	int z = (y * int(pow(10, digits-1))) + x;
	
	cout << z << endl;
}

