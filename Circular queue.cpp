#include<iostream>
#define max 5
using namespace std;
void enqueue();
void dequeue();
void display();
int a[max],f,r;
int main()
{
	f = 0, r = -1;
	int ch;
	do
	{
		cout<<"\n 1 ENQUEUE 2 DEQUEUE 3 DISPLAY 4 EXIT \n Enter choice=";
		cin>>ch;
		switch(ch)
		{
			case 1: enqueue();break;
			case 2: dequeue();break;
			case 3: display();break;
			case 4: break;
			default:cout<<"\n Invalid choice \n";
		}
	}while(ch!=4);
}
void enqueue()
{
	if(r-f == max-1)
		cout<<"\n Queue overflow " <<endl;
	else
	{
		int ele;
		cout<<"\n Enter the ele = ";
		cin>>ele;
		++r;
		a[r%max] = ele;
	}	
}
void dequeue()
{
	if(f>r)
		cout<<"\n Queue underflow\n";
	else
	{
		cout<<"\n The element deleted = "<<a[f%max]<<endl;
		a[f%max] = 0;
		f++;
	}
}
void display()
{
	if(f>r)
		cout<<"\n Queue empty\n";
	else
	{
		cout<<"\n the elements of queue = \n";
		for(int i=0;i<max;i++)
			cout<<a[i]<<"\t";
	}
}
