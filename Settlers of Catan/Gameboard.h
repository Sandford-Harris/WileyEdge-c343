#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <tr1/memory>
#include <conio.h>
#include <windows.h>

#include "Tile.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

class Gameboard{
	
	private:
		vector<Tile*> tiles; //1 desert, 4 fields, 4 forest, 4 pasture, 3 mountains, 3 Hills
		vector<int> numberTokens; //index in numbertokens is index of tile with that number in tiles
		int intersectionMap[54] = {1,3,5,0,2,4,6,
									8,10,12,14,7,9,11,13,15,
									17,19,21,23,25,16,18,20,22,24,26,
									27,29,31,33,35,37,28,30,32,34,36,
									38,40,42,44,46,39,41,43,45,
									47,49,51,53,48,50,52};
		void init(){
			int tokensToAdd[18] = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
			int tilesToAdd[19] = { 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5 };
			//randomly shuffle the order so when added the board is random each time
			random_shuffle(&tokensToAdd[0], &tokensToAdd[18]);
			random_shuffle(&tilesToAdd[0], &tilesToAdd[19]);
			int tokenCounter = 0;
			for(int i = 0; i < 19; i++){
				Tile *t;
				if(tilesToAdd[i] == 0){
					t = new Tile((TerrainType)tilesToAdd[i], -1);
					numberTokens.at(i) = -1;
				}
				else{
					t = new Tile((TerrainType)tilesToAdd[i], tokensToAdd[tokenCounter]);
					numberTokens.at(i) = tokensToAdd[tokenCounter];
					tokenCounter++;
				}
				tiles.push_back(t);
			}
			
			placeEdges();
			placeIntersections();
		}
		void placeEdges(){
			
			//72 unique edges
			vector<std::tr1::shared_ptr<Intersection> > e;
			for(int i = 0; i < 72; i++){
				std::tr1::shared_ptr<Intersection> edge(new Intersection(Intersection::EDGE, i));
				e.push_back(edge);
			}
			
			int top = 0, side = 6, bot = 11;
			for(int i = 0; i < tiles.size(); i++){
				if(i==0){
				}
				tiles.at(i)->addEdges(&e.at(top), &e.at(top+1), &e.at(side), &e.at(side+1), &e.at(bot), &e.at(bot+1));
				if(i == 2){
					top = 10;
					side = 18;
					bot = 24;
				}
				else if(i == 6){
					top = 23;
					side = 33;
					bot = 39;
				}
				else if(i == 11){
					top = 40;
					side = 49;
					bot = 54;
				}
				else if(i == 15){
					top = 55;
					side = 62;
					bot = 66;
				}
				else{
					top += 2;
					side += 1;
					bot += 2;
				}
			}
			
		}
		void placeIntersections(){
			//54 unique intersections
			vector<std::tr1::shared_ptr<Intersection> > ints;
			for(int i = 0; i < 54; i++){
				std::tr1::shared_ptr<Intersection> inter(new Intersection(Intersection::CORNER, i));
				ints.push_back(inter);
			}
			int top = 0, bot = 8;
			for(int i = 0; i < tiles.size(); i++){
				if(i==0){
				}
				tiles.at(i)->addIntersections(&ints.at(top), &ints.at(top+1), &ints.at(top+2), &ints.at(bot), &ints.at(bot+1), &ints.at(bot+2));
				if(i == 2){
					top = 7;
					bot = 17;
				}
				else if(i == 6){
					top = 16;
					bot = 27;
				}
				else if(i == 11){
					top = 28;
					bot = 38;
				}
				else if(i == 15){
					top = 39;
					bot = 47;
				}
				else{
					top += 2;
					bot += 2;
				}
			}
		}
		
