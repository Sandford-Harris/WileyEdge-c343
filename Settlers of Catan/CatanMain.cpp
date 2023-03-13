
#include "Gameboard.h"
#include "Player.h"

using namespace std;

void draft(int *intersectionCursor, int *intersectionRow, int *roadCursor,int *roadRow, Player *p1, Player *p2, Player *p3);
void build(int *intersectionCursor, int *intersectionRow, int *roadCursor,int *roadRow, Player *currentPlayer);
bool placeSettlement(int *cursor, int *row, Player *currentPlayer, bool city, bool draft);
bool placeRoad(int *cursor, int *row, Player *currentPlayer, bool draft);
Player* getNextPlayer(Player *p1, Player *p2, Player *p3, int *current);
void distributeResources(Player *p1, Player *p2, Player *p3, int roll);
int rollDice();

Gameboard *board;

int main(){
	
	board = new Gameboard();
	
	//3 players - not variable in this version
	Player *p1 = new Player(10); //green player
	Player *p2 = new Player(11); //blue player
	Player *p3 = new Player(14); // yellow player
	int playerPtr = 0;
	Player *currentPlayer;
							
	int ch, IntersectionCursor = 0, IntersectionRow = 1, roadCursor = 0, roadRow = 1;
	
	draft(&IntersectionCursor, &IntersectionRow, &roadCursor, &roadRow, p1, p2, p3);
	cin.clear();
	do{
		currentPlayer = getNextPlayer(p1, p2, p3, &playerPtr);
		board->display(-1, -1);
		
		int diceRoll = rollDice();
		diceRoll += rollDice();
		cout << "\nThe dice have rolled " << diceRoll << "! Distributing resources...\n";
		distributeResources(p1, p2, p3, diceRoll);
		
		do{
			cout << endl;
			cout << "\nIt is Player " << playerPtr << "'s Turn.\n";
			cout << "You have " << currentPlayer->getVPs() << "/10 victory points.\n";

			cout << "\nYou have " << currentPlayer->getResourceCount(Player::WHEAT) << " Wheat, "
										<< currentPlayer->getResourceCount(Player::WOOD) << " Wood, "
										<< currentPlayer->getResourceCount(Player::SHEEP) << " Sheep, "
										<< currentPlayer->getResourceCount(Player::ORE) << " Ore, and "
										<< currentPlayer->getResourceCount(Player::CLAY) << " Clay in your hand.\n";
			
			cout << "\nWhat do you want to do?\n";
			cout << "\n1 - Build\n";
			cout << "2 - Trade (NOT IMPLEMENTED)\n";
			cout << "3 - pass Turn\n";
			cout << "4 - Quit\n";
			cout << "=";
			cin >> ch;
			
			switch(ch){
				
				case 1: //place a settlement
					build(&IntersectionCursor, &IntersectionRow, &roadCursor, &roadRow, currentPlayer);
					break;
				case 2: // place road
					break;
				case 3:
					break;
				case 4:
					break;
				default:
					break;
			}
		}while(ch!=3);
		if(currentPlayer->getVPs() >= 10){
			break;
		}
	}while(ch!=4);
	
	if(currentPlayer->getVPs() >= 10){
		cout << "Congratulations player " << playerPtr << "! You've won!" << endl;
	}
}
void draft(int *intersectionCursor, int *intersectionRow, int *roadCursor,int *roadRow, Player *p1, Player *p2, Player *p3){
	
	board->display(-1, -1);
	cout << "\nDrafting...\n";
	
	bool completedAction = false;
	char ch;
	Player *currentPlayer = p1;
	do{
		cout << "Player 1 - place your first settlement:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, true);
	}while(!completedAction);
	do{
		board->display(-1, -1);
		cout << "Player 1 - place your first road:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeRoad(roadCursor, roadRow, currentPlayer, true);
	}while(!completedAction);
	
	currentPlayer = p2;
	do{
		board->display(-1, -1);
		cout << "Player 2 - place your first settlement:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, true);
	}while(!completedAction);
	do{
		board->display(-1, -1);
		cout << "Player 2 - place your first road:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeRoad(roadCursor, roadRow, currentPlayer, true);
	}while(!completedAction);
	
	currentPlayer = p3;
	do{
		board->display(-1, -1);
		cout << "Player 3 - place your first settlement:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, true);
	}while(!completedAction);
	do{
		board->display(-1, -1);
		cout << "Player 3 - place your first road:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeRoad(roadCursor, roadRow, currentPlayer, true);
	}while(!completedAction);
	
	do{
		board->display(-1, -1);
		cout << "Player 3 - place your second settlement:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, true);
	}while(!completedAction);
	do{
		board->display(-1, -1);
		cout << "Player 3 - place your second road:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeRoad(roadCursor, roadRow, currentPlayer, true);
	}while(!completedAction);
	
	currentPlayer = p2;
	do{
		board->display(-1, -1);
		cout << "Player 2 - place your second settlement:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, true);
	}while(!completedAction);
	do{
		board->display(-1, -1);
		cout << "Player 2 - place your second road:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeRoad(roadCursor, roadRow, currentPlayer, true);
	}while(!completedAction);
	
	currentPlayer = p1;
	do{
		board->display(-1, -1);
		cout << "Player 1 - place your second settlement:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, true);
	}while(!completedAction);
	do{
		board->display(-1, -1);
		cout << "Player 1 - place your second road:\nPress any key to continue\n";
		cin >> ch;
		completedAction = placeRoad(roadCursor, roadRow, currentPlayer, true);
	}while(!completedAction);
}

