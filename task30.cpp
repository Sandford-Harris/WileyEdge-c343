#include <iostream>

using namespace std;

int main(){
	
	int **a;
	int row, col;
	
	cout << "Enter row and column count: ";
	cin >> row >> col;
	
	a = new int *[row];
	for(int i=0; i < row; i++){
		a[i] = new int[col];
	}
	
	//Giving inputs to the array
	cout << "Enter " << (row * col) << " numbers to the Array\n";
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cout << "Enter the elements at Row " << i + 1 << " Column " << j + 1 << endl;
			cin >> a[i][j];
		}
	}
	//sum of each row
	for(int i = 0; i < row; i++){
		int sum = 0;
		for(int j = 0; j < col; j++){
			sum += a[i][j];
		}
		cout << "sum of row " << i+1 << " = " << sum << endl;
	}
	cout << "===========================================" << endl;
	//sum of each column
	for(int i = 0; i < row; i++){
		int sum = 0;
		for(int j = 0; j < col; j++){
			sum += a[j][i];
		}
		cout << "sum of col " << i+1 << " = " << sum << endl;
	}
	cout << "===========================================" << endl;
	//sum of each diagonal
	if(row == col){
		int sum = 0;
		for(int i = 0; i < row; i++){
			sum += a[i][i];
		}
		cout << "sum of diagonal (tl to br) = " << sum << endl;
		sum = 0;
		for(int i = row-1; i >= 0; i--){
			sum += a[i][row-i-1];
		}
		cout << "sum of diagonal (tr to bl) = " << sum << endl;
	}
	
}
