#include <iostream>
#include "productLinkedList.h"

using namespace std;


int main(){
	
	head = NULL;
	cnt = 0;
	int ch;
	
	string name, category;
	int pid;
	double price;
	double total;
	
	do{
		cout << "\nWhat do you want to do?" << endl;
		cout << "\t1- Add product to the list" << endl;
		cout << "\t2- Remove product from end of the list" << endl;
		cout << "\t3- Display product of given id" << endl;
		cout << "\t4- Display all products" << endl;
		cout << "\t5- Calculate total price of current products" << endl;
		cout << "\t6- Sort products by category" << endl;
		cout << "\t7- Exit" << endl;
		cout << "=";
		cin >> ch;
		switch(ch){
			
			case 1:
				cout << "\nEnter the product ID: ";
				cin >> pid;
				cout << "\nEnter the product name: ";
				cin >> name;
				cout << "\nEnter the product price: ";
				cin >> price;
				cout << "\nEnter the product category: ";
				cin >> category;
				push_back(new Product(pid, name, price, category));
				break;		
			case 2:
			{
				Product *p = pop_back();
				if(p != NULL){
					cout << "\nProduct " << p->pName << " Removed from list." << endl;
					delete p;
				}
				else{
					cout <<"\nNo products in the list to remove\n";
				}
				break;	
			}	
			case 3:
				cout << "\nEnter the product ID: ";
				cin >> pid;
				displayProduct(pid);
				break;
			case 4:
				cout << "\nListing Products...\n";
				displayAll();
				break;
			case 5:
				total = calculateTotal();
				cout << fixed << setprecision(2);
				cout << "\nThe current total price of products in the list is $" << total << endl;
				break;
			case 6:
				cout << "\nArranging products based on category...\n";
				sortByCategory();
				displayAll();
				break;
			case 7:
				break;
			default:
				cout << "\nInvalid input\n";
				break;
		}
		
	}while(ch!=7);
	
}
