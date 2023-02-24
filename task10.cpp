#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int n;
	cout<<"enter a number\n";
	cin>>n;
	
	int count = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < i; j++){
			cout << count << " ";
			count++;
		}
		cout << endl;
	}
	
}
