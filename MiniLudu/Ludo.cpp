#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LudoList.h"

using namespace std;

enum Direction{
	
	UP = 1,
	LEFT = 2,
	DOWN = 3,
	RIGHT = 4
};

enum Turn{
	
	PLAYER_1 = 1,
	PLAYER_2 = 2,
	PLAYER_3 = 3,
	PLAYER_4 = 4
};

struct Player{
	
	Node *boardTile;
	int pos;
	int boardPos;
	int boardStartPos;
	Direction dir;
	
	Player(int boardStartPos, Direction dir){
		this->boardStartPos = boardStartPos;
		this->dir = dir;
		this->boardPos = boardStartPos;
		
		this->pos = 0;
		this->boardTile = getBoardTile(boardPos);
	}
	
	void reset(int n){
		this->dir = (Direction)n;
		this->boardPos = boardStartPos;
		this->pos = 0;
		this->boardTile = getBoardTile(boardPos);
	}
};

void changeDirection(Direction dir);
int movePlayer(Player *player, int toMove);
void updateBoardPosition(Player *player);
void checkKills(Player *current, Player *player1, Player *player2, Player *player3, Player *player4, int boardPos);
bool safecheck(int pos);
string locationcheckmultiple(int p1, int p2, int p3, int p4);
int locationcheckmultiplepos(int p1, int p2, int p3, int p4);
void display(Player *p1, Player *p2, Player *p3, Player *p4);
int rollDice();

int safeSpots[12] = {1, 4, 7, 9, 13, 22, 28, 37, 41, 43, 46, 49};
int turningPoints[13] = {3, 9, 15, 21, 22, 27, 31, 35, 38, 41, 43, 45, 46};

int main(){
	
	//seed random for variance
	srand(time(NULL));
	
	//initialise list values
	head = NULL;
	cnt = 0;
	//setup board and players
	initialiseBoard(49, safeSpots, 12);
	Player *p1 = new Player(28, UP);
	Player *p2 = new Player(4, LEFT);
	Player *p3 = new Player(22, DOWN);
	Player *p4 = new Player(46, RIGHT);
	
	char ch;
	int diceRoll;
	Turn currentPlayer = PLAYER_1;
	vector<int> winners;
	bool hasWon[4] = {false, false, false, false};
	
	do{
		
		display(p1, p2, p3 ,p4);
		
		cout << "\nIt is Player " << currentPlayer << "'s turn." << endl;
		cout << "Press any key to roll or press x to exit\n=";
		cin >> ch;
		
		Player *current;
		if(currentPlayer == PLAYER_1) current = p1;
		else if(currentPlayer == PLAYER_2) current = p2;
		else if(currentPlayer == PLAYER_3) current = p3;
		else current = p4;
		
		switch(ch){
			
			case 'x':
				break;
			default:
				diceRoll = rollDice();
				cout << "\nPlayer " << currentPlayer << " rolled a " << diceRoll << endl;
				if(diceRoll + current->pos > 47){ // player has overshot the goal
					cout << "You rolled too high! need to roll " <<  47-(current->pos) << " or less.\n";
					break;
				}
				else if(diceRoll + current->pos == 47){ // player has landed on the goal.
					cout << "\nPlayer " << currentPlayer << " has reached the goal!\n";
					winners.push_back(currentPlayer);
					hasWon[currentPlayer-1] = true;
					movePlayer(current, diceRoll);
					break;
				}
				else{
					int newBoardPos = movePlayer(current, diceRoll);
					checkKills(current, p1, p2, p3, p4, newBoardPos);
					cout << "\nPlayer " << currentPlayer << " is now " << 47-(current->pos) << " steps from the goal\n";
				}
				break;
		}
		
		do{
			if(currentPlayer == PLAYER_1) currentPlayer = PLAYER_2;
			else if(currentPlayer == PLAYER_2) currentPlayer = PLAYER_3;
			else if(currentPlayer == PLAYER_3) currentPlayer = PLAYER_4;
			else currentPlayer = PLAYER_1;	
		}while(hasWon[currentPlayer-1] == true);
		
		
		
	}while(ch!='x' && winners.size() < 3);
	
	display(p1, p2, p3 ,p4);
	
	if(winners.size() == 3){
		cout << "\n1st place - Player " << winners.at(0) << endl;
		cout << "\n2nd place - Player " << winners.at(1) << endl;
		cout << "\n3rd place - Player " << winners.at(2) << endl;
	}
	
}

Direction changeDirection(Direction dir, int pos){
	
	if(pos < 27){
		if(dir == UP){
			return LEFT;
		}
		else if(dir == LEFT){
			return DOWN;
		}
		else if(dir == DOWN){
			return RIGHT;
		}
		else if(dir == RIGHT){
			return UP;
		}
	}
	else{
		if(dir == UP){
			return RIGHT;
		}
		else if(dir == RIGHT){
			return DOWN;
		}
		else if(dir == DOWN){
			return LEFT;
		}
		else if(dir == LEFT){
			return UP;
		}
	}
}

