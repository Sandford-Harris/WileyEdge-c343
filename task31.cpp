#include <iostream>

using namespace std;

int main(){
	
	int maxLen = 100;
	char *s = new char[maxLen];

	cout << "Enter a Sentence: ";
	gets(s);
	
	char prev = s[0];
	for(int i = 0; i < maxLen; i++){
		
		if(s[i] == '\0'){
			break;
		}
		if(s[i] != ' '){
			cout << s[i];
		}
		else if(s[i] == ' ' && prev != ' '){
			cout << " ";
		}
		prev = s[i];
	}
}
