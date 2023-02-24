#include <iostream>
#include <string>

using namespace std;

struct Student{
	int id;
	char name[20];
};

void getdata(Student *x){
	
	cout << "Enter id ";
	cin >> x->id;
	cout << "enter name ";
	cin >> x->name;
}

void display(Student x){
	
	cout << "ID: " << x.id << endl;
	cout << "Name: " <<  x.name << endl;
}

int main(){
	
	Student *s = new Student[3];
	for(int i=0; i < 3; i++){
		getdata(&s[i]);
	}
	for(int i=0; i < 3; i++){
		display(s[i]);
	}
	
}
