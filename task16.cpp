#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	//bug with n=123 m=67890, the loop runs again and ndigits is not 0
	
	int n, m;
	cout<<"enter n and m:\n";
	cin>>n >> m;
	
	int nDigits = int(log10(n)+1);
	int mDigits = int(log10(m)+1);
	
	int op = 0;
	
	int iter = (nDigits < mDigits) ? nDigits : mDigits;
	
	
	
	for(int i = 1; i <= iter+1; i++){
		int q;
		if(nDigits-(i-1) > 0){
			q = (n < 10) ? n : n / int(pow(10,nDigits-i));
			op = op*10 + q;
			n = n % int(pow(10,nDigits-i));
		}
		else{
			if(nDigits != mDigits){
				op = op * int(pow(10,mDigits-i)) + m;
			}
		}

		if(mDigits-(i-1) > 0){
			q = (m < 10) ? m : m / int(pow(10,mDigits-i));	
			op = op*10 + q;
			m = m % int(pow(10,mDigits-i));
		}
		else{
			if(nDigits != mDigits){
				op = op * int(pow(10,nDigits-i)) + n;			
			}

		}
		
	}
	cout << op;
}
