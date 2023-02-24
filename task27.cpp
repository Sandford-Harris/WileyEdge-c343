#include <iostream>

using namespace std;

void input(int[], int);
void output(int[], int);

int main(){
	
	int *a, *b, *c;
	int aLen, bLen, cLen;
	cout << "Enter 1st array length: ";
	cin >> aLen;
	a = new int[aLen];
	
	cout << "Enter 1st array values: ";
	input(a, aLen);
	
	cout << "Enter 2nd array length: ";
	cin >> bLen;
	b = new int[bLen];
	
	cout << "Enter 2nd array values: ";
	input(b, bLen);
	
	cout << "Enter 3rd array length: ";
	cin >> cLen;
	c = new int[cLen];
	
	cout << "Enter 3rd array values: ";
	input(c, cLen);
	
	int dLen = aLen+bLen+cLen;
	int *d = new int[dLen];
	
	int maxLen = (((aLen > bLen) ? aLen : bLen) > cLen ) ? ((aLen > bLen) ? aLen : bLen) : cLen;
	
	int i = 0, Iter = 0;
	while(i < maxLen){
		if(i < aLen){
			d[Iter] = a[i];
			Iter++;
		}
		if(i < bLen){
			d[Iter] = b[i];
			Iter++;
		}
		if(i < cLen){
			d[Iter] = c[i];
			Iter++;
		}
		i++;
	}
	output(d, dLen);
}

void input(int a[], int n){
	for(int i = 0; i < n; i++)
		cin >> a[i];
}


void output(int a[], int n){
	for(int i = 0; i < n; i++)
		cout << a[i] << " ";
}
