#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int rollDice();
void populateGameboard(char*, int);
void displayGameboard(char*, int, int, int);

enum Turn {
		PLAYER_1_TURN = 1,
		PLAYER_2_TURN = 2
	};

int main(){
	
	//seed random for variance in games
	
	//start position is -1 (starting at 0 off the board)
	
	int seed = time(NULL);
	srand(seed);
	
	int p1pos = -1, p2pos = -1, tileCount = 100, diceRoll;
	
	Turn currentTurn = PLAYER_1_TURN;
	char *gameboard = new char[tileCount];
	
	populateGameboard(gameboard, tileCount);
	displayGameboard(gameboard, tileCount, p1pos, p2pos);
	
	char ch;
	do{
		cout << "It is Player " << currentTurn << "'s turn.\nr - roll dice\nx - exit\n=";
		cin>> ch;
		
		int pos = -1;
		switch(ch){
			case 'r':
			{
				//calculate the amount the player should move
				diceRoll = rollDice();
				cout << "You rolled a  " << diceRoll << "!" << endl;
				
				//workout which player should be moving and find their new position
				pos = (currentTurn == PLAYER_1_TURN) ? p1pos : p2pos;
				pos += diceRoll;
				//if player position is >= tileCount, the game ends
				if(pos >= tileCount){
					pos = tileCount-1; // set pos to tileCount-1 so player is displayed if over
					break;
				}
					
				char tile = gameboard[pos];
				if(tile == 'a' || tile == 'b' || tile == 'c' || tile == 'd'){ //player is on a ladder
					//find the end of the same ladder and set player position to be there
					for(int i = pos+1; i < tileCount; i++){
						if(gameboard[i] == tile){
							pos = i;
							cout << "You've landed on a ladder!" << endl;								
						}
					}
				}
				else if(tile == 'z' || tile == 'y' || tile == 'x'){ //player is on a snake
					//find the end of the same snake and set player position to be there
					for(int i = pos-1; i >= 0; i--){
						if(gameboard[i] == tile){
							cout << "You've landed on a snake!" << endl;
							pos = i;
						}
					}
				}
				cout << "Player " << currentTurn << " is now at position " << pos + 1 << endl;	
				break;	
			}	
			case 'x':
				"Goodbye!";
				break;
		}
		
		//update the current players position and switch turns
		if(currentTurn == PLAYER_1_TURN){
			p1pos = pos;
			currentTurn = PLAYER_2_TURN;
		}
		else{
			p2pos = pos;
			currentTurn = PLAYER_1_TURN;
		}
		//display the current state of the gameboard
		displayGameboard(gameboard, tileCount, p1pos, p2pos);
		
		
	}while(p1pos < tileCount-1 && p2pos < tileCount-1 && ch != 'x');
	
	//if the game was won, output a win message
	if(p1pos >= tileCount-1)
		cout << "Congratulations player 1! You've won!";
	else if (p2pos >= tileCount-1)
		cout << "Congratulations player 2! You've won!";
	
}

//return a random value between 1 and 6

int rollDice(){
	
	return rand() % 6 + 1;
}

//function to fill all tiles of the game board with the correct elements
void populateGameboard(char *gameboard, int tileCount){
	
	for(int i = 0; i < tileCount; i++){
		if(i == 5 || i == 45) // ladder 1
			gameboard[i] = 'a';
		else if(i == 18 || i == 42) // ladder 2
			gameboard[i] = 'b';
		else if(i == 51 || i == 70) // ladder 3
			gameboard[i] = 'c';
		else if(i == 56 || i == 97) // ladder 4
			gameboard[i] = 'd';
		else if(i == 8 || i == 46) // snake 1
			gameboard[i] = 'z';
		else if(i == 39 || i == 61) // snake 2
			gameboard[i] = 'y';
		else if(i == 74 || i == 95) // snake 3
			gameboard[i] = 'x';
		else						//empty square
			gameboard[i] = 's';
	}
}

//function to display the current board state
void displayGameboard(char *gameboard, int tileCount, int p1pos, int p2pos){
	
	int rowdir = 0; // 0 = left to right, 1 = right to left
	int counter = 0; //counter to increment on right to left rows
	for(int i = tileCount-1; i >= 0; i--){
		cout << "[";
		
		//set the current tile to be gameboard[i] if the row is moving left to right (100, 99, 88...)
		//set the current tile to be gameboard[i - (i%10) + counter] if the row is moving right to left (1, 2, 3...)
		int tileInd = (rowdir == 0) ? i : i - (i%10) + counter;
		char tile = gameboard[tileInd];
		
		//output x if player 1 is on the tile
		if(rowdir == 0 && tileInd == p1pos) cout << "x";
		else if(rowdir == 1 && tileInd == p1pos) cout << "x";
		else cout << " ";
		
		//if the tile has a ladder output 'lx' where x is the ladder id 
		if(tile == 'a' || tile == 'b' || tile == 'c' || tile == 'd') cout << "L" << tile - 'a' + 1;
		//if the tile has a snake output 'sx' where x is the snake id 
		else if(tile == 'z' || tile == 'y' || tile == 'x') cout << "S" << 'z' - tile + 1;
		//if the tile is empty output its number on the grid;
		else{
			if(tileInd == 99) cout << "$$";
			else cout << tileInd+1; 
			if(tileInd+1 < 10) cout << " ";
		}
		
		//output + if player 2 is on the tile
		if(rowdir == 0 && i == p2pos) cout << "+";
		else if(rowdir == 1 && tileInd == p2pos) cout << "+";
		else cout << " ";
			
		cout << "]";			
		
		//swap rowdir every 10 tiles and start a new row
		if(i%10 == 0){
			rowdir = (rowdir == 0) ? 1 : 0;
			counter = 0;
			
			cout << endl;
		}else counter++;
	}
}



