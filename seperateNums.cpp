#include <iostream>

using namespace std;

void separateNums(string s, string &lets, int &nums){

	if(s.length() == 0){
		return;
	}
	else{
		if(isalpha(s[0])) lets += s[0];
		else if(isdigit(s[0])) nums = (nums*10) + (s[0] - '0');
		separateNums(s.substr(1, s.length()-1), lets, nums);
	}
}

int main(){
	
	string s;
	cin >> s;
	//string s = "am3n45jj677";
	
	string letters = "";
	int numbers = 0;
	separateNums(s, letters, numbers);
	cout << letters << endl;
	cout << numbers << endl;
}