//moves a given player toMove tiles along the board;
int movePlayer(Player *player, int toMove){
	
	if(toMove <= 0){
		return player->boardPos;
	}
	else{
		//update board position
		updateBoardPosition(player);
		player->pos++;
		toMove--;
		//change direction if at turning point
		for(int i = 0; i < 13; i++){
			if(player->pos == turningPoints[i]){
				player->dir = changeDirection(player->dir, player->pos);
				break;
			}
		}
		return movePlayer(player, toMove);
	}
}

//moves player its next position on the board
void updateBoardPosition(Player *player){
	
	if(player->dir == UP){
		player->boardPos -= 7;
	}
	else if(player->dir == DOWN){
		player->boardPos += 7;
	}	
	else if(player->dir == LEFT){
		player->boardPos -= 1;
	}
	else if(player->dir == RIGHT){
		player->boardPos += 1;
	}
	
	player->boardTile = getBoardTile(player->boardPos);
}

//kills players if they are on an unsafe tile 
void checkKills(Player *current, Player *player1, Player *player2, Player *player3, Player *player4, int boardPos){
	
	Node *boardTile = getBoardTile(boardPos);
	if(!(boardTile->safe)){
		//if any player is on boardTile, then reset them to starting state
		if(player1->boardTile == boardTile && player1 != current){
			player1->reset(1);
			cout << "player 1 was killed!" << endl;
		}
		if(player2->boardTile == boardTile && player2 != current){
			player2->reset(2);
			cout << "player 2 was killed!" << endl;
		}
		if(player3->boardTile == boardTile && player3 != current){
			player3->reset(3);
			cout << "player 3 was killed!" << endl;
		}
		if(player4->boardTile == boardTile && player4 != current){
			player4->reset(4);
			cout << "player 4 was killed!" << endl;
		}
	}
}

int rollDice(){
	
	return rand() % 4 + 1;
}

bool safecheck(int pos) {
	for (int i = 0; i < sizeof(safeSpots)/sizeof(int); i++) {
		if (pos == safeSpots[i]) {
			return true;
		} 	
	}
	return false;
}

string locationcheckmultiple(int p1, int p2, int p3, int p4) {
	if (p1 == p2 && p1 == p3 && p1 == p4) {
		return "1,2,3,4|";
	} else if (p1 == p2 && p1 == p3) {
		return " 1,2,3 |";
	} else if (p1 == p2 && p1 == p4) {
		return " 1,2,4 |";
	} else if (p2 == p3 && p2 == p4) {
		return " 2,3,4 |";
	} else if (p1 == p2) {
		return "  1,2  |";
	} else if (p1 == p3) {
		return "  1,3  |";
	} else if (p1 == p4) {
		return "  1,4  |";
	} else if (p2 == p3) {
		return "  2,3  |";
	} else if (p2 == p4) {
		return "  2,4  |";
	} else if (p3 == p4) {
		return "  3,4  |";
	} else {
		return "";
	}
}

int locationcheckmultiplepos(int p1, int p2, int p3, int p4) {
	if (p1 == p2 == p3 == p4) {
		return p1;
	} else if (p1 == p2 == p3) {
		return p1;
	} else if (p1 == p2 == p4) {
		return p1;
	} else if (p2 == p3 == p4) {
		return p2;
	} else if (p1 == p2) {
		return p1;
	} else if (p1 == p3) {
		return p1;
	} else if (p1 == p4) {
		return p1;
	} else if (p2 == p3) {
		return p2;
	} else if (p2 == p4) {
		return p2;
	} else if (p3 == p4) {
		return p3;
	} else {
		return 0;
	}
}

void display(Player *p1, Player *p2, Player *p3, Player *p4) {
	cout << "|";
	for (int i = 1; i <= 49; i++) {
		string mult = locationcheckmultiple(p1 -> boardPos, p2 -> boardPos, p3 -> boardPos, p4 -> boardPos);
		int multpos = locationcheckmultiplepos(p1 -> boardPos, p2 -> boardPos, p3 -> boardPos, p4 -> boardPos);
		if (i == multpos) {
			cout << mult;
		} else if (p1 -> boardPos == i) {
			cout << "   1   |";
		} else if (p2 -> boardPos == i) {
			cout << "   2   |";
		} else if (p3 -> boardPos == i) {
			cout << "   3   |";
		} else if (p4 -> boardPos == i) {
			cout << "   4   |";
		} else if (safecheck(i) == true) {
			cout << "   S   |";
		} else if (i == 25) {
			cout << "   F   |";
		} else {
			cout << "       |";
		}
		if (i % 7 == 0) {
			cout << "|" << endl << "|";
		}
	}
		 
}

