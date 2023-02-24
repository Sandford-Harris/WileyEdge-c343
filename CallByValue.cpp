#include <iostream>

using namespace std;

void swap(int a, int b){
	
	int temp = a;
	a = b;
	b = temp;
	cout << "SWAP a = " << a<< " b = "<<b<<endl;
	cout << "SWAP (addresses) &a = " << &a<< " &b = "<<&b<<endl;
}

int main(){
	
	int a = 10, b = 20;
	
	cout << "MAIN (before) a = " << a<< " b = "<<b<<endl;
	cout << "MAIN (addresses) &a = " << &a<< " &b = "<<&b<<endl;
	
	swap(a,b);
	cout << "MAIN (after) a = " << a<< " b = "<<b<<endl;
}
