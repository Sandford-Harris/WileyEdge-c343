#include <iostream>

using namespace std;

bool checkPalindrome(string s){
	
	if(s.length() <= 1){
		return true;
	}
	else if(s[0] != s[s.length()-1]){
		return false;
	}
	else{
		return checkPalindrome(s.substr(1, s.length()-2));
	}
}

int main(){
	
	string s;
	cin >> s;
	
	bool palindrome = checkPalindrome(s);
	cout << s << ((checkPalindrome(s)) ? " is a palindrome" : " is not a palindrome") << endl;

}