void build(int *intersectionCursor, int *intersectionRow, int *roadCursor,int *roadRow, Player *currentPlayer){
	
	char ch;
	string msg = "";
	bool completedAction = false;
	do{
		completedAction = false;
		board->display(-1, -1);
		cout << msg << endl;
		msg = "";
		cout << endl << "\nYou have " << currentPlayer->getResourceCount(Player::WHEAT) << " Wheat, "
							<< currentPlayer->getResourceCount(Player::WOOD) << " Wood, "
							<< currentPlayer->getResourceCount(Player::SHEEP) << " Sheep, "
							<< currentPlayer->getResourceCount(Player::ORE) << " Ore, and "
							<< currentPlayer->getResourceCount(Player::CLAY) << " Clay in your hand.\n";
									
		cout << "\nWhat do you want to build?\n";
		cout << "\ns - place a settlement | 1 VP | Cost: 1 Wheat, 1 Wood, 1 Clay, 1 Sheep\n";
		cout << "r - place a road | 0 VP | Cost: 1 Wood, 1 Clay\n";
		cout << "c - upgrade a settlement into a city | 2 VP | Cost: 2 Wheat, 3 Ore\n";
		cout << "b - go back\n";
		cout << "=";
		cin >> ch;
		
		switch(ch){
			
			case 's':
				if(currentPlayer->getResourceCount(Player::WHEAT) >= 1 && currentPlayer->getResourceCount(Player::WOOD) >= 1
				&& currentPlayer->getResourceCount(Player::SHEEP) >= 1 && currentPlayer->getResourceCount(Player::CLAY) >= 1){
					*intersectionCursor = 0;
					*intersectionRow = 1;
					completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, false, false);
					
					if(completedAction){
						currentPlayer->addResourceCount(Player::WHEAT, -1);
						currentPlayer->addResourceCount(Player::WOOD, -1);
						currentPlayer->addResourceCount(Player::SHEEP, -1);
						currentPlayer->addResourceCount(Player::CLAY, -1);
						currentPlayer->addVP();
					}
				}
				else{
					msg = "\nYou dont have enough resources to build that!\n";	
				}
				
				break;
			case 'r':
				if(currentPlayer->getResourceCount(Player::WOOD) >= 1 && currentPlayer->getResourceCount(Player::CLAY) >= 1){
					*roadCursor = 0;
					*roadRow = 1;
					completedAction = placeRoad(roadCursor, roadRow, currentPlayer, false);
					if(completedAction){
						currentPlayer->addResourceCount(Player::WOOD, -1);
						currentPlayer->addResourceCount(Player::CLAY, -1);
					}
				}
				else{
					msg = "\nYou dont have enough resources to build that!\n";	
				}
				break;
			case 'c':
				
				if(currentPlayer->getResourceCount(Player::WHEAT) >= 2 && currentPlayer->getResourceCount(Player::ORE) >= 3){
					*intersectionCursor = 0;
					*intersectionRow = 1;
					completedAction = placeSettlement(intersectionCursor, intersectionRow, currentPlayer, true, false);
					
					if(completedAction){
						currentPlayer->addResourceCount(Player::WHEAT, -2);
						currentPlayer->addResourceCount(Player::ORE, -3);
						currentPlayer->addVP();
					}
				}
				else{
					msg = "\nYou dont have enough resources to build that!\n";	
				}
				
				break;
			case 'b':
				break;
			default:
				msg = "\nInvalid input\n";
				break;
				
		}
		
		
	}while(ch!='b');
}

