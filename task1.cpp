#include <iostream>
using namespace std;

int main(){
	
	int paperPrice = 20;
	int inkPrice = 10;
	int markerPrice = 5;
	int penPrice = 3;
	
	int quantity = 0, totalPrice = 0, productPrice;
	string product;
	bool doLoop = true;
	cout << "Hello welcome to the store!\n";
	
	while(doLoop){
		cout<< "What would you like to purchase?\n";
	
		cout << "Paper - 20\nInk - 10 \nMarker - 5 \nPen - 3\n";
		
		bool validProduct = false;
		while(!validProduct){
			cin>>product;
	
			if(product != "Paper" && product != "Ink" && product != "Marker" && product != "Pen\n" ){
				cout << "That isn't a valid product, please try again\n";
			}
			else{
					validProduct = true;
				if(product == "Paper"){
					productPrice = paperPrice;
				}
				else if(product == "Ink"){
					productPrice = inkPrice;
				}
				else if(product == "Marker"){
					productPrice = markerPrice;
				}
				else{
					productPrice = penPrice;
				}
			}
		}
	
		cout << "how much would you like?\n";
		cin >> quantity;
		totalPrice = totalPrice + (quantity * productPrice);
		cout << "Your current bill is "<<totalPrice<<"\nWould you like to order more?";
	
		string answer;
		cin >> answer;
		if(answer != "yes"){
			cout << "goodbye! your final bill is "<<totalPrice;
			doLoop = false;
		}
	}
	
	
	
}
