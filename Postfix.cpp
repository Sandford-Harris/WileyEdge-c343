#include <iostream>

using namespace std;

struct Stack{

	int top;
	int stackMax;
	char *stack;
	
	Stack(int max){
		
		top = 0;
		stack = new char[max];
		stackMax = max;
	}
	
	//add character to the top of the stack
	void push(char op){
		if(top < stackMax){
			stack[top] = op;
			top++;
		}
		else{
			cout << "ERROR: Stack full" << endl;
		}
	}
	
	//remove the top element of the stack and return it
	char pop(){
		if(top > 0){
			char c = stack[top-1];
			top--;
			return c;
		}
		else{
			return '\0';
		}
	}
	
	//return the top element of the stack without removing it
	char peek(){
		if(top > 0){
			char c = stack[top-1];
			return c;
		}
		else{
			return '\0';
		}
	}

};

bool checkPrecedence(char a, char b);

int main(){
	
	Stack operands = Stack(10);
	string postfix = "", exp;
	
	cout << "Enter an expression: ";
	cin >> exp;
	
	Stack brackets = Stack(10);
	bool unequal = false;
	for(int i=0; i < exp.size(); i++){
		if(exp[i] == '{' || exp[i] == '(' || exp[i] == '[') brackets.push(exp[i]);
		else if(exp[i] == '}'){
			if(brackets.peek() == '{') brackets.pop();
			else {
				unequal = true;
				break;
			}
		}
		else if(exp[i] == ')'){
			if(brackets.peek() == '(') brackets.pop();
			else {
				unequal = true;
				break;
			}
		}
		else if(exp[i] == ']'){
			if(brackets.peek() == '[') brackets.pop();
			else {
				unequal = true;
				break;
			}
		}
	}
	unequal = (brackets.peek() != '\0');
	if(unequal){
		cout << "Unequal brackets or braces" << endl;
		return 0;
	} 
	
	for(int i=0; i < exp.size(); i++){
		
		cout << "element to process = " << exp[i] << ": ";
		if(isalpha(exp[i])){
			cout << "is alpha" << endl;
			postfix += exp[i];
		}
		else if(operands.peek() == '\0' || operands.peek() == '('){
			cout << "pushing to stack" << endl;
			operands.push(exp[i]);
		}
		else if(exp[i] == '('){
			cout << "pushing to stack" << endl;
			operands.push(exp[i]);
		}
		else if(exp[i] == ')'){
			cout << "popping stack till '(' " << endl;
			char c = operands.pop();
			while(c != '\0'){
				if(c == '(')
					break;
				postfix += c;
				c = operands.pop();
			}
		}
		else if (checkPrecedence(exp[i], operands.peek())){
			cout << "higher precedence - pushing to stack" << endl;
			operands.push(exp[i]);
		}
		else{
			cout << "lower precedence - popping till higher" << endl;
			char c = operands.pop();
			while(c != '\0'){
				postfix += c;
				if(checkPrecedence(exp[i], operands.peek())){
					operands.push(exp[i]);
					break;
				}
				c = operands.pop();
			}
		}
	}
	//pop remaing on stack to postfix
	char c = operands.pop();
	while(c != '\0'){
		postfix += c;
		c = operands.pop();
	}

	cout << "postfix = " << postfix << endl;
}

bool checkPrecedence(char a, char b){ // returns true if a has a higher precedence than b
	
	if(a == '^' || a == b){
		return true;
	}
	else if(a == '*' && b != '^'){
		return true;
	}
	else if(a == '/' && b != '^' && b != '*'){
		return true;
	}
	else if(a == '+' && b != '^' && b != '*' && b != '/'){
		return true;
	}
	else if(a == '-' && b != '^' && b != '*' && b != '/' && b != '+'){
		return true;
	}
	else{
		return false;
	}
}
