#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countOccurances(vector<string>, string, int n=0);

int main(){
	
	vector<string> s1;
	string s,s2;
	while(cin >> s){
		s1.push_back(s);
	}
	cin >> s2;
	int x = countOccurances(s1, s2);
	cout << s2 << " occured " << x << " times" << endl;
}

//this is not working

int countOccurances(vector<string> s1, string s2, int n){
	
	if(s1.size() == 0) return n;
	else{
		string s = s1.back();
		if(s2 == s){
			n++;
		}
		s1.pop_back();
		return countOccurances(s1, s2, n);
	}
}