	public:
		Gameboard(){
			srand(time(NULL));
			numberTokens.resize(19, -1);
			init();
		}
		Tile* getTile(int index){
			if(index < 19){
				return tiles.at(index);
			}
			return NULL;
		}
		//returns all tiles that contain intersection with id intId
		vector<Tile*> getTilesAtIntersection(int intId){
			vector<Tile*> tilesAtIntersection;
			for(int i = 0; i < tiles.size(); i++){
				for(int j = 0; j < 6; j++){
					if(tiles.at(i)->getIntersection(j)->getID() == intId){
						tilesAtIntersection.push_back(tiles.at(i));
					}
				}
			}
			return tilesAtIntersection;
		}
		//returns all tiles that contain edge with id edgeId
		vector<Tile*> getTilesAtEdge(int edgeId){
			vector<Tile*> tilesAtEdge;
			for(int i = 0; i < tiles.size(); i++){
				for(int j = 0; j < 6; j++){
					if(tiles.at(i)->getEdge(j)->getID() == edgeId){
						tilesAtEdge.push_back(tiles.at(i));
					}
				}
			}
			return tilesAtEdge;
		}
		void display(int cursor, int cursorType){
			
			system("CLS");
			
			//70 columns wide
			//top row (may have settlements here eventually)
			for(int i = 0; i < 70; i++){
				cout << " ";
			}
			cout << endl;
			//pointer to keep track of how many potential cursor positions have been passed
			int ptr = 0, edgeIndex = 0, intersectionIndex = 0;
			//row 1
			drawTriangles(24, 3, false, &ptr, cursor, cursorType, &edgeIndex, &intersectionIndex);
			drawTiles(19, 0, 3, &ptr, cursor, cursorType, &edgeIndex);
			//row 2
			drawTriangles(17, 4, false, &ptr, cursor, cursorType, &edgeIndex, &intersectionIndex);
			drawTiles(12, 3, 7, &ptr, cursor, cursorType, &edgeIndex);
			//row 3
			drawTriangles(10, 5, false, &ptr, cursor, cursorType, &edgeIndex, &intersectionIndex);
			drawTiles(5, 7, 12, &ptr, cursor, cursorType, &edgeIndex);
			//row 4
			drawTriangles(17, 4, true, &ptr, cursor, cursorType, &edgeIndex, &intersectionIndex);
			drawTiles(12, 12, 16, &ptr, cursor, cursorType, &edgeIndex);
			//row 5
			drawTriangles(24, 3, true, &ptr, cursor, cursorType, &edgeIndex, &intersectionIndex);
			drawTiles(19, 16, 19, &ptr, cursor, cursorType, &edgeIndex);
			drawTriangles(31, 2, true, &ptr, cursor, cursorType, &edgeIndex, &intersectionIndex);
			//bottom row (may have settlements here eventually)
			for(int i = 0; i < 70; i++){
				cout << " ";
			}
			cout << endl;
		}
		//draws the slanted edges of the hexagons
		//startind = offset from left edge of the screen
		//num = how many triangles to draw (num = 2 draws /\/\ )/
		//bottomRow = if the draws extra slants at the start and end of the row (num = 2 draws \/\/\/ )
		//ptr = cursor positions passed 
		//cursor = the position the cursor should be printed in
		//cursorType = where to draw the cursor depending on what is being selected, 0 = intersection, 1 = edge
		void drawTriangles(int startInd, int num, bool bottomRow, int *ptr, int cursor, int cursorType, int *edgeInd, int *intInd){ 
		
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for colour printing
			
			if(startInd < 4) startInd = 4; //ensure there is always enough space to print 
			int initialStart = startInd;
			
			int lineLength = (initialStart-4-num) + (13 * num); //a line should be triangle width * num triangles + a buffer
			if(bottomRow) lineLength += 4; // extra line length so an upward slant is printed at the end
			
			bool capAdded, firstLineColoured = false, secondLineColoured = false;
			int line1colptr = *ptr, line2colptr = 0;
			for(int i = 0; i < 3; i++){
				//at what point the decending edge should be printed at on each row, spaces the triangle edges out from top down
				int decendingInd = startInd + (4*i)+2;
				capAdded = false;
				for(int j = 0; j < lineLength; j++){
					//print a leading decending row once if the row is a bottomRow
					if(bottomRow && !capAdded){
						//if drawing cursor on intersections, check if the cursor is before a leading row
						if(j== startInd-12 && i == 0 && cursorType == 0){
							//if ptr is at intended cursor position, draw the cursor
							
							if(*ptr == cursor){ 
								SetConsoleTextAttribute(hConsole, 12);
								cout << "0";
								SetConsoleTextAttribute(hConsole, 15);
								*ptr = *ptr + 1;
								continue;
							}
							else{
								drawIntersection(intersectionMap[*intInd]);
							}
							*ptr = *ptr + 1;
							*intInd = *intInd + 1;
							continue;
						}
						else if(j== startInd-12 && i == 0){
							drawIntersection(intersectionMap[*intInd]);
							*intInd = *intInd + 1;
							continue;
						}
						//for drawing the leading edge
						if(j == startInd-11+(i*4)){
							
							//if drawing the cursor on an edge, replace an edge piece with the cursor if position is correct
							if(i== 1 && cursorType == 1){
								*ptr = *ptr + 1;
								if(*ptr - 1 == cursor){
									SetConsoleTextAttribute(hConsole, 12);
									cout << "0.";
									SetConsoleTextAttribute(hConsole, 15);
								}
								else{
									drawEmptyEdge(edgeInd,1);
								}
							}
							else if(i == 0 && cursorType == 1 && *ptr == cursor){
								SetConsoleTextAttribute(hConsole, 12);
								cout << "'.";
								SetConsoleTextAttribute(hConsole, 15);
								
							}
							else if(i == 2 && cursorType == 1 && !secondLineColoured){
								if(line2colptr+*ptr == cursor+((num+1)*2)){
									SetConsoleTextAttribute(hConsole, 12);
									cout << "'."; 
									SetConsoleTextAttribute(hConsole, 15);
									secondLineColoured = true;
								}
								else{
									drawEmptyEdge(edgeInd,1);
								}
								line2colptr--;
							}
							else{
								drawEmptyEdge(edgeInd,1);
							}
							line1colptr++;
							//decrement start and end to account for characters added by leading edge
							startInd -= 2;
							decendingInd -= 2;
							if(!capAdded) *edgeInd = *edgeInd + 1;
							capAdded = true;
							
						}
					}
					//drawing the acending edge of the triangle
					if(j == startInd){
						//if drawing the cursor on an edge, replace an edge piece with the cursor if position is correct
						if(i == 1 && cursorType == 1){
							if(*ptr == cursor){
								SetConsoleTextAttribute(hConsole, 12);
								cout << ".0";
								SetConsoleTextAttribute(hConsole, 15);
								*ptr = *ptr + 1;
								*edgeInd = *edgeInd + 1;
								startInd += 12; //increment start index to the acending edge of the next triangle
								continue;
							}
							*ptr = *ptr + 1;
						}
						if(i == 0 && cursorType == 1 && !firstLineColoured){
							if(line1colptr == cursor && line1colptr >= *ptr){
								SetConsoleTextAttribute(hConsole, 12);
								cout << ".'";
								SetConsoleTextAttribute(hConsole, 15);
								firstLineColoured = true;
							}
							else{
								drawEmptyEdge(edgeInd,0);
							}
							line1colptr++;
						}
						else if(i == 2 && cursorType == 1 && !secondLineColoured){
							if(line2colptr+*ptr == cursor+(num*2)){
								SetConsoleTextAttribute(hConsole, 12);
								cout << ".'";
								SetConsoleTextAttribute(hConsole, 15);
								secondLineColoured = true;
							}
							else{
								drawEmptyEdge(edgeInd,0);
							}
							line2colptr++;
						}
						else{
							drawEmptyEdge(edgeInd,0);
						}
						*edgeInd = *edgeInd + 1;
						startInd += 12; //increment start index to the acending edge of the next triangle
					}
					//drawing the decending edge of the triangle
					else if(j == decendingInd){
						//if drawing the cursor on an edge, replace an edge piece with the cursor if position is correct
						if(i == 1 && cursorType == 1){
							if(*ptr == cursor){
								SetConsoleTextAttribute(hConsole, 12);
								cout << "0.";
								SetConsoleTextAttribute(hConsole, 15);
								*ptr = *ptr + 1;
								*edgeInd = *edgeInd + 1;
								decendingInd = startInd + 2 + (4*i); //increment decendingInd index to the decending edge of the next triangle
								continue;
							}
							*ptr = *ptr + 1;
						}
						if(i == 0 && cursorType == 1 && !firstLineColoured){
							if(line1colptr == cursor && line1colptr >= *ptr){
								SetConsoleTextAttribute(hConsole, 12);
								cout << "'.";
								SetConsoleTextAttribute(hConsole, 15);
								firstLineColoured = true;
							}
							else{
								drawEmptyEdge(edgeInd,1);
							}
							line1colptr++;
						}
						else if(i == 2 && cursorType == 1 && !secondLineColoured){
							if(line2colptr+*ptr == cursor+(num*2)){
								SetConsoleTextAttribute(hConsole, 12);
								cout << "'."; 
								SetConsoleTextAttribute(hConsole, 15);
								secondLineColoured = true;
							}
							else{
								drawEmptyEdge(edgeInd,1);
							}
							line2colptr++;
						}
						else{
							drawEmptyEdge(edgeInd,1);
						}
						*edgeInd = *edgeInd + 1;
						decendingInd = startInd + 2 + (4*i); //increment decendingInd index to the decending edge of the next triangle
					}
					//if cursor is at intersections, if the intersection is before or after all triangles are drawn, draw the cursor
					else if(((j == startInd-1 && i == 2) || (j == startInd-11 && i == 0 && j > initialStart-11)) && cursorType == 0){
						if(*ptr == cursor){
							SetConsoleTextAttribute(hConsole, 12);
							cout << "0";
							SetConsoleTextAttribute(hConsole, 15);
						}
						else{
							drawIntersection(intersectionMap[*intInd]);
						}
						*ptr = *ptr + 1;
						*intInd = *intInd + 1;
					}
					else if(((j == startInd-1 && i == 2) || (j == startInd-11 && i == 0 && j > initialStart-11))){
						drawIntersection(intersectionMap[*intInd]);
						*intInd = *intInd + 1;
					}
					else cout << " ";
				}
				cout << endl;
				startInd = initialStart - 2*(i+1); // move the start index back for the next level of the triangle (widen base)
				
				if(i!=2){
					if(bottomRow){
						*edgeInd = *edgeInd - ((num+1)*2);
					}
					else{
						*edgeInd = *edgeInd - (num*2);
					}
				}
			}
		}
		//output tile data to screen from tiles at the start index to the end index (exclusive). printing starts at offset
		void drawTiles(int offset, int startInd, int endInd, int *ptr, int cursor, int cursorType, int *edgeInd){
			
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for adding colour
			bool colAdded = false;
			int colourPtr = *ptr;
			int num = endInd - startInd;
			//first line
			for(int i = 0; i < offset; i++){ //adding offset
				cout << " ";
			}
			for(int i = startInd; i < endInd; i++){ // drawing the tiles number token if it has one
				Tile *t = tiles.at(i);
				if(!colAdded && colourPtr == cursor && cursorType == 1){
					SetConsoleTextAttribute(hConsole, 12);
					cout << "|";
					SetConsoleTextAttribute(hConsole, 15);
				}
				else{
					
					drawEmptyEdge(edgeInd, 2);
				}
				colourPtr++;
				if(t->getNumberToken() >= 10){ //space 2 digit numbers out so keep symmetry
					cout<< "     " << t->getNumberToken()/10 << " " << t->getNumberToken()%10 << "     "; // 10-12 number token
				} 
				else{
					if(t->getNumberToken() != -1)
						cout << "      " << t->getNumberToken() << "      "; //2-9 number token
					else cout << "             "; //no number token
				}
				*edgeInd = *edgeInd + 1; 
			}
			if(!colAdded && colourPtr == cursor && cursorType == 1){
				SetConsoleTextAttribute(hConsole, 12);
				cout << "|";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else{
				drawEmptyEdge(edgeInd, 2);
			}
			*edgeInd = *edgeInd + 1;
			cout << endl;
			*edgeInd = *edgeInd - (num + 1);
			//second line
			for(int i = 0; i < offset; i++){ //adding offset
				cout << " ";
			}
			for(int i = startInd; i < endInd; i++){
				Tile *t = tiles.at(i);
				//draw cursor on the edge if selecting edges, when ptr is at right cursor position
				if(cursorType == 1){
					if(*ptr == cursor){
						SetConsoleTextAttribute(hConsole, 12);
						cout << "0";
						SetConsoleTextAttribute(hConsole, 15);
					}
					else{
						drawEmptyEdge(edgeInd, 2);	
					}
					*ptr = *ptr + 1;
				}
				else{
					drawEmptyEdge(edgeInd, 2);	
				}
				//add terrain text to middle of tile 
				switch(t->getTerrainType()){
					
					case 0:
						cout << "   DESERT    ";
						break;
					case 1:
						cout << "    FIELD    ";
						break;
					case 2:
						cout << "   FORESTS   ";
						break;
					case 3:
						cout << "   PASTURE   ";
						break;
					case 4:
						cout << "  MOUNTAINS  ";
						break;
					case 5:
						cout << "    HILLS    ";
						break;
					default:
						cout << "    ERROR    "; //should never print
						break;
				}
				*edgeInd = *edgeInd + 1;	
			}
			//draw cursor on the edge if selecting edges, when ptr is at right cursor position
			if(cursorType == 1){
				if(*ptr == cursor){
					SetConsoleTextAttribute(hConsole, 12);
					cout << "0";
					SetConsoleTextAttribute(hConsole, 15);
				}
				else{
					drawEmptyEdge(edgeInd, 2);	
				}
				*ptr = *ptr + 1;
			}
			else{
				drawEmptyEdge(edgeInd, 2);	
			}
			*edgeInd = *edgeInd + 1;
			cout << endl;
			*edgeInd = *edgeInd - (num + 1);
			//last line
			for(int i = 0; i < offset; i++){ // add offset
				cout << " ";
			}
			for(int i = startInd; i < endInd; i++){ //empty last line 
				if(!colAdded && colourPtr-num == cursor && cursorType == 1){
					SetConsoleTextAttribute(hConsole, 12);
					cout << "|";
					SetConsoleTextAttribute(hConsole, 15);
				}
				else{
					drawEmptyEdge(edgeInd, 2);
				}
				colourPtr++;
				cout << "             ";
				*edgeInd = *edgeInd + 1;
			}
			if(!colAdded && colourPtr-num == cursor && cursorType == 1){
				SetConsoleTextAttribute(hConsole, 12);
				cout << "|";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else{
				drawEmptyEdge(edgeInd, 2);
			}
			*edgeInd = *edgeInd + 1;
			cout << endl;
		}
		
		std::tr1::shared_ptr<Intersection> getEdgeOwner(int ptr){
			for(int i = 0; i < tiles.size(); i++){
				for(int j =0; j < 6; j++){
					if(tiles.at(i)->getEdge(j)->getID() == ptr){
						return tiles.at(i)->getEdge(j);
					}
				}
			}
		}
		
		void drawEmptyEdge(int *ptr, int dir){ //0 asending // 1 decending // 2 straight
		
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for colour printing
			int colour = getEdgeOwner(*ptr)->getOwnerID();
			//cout << "ptr = " << *ptr << "colour is " << colour << endl;
			if(colour != -1){
				SetConsoleTextAttribute(hConsole, colour);
				if(dir == 0) cout << ".'";
				else if(dir == 1)cout << "'.";
				else cout << "|";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else{
				if(dir == 0) cout << ".'";
				else if(dir == 1)cout << "'.";
				else cout << "|";
			}
		}
		
		std::tr1::shared_ptr<Intersection> getIntersectionOwner(int ptr){
			for(int i = 0; i < tiles.size(); i++){
				for(int j =0; j < 6; j++){
					if(tiles.at(i)->getIntersection(j)->getID() == ptr){
						return tiles.at(i)->getIntersection(j);
					}
				}
			}
		}
		
		void drawIntersection(int ptr){
			
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for colour printing
			std::tr1::shared_ptr<Intersection> inter = getIntersectionOwner(ptr);
			if(inter->getOwnerID() != -1){
				SetConsoleTextAttribute(hConsole, inter->getOwnerID());
				if(inter->getTokenType() == Intersection::TOWN){
					cout << "T";
				}
				else if(inter->getTokenType() == Intersection::CITY){
					cout << "C";
				}
				else{
					cout << "O";
				}
				SetConsoleTextAttribute(hConsole, 15);
			}
			else{
				cout << " ";
			}
		}
		
		//moves the cursor across intersections on the board
		void moveIntersectionCursor(int key, int *cursorIndex, int *row){
			switch(key){
				case KEY_LEFT: //left
					//check if cursor is at an edge
					if(*cursorIndex != 0 && *cursorIndex != 7 && *cursorIndex != 16 && *cursorIndex != 27 && *cursorIndex != 38 && *cursorIndex != 47){
						*cursorIndex = *cursorIndex - 1;
					}
					break;
				case KEY_RIGHT: //right
					//check if cursor is at an edge
					if(*cursorIndex != 6 && *cursorIndex != 15 && *cursorIndex != 26 && *cursorIndex != 37 && *cursorIndex != 46 && *cursorIndex != 53){
						*cursorIndex = *cursorIndex + 1;
					}
					break;
				case KEY_UP: //up
					//check if cursor is at an edge
					if(*row != 1 && *cursorIndex != 7 && *cursorIndex != 16 && *cursorIndex != 15 && *cursorIndex != 26){
						*cursorIndex = *cursorIndex - 8; //move at least 8 intersection points
						if(*row == 3 || *row == 4) *cursorIndex= *cursorIndex - (*row-1); // move slightly more on center rows due to more tiles 
						else if(*row == 5) *cursorIndex = *cursorIndex - 2; // move more on row 5 as row 4 has more tiles 
						*row = *row - 1;
					}
					break;
				case KEY_DOWN: //down
					//check if cursor is at an edge
					if(*row != 6 && *cursorIndex != 27 && *cursorIndex != 37 && *cursorIndex != 38 && *cursorIndex != 46){
						*cursorIndex = *cursorIndex + 8; //move at least 8 intersection points
						if(*row == 2 || *row == 4) *cursorIndex = *cursorIndex + 2; // move slightly more on center rows due to more tiles 
						else if(*row == 3) *cursorIndex = *cursorIndex + 3; // move more on row 5 as row 4 has more tiles 
						*row = *row + 1;
					}
					break;
				default:
					break;
			}
		}
		
		void moveEdgeCursor(int key, int *cursorIndex, int *row){
			switch(key){
				case KEY_LEFT: //left
					//check if cursor is at an edge
					if(*cursorIndex != 0 && *cursorIndex != 6 && *cursorIndex != 10 && *cursorIndex != 18 
						&& *cursorIndex != 23 && *cursorIndex != 33 && *cursorIndex != 39 && *cursorIndex != 49 
						&& *cursorIndex != 54 && *cursorIndex != 62 && *cursorIndex != 66){
							
						*cursorIndex = *cursorIndex - 1;
					}
					break;
				case KEY_RIGHT: //right
					//check if cursor is at an edge
					if(*cursorIndex != 5 && *cursorIndex != 9 && *cursorIndex != 17 && *cursorIndex != 22 
						&& *cursorIndex != 32 && *cursorIndex != 38 && *cursorIndex != 48 && *cursorIndex != 53 
						&& *cursorIndex != 61 && *cursorIndex != 65 && *cursorIndex != 71){
							
						*cursorIndex = *cursorIndex + 1;
					}
					break;
				case KEY_UP: //up
					//check if cursor is at an edge
					if(*row != 1){
						//move very specific amounts each row due to non-straight movement path and changing tile counts 
						//amount cursor is moved by are arbitrary values based on board size
						if(*row == 2){
							*cursorIndex = (*cursorIndex * 2)-12;
							if(*cursorIndex == 6) *cursorIndex = *cursorIndex - 1;
						} 
						else if(*row == 3) *cursorIndex = (*cursorIndex + 2)/2;
						else if(*row == 4){
							*cursorIndex = (*cursorIndex * 2)-26;
							if(*cursorIndex == 18) *cursorIndex = *cursorIndex - 1;
						} 
						else if(*row == 5) *cursorIndex = (*cursorIndex + 13)/2;
						else if(*row == 6){
							*cursorIndex = (*cursorIndex * 2)-43;
							if(*cursorIndex == 33) *cursorIndex = *cursorIndex - 1;
						} 
						else if(*row == 7) *cursorIndex = (*cursorIndex + 28)/2;
						else if(*row == 8){
							*cursorIndex = (*cursorIndex * 2)-58;
						} 
						else if(*row == 9) *cursorIndex = (*cursorIndex + 45)/2;
						else if(*row == 10){
							*cursorIndex = (*cursorIndex * 2)-69;
						} 
						else if(*row == 11) *cursorIndex = (*cursorIndex + 59)/2;
						*row = *row - 1;
					}
					
					break;
				case KEY_DOWN: //down
					//check if cursor is at an edge
					if(*row != 11){
						//move very specific amounts each row due to non-straight movement path and changing tile counts
						//amount cursor is moved by are arbitrary values based on board size
						if(*row == 1) *cursorIndex = (*cursorIndex + 6) - (*cursorIndex/2);
						else if(*row == 2){
							*cursorIndex = (*cursorIndex * 2)-2;
						} 
						else if(*row == 3) *cursorIndex = (*cursorIndex + 13) - (*cursorIndex/2);
						else if(*row == 4){
							*cursorIndex = (*cursorIndex * 2)-13;
						} 
						else if(*row == 5){
							if(*cursorIndex%2 == 1){
								*cursorIndex = (*cursorIndex + 22) - (*cursorIndex/2) -1;
							}else{
								*cursorIndex = (*cursorIndex + 22) - (*cursorIndex/2);
							}
						} 
						else if(*row == 6){
							*cursorIndex = (*cursorIndex * 2)-28;
							if(*cursorIndex == 38) *cursorIndex = *cursorIndex + 1;
						} 
						else if(*row == 7) *cursorIndex = (*cursorIndex + 29) - (*cursorIndex/2);
						else if(*row == 8){
							*cursorIndex = (*cursorIndex * 2)-45;
							if(*cursorIndex == 53) *cursorIndex = *cursorIndex + 1;
						} 
						else if(*row == 9){
							if(*cursorIndex%2 == 1){
								*cursorIndex = (*cursorIndex + 35) - (*cursorIndex/2)-1;
							}
							else{
								*cursorIndex = (*cursorIndex + 35) - (*cursorIndex/2);
							}
						} 
						else if(*row == 10){
							*cursorIndex = (*cursorIndex * 2)-59;
							if(*cursorIndex == 65) *cursorIndex = *cursorIndex + 1;
						} 
						*row = *row + 1;
					}
					
					break;
				default:
					break;
			}
		}
		
};
