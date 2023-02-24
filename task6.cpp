#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n;
	int temp=0;
	int digits;
	int x =0;
	
	cout<<"n = ";
	cin>>n;
	cout<<"\n";
	
	digits = int(log10(n)+1);
	
	for(int i = digits; i>1; i-=2)
	{
		temp = int(n/pow(10,i-2));
		
		x = x*10;
		x += temp%10;
		temp = temp/10;
		x = x*10;
		x += temp%10;
	}
	if(digits%2==1)
	{
		x = x*10;
		x += n%10;
	}
	
	
	cout<<"The new value is "<<(x);
}
