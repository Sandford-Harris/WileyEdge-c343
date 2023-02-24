#include<iostream>
#define max 10

using namespace std;

void push(int a[],int &upTop, int &downTop, int dir);
void pop(int a[],int &upTop, int &downTop, int dir);
void display(int a[], int upTop, int downTop);

int main()
{
	int a[max],upTop = -1, downTop = max;
	int ch, dir;
	do
	{
		cout<<"\n 1 PUSH 2 POP 3 DISPLAY 4 EXIT\n Enter choice = ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				dir = 1;
				cout << "From which direction? 1 - Top, 2 - Bottom: ";
				cin >> dir;
				push(a,upTop, downTop, dir);
				break;
			case 2: 
				dir = 1;
				cout << "From which direction? 1 - Top, 2 - Bottom: ";
				cin >> dir;
				pop(a,upTop, downTop, dir);
				break;
			case 3: display(a, upTop, downTop);break;
			case 4: break;
		}
	}while(ch!=4);
}

void push(int a[],int &upTop, int &downTop, int dir)
{
	if(dir == 1){ //push from top->bottom
		if(upTop==max-1 || upTop == downTop-1)
			cout<<"\n Stack overflow \n";
		else
		{
			int ele;
			cout<<"\n enter the ele = ";
			cin>>ele;
			a[++upTop]=ele;
		}
	}
	else if(dir == 2){ //push from bottom->top
		if(downTop==0 || downTop == upTop+1)
			cout<<"\n Stack overflow \n";
		else
		{
			int ele;
			cout<<"\n enter the ele = ";
			cin>>ele;
			a[--downTop]=ele;
		}
	}
	
}

void pop(int a[],int &upTop, int &downTop, int dir)
{
	
	if(dir == 1){ //pop from top->bottom
		if(upTop==-1)
			cout<<"\n Stack underflow \n";
		else
		{
			cout<<"\n Deleting  = "<<a[upTop--]<<endl;
		}
	}
	else if(dir == 2){ //pop from bottom->top
		if(downTop==max)
			cout<<"\n Stack underflow \n";
		else
		{
			cout<<"\n Deleting  = "<<a[downTop++]<<endl;
		}
	}
}

void display(int a[], int upTop, int downTop)
{
	cout<<"\n Stack elements \n";
		for(int i=max-1;i>=0;i--){
			if(i > upTop && i < downTop){
				cout << endl;
			}
			else{
				cout<<a[i]<<endl;
			}
		}
}

