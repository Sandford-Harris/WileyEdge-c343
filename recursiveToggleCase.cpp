#include <iostream>

using namespace std;

string toggleCase(string s){
	
	if(s.length()==0){
		return "";
	}
	else{
		char first = (islower(s[0])) ? toupper(s[0]) : tolower(s[0]);
		string output(1, first);
		return output += toggleCase(s.substr(1, s.length()-1));
	}
}

int main(){
	
	string s;
	getline(cin, s);
	
	string s2 = toggleCase(s);
	cout << s2;
}