bool placeSettlement(int *cursor, int *row, Player *currentPlayer, bool city, bool draft){
	
	int cursorPoints[54] = {3,0,4,1,5,2,6,
							11,7,12,8,13,9,14,10,15,
							21,16,22,17,23,18,24,19,25,20,26,
							27,33,28,34,29,35,30,36,31,37,32,
							38,43,39,44,40,45,41,46,42,
							47,51,48,52,49,53,50};
	
	int currentplayerID = currentPlayer->getID();
	int choice;
	bool completedAction = false;
	do{
		
		board->display(cursorPoints[*cursor], 0);
		cout << endl << "Hit enter to choose your location or use arrow keys to move the cursor. 'b' for back." << endl;
		choice = getch();
		switch(choice){
			
			case '\r':
				if(board->getIntersectionOwner(*cursor)->getOwnerID() == -1 && !city){
					vector<Tile*> tilesAtCursor = board->getTilesAtIntersection(*cursor);
					for(int i = 0; i < tilesAtCursor.size(); i++){
						for(int j = 0; j < 6; j++){
							if(board->getIntersectionOwner(*cursor)->getID() == tilesAtCursor.at(i)->getIntersection(j)->getID()){
								switch(j){
									case 0: //TL - next to T, BL
										tilesAtCursor.at(i)->setIntersectionOwnerID(1, -2);//set T inaccessible
										tilesAtCursor.at(i)->setIntersectionOwnerID(3, -2);//set BL inaccessible
										break;
									case 1: //T - next to TL, TR
										tilesAtCursor.at(i)->setIntersectionOwnerID(0, -2);//set TL inaccessible
										tilesAtCursor.at(i)->setIntersectionOwnerID(2, -2);//set TR inaccessible
										break;
									case 2: // TR - next to T, BR
										tilesAtCursor.at(i)->setIntersectionOwnerID(1, -2);//set T inaccessible
										tilesAtCursor.at(i)->setIntersectionOwnerID(5, -2);//set BR inaccessible
										break;
									case 3: // BL - next to TL, B
										tilesAtCursor.at(i)->setIntersectionOwnerID(0, -2);//set TL inaccessible
										tilesAtCursor.at(i)->setIntersectionOwnerID(4, -2);//set B inaccessible
										break;
									case 4: // B - next to BL, BR
										tilesAtCursor.at(i)->setIntersectionOwnerID(3, -2);//set BL inaccessible
										tilesAtCursor.at(i)->setIntersectionOwnerID(5, -2);//set BR inaccessible
										break;
									case 5: // BR - next B, TR
										tilesAtCursor.at(i)->setIntersectionOwnerID(4, -2);//set B inaccessible
										tilesAtCursor.at(i)->setIntersectionOwnerID(2, -2);//set TR inaccessible
										break;
									default:
										break;
								}
							}
						}
					}
					board->getIntersectionOwner(*cursor)->setOwnerID(currentplayerID);
					board->getIntersectionOwner(*cursor)->setTokenType(Intersection::TOWN);
					completedAction = true;
				}
				else if(board->getIntersectionOwner(*cursor)->getOwnerID() == currentplayerID && city){
					if(board->getIntersectionOwner(*cursor)->getTokenType() == Intersection::TOWN){
						board->getIntersectionOwner(*cursor)->setTokenType(Intersection::CITY);
						completedAction = true;
					}
				}
				else{
					if(city){
						cout << "\nInvalid choice! Can only place on your own existing settlements\n";
					}
					else if(board->getIntersectionOwner(*cursor)->getOwnerID() == -2){
						cout << "\nInvalid choice! Too close to existing settlement\n";
					}
					else{
						cout << "\nInvalid choice! position is already owned\n";
					}
					choice = -1;
				}
				break;
			default:
				choice = getch();
				if(choice == 'b') break;
				board->moveIntersectionCursor(choice, cursor, row);
				break;
		}
		
	}while(choice != '\r' && choice != 'b');
	return completedAction;
}

bool placeRoad(int *cursor, int *row, Player *currentPlayer, bool draft){
	
	int choice;
	string msg;
	bool completedAction = false;
	do{
		board->display(*cursor, 1);
		cout << msg << endl;
		msg = "";
		cout << endl << "Hit enter to choose your location or use arrow keys to move the cursor. 'b' for back." << endl;
		choice = getch();
		int currentplayerID = currentPlayer->getID(); 
		switch(choice){
			
			case '\r':
				if(board->getEdgeOwner(*cursor)->getOwnerID() == -1){
					vector<Tile*> tilesAtEdge = board->getTilesAtEdge(*cursor);
					bool ownsAdjacent = false;
					for(int i = 0; i < tilesAtEdge.size(); i++){
						for(int j = 0; j < 6; j++){
							if(board->getEdgeOwner(*cursor)->getID() == tilesAtEdge.at(i)->getEdge(j)->getID()){
								//check intersections and edges
								switch(j){
										case 0: //TL 
											if(tilesAtEdge.at(i)->getIntersection(0)->getOwnerID() == currentplayerID 
											|| tilesAtEdge.at(i)->getIntersection(1)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(1)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(2)->getOwnerID() == currentplayerID){
												ownsAdjacent = true;
											}
											break;
										case 1: //TR 
											if(tilesAtEdge.at(i)->getIntersection(1)->getOwnerID() == currentplayerID 
											|| tilesAtEdge.at(i)->getIntersection(2)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(0)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(3)->getOwnerID() == currentplayerID){
												ownsAdjacent = true;
											}
											break;
										case 2: // L 
											if(tilesAtEdge.at(i)->getIntersection(0)->getOwnerID() == currentplayerID 
											|| tilesAtEdge.at(i)->getIntersection(3)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(0)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(4)->getOwnerID() == currentplayerID){
												ownsAdjacent = true;
											}
											break;
										case 3: // R 
											if(tilesAtEdge.at(i)->getIntersection(2)->getOwnerID() == currentplayerID 
											|| tilesAtEdge.at(i)->getIntersection(5)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(1)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(5)->getOwnerID() == currentplayerID){
												ownsAdjacent = true;
											}
											break;
										case 4: // BL
											if(tilesAtEdge.at(i)->getIntersection(3)->getOwnerID() == currentplayerID 
											|| tilesAtEdge.at(i)->getIntersection(4)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(2)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(5)->getOwnerID() == currentplayerID){
												ownsAdjacent = true;
											}
											break;
										case 5: // BR 
											if(tilesAtEdge.at(i)->getIntersection(4)->getOwnerID() == currentplayerID 
											|| tilesAtEdge.at(i)->getIntersection(5)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(4)->getOwnerID() == currentplayerID
											|| tilesAtEdge.at(i)->getEdge(3)->getOwnerID() == currentplayerID){
												ownsAdjacent = true;
											}
											break;
										default:
											break;
									}
							}
						}
					}
					if(ownsAdjacent){
						board->getEdgeOwner(*cursor)->setOwnerID(currentplayerID);
						board->getEdgeOwner(*cursor)->setTokenType(Intersection::ROAD);
						completedAction = true;
					}
					else{
						msg =  "\nInvalid choice! can only place roads next to your own infrastructure\n";
						choice = -1;
					}
				}
				else{
					msg =  "\nInvalid choice! position is already owned\n";
					choice = -1;
				}
				break;
			default:
				choice = getch();
				if(choice == 'b') break;
				board->moveEdgeCursor(choice, cursor, row);
				break;
		}
		
	}while(choice != '\r' && choice != 'b');
	return completedAction;
}

Player* getNextPlayer(Player *p1, Player *p2, Player *p3, int *current){
	if(*current == 1){
		*current = 2;
		return p2;
	}
	else if(*current == 2){
		*current = 3;
		return p3;
	}
	else{
		*current = 1;
		return p1;
	}
}

void distributeResources(Player *p1, Player *p2, Player *p3, int roll){
	
	string resourceNames[5] = { "Wheat", "Wood", "Sheep", "Ore", "Clay" };
	for(int i = 0; i < 19; i++){
		if(board->getTile(i)->getNumberToken() == roll){
			for(int j = 0; j < 6; j++){
				if(board->getTile(i)->getIntersection(j)->getOwnerID() > -1){
					Player::Resource resource = (Player::Resource)(board->getTile(i)->getTerrainType()-1);
					int amount = (int)(board->getTile(i)->getIntersection(j)->getTokenType());
					
					if(board->getTile(i)->getIntersection(j)->getOwnerID() == p1->getID()){
						p1->addResourceCount(resource, amount);
						cout << "Player 1 got " << amount << " " << resourceNames[(int)resource] << "!" << endl; 
					}
					else if(board->getTile(i)->getIntersection(j)->getOwnerID() == p2->getID()){
						p2->addResourceCount(resource, amount);
						cout << "Player 2 got " << amount << " " << resourceNames[(int)resource] << "!" << endl; 
					}
					else if(board->getTile(i)->getIntersection(j)->getOwnerID() == p3->getID()){
						p3->addResourceCount(resource, amount);
						cout << "Player 3 got " << amount << " " << resourceNames[(int)resource] << "!" << endl; 
					}
				}
			}
		}
	}
}

int rollDice(){
	return rand() % 6 + 1;
}

