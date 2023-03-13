#include <iostream>
#include <vector>

using namespace std;

class Player{
	
	
	private:
		int id; // doubles as player colour
		int victoryPoints;
		vector<int> cardsInHand; //holds resource counts 0 - WHEAT, 1 - WOOD, 2 - SHEEP, 3 - ORE, 4 - CLAY
		
	public:
		Player(int i){
			id = i;
			victoryPoints = 2; // each player has 2 settlements after drafting
			for(int i = 0; i < 5; i++)
				cardsInHand.push_back(2);// start with 2 of everything for simplicity
		}
		enum Resource{
			WHEAT = 0,
			WOOD = 1,
			SHEEP = 2,
			ORE = 3,
			CLAY = 4
		};
		int getID(){
			return id;
		}
		int getVPs(){
			return victoryPoints;
		}
		void addVP(){
			victoryPoints += 1;
		}
		int getResourceCount(Resource resource){
			return cardsInHand.at((int)resource);
		}
		void addResourceCount(Resource resource, int amount){
			cardsInHand.at((int)resource) += amount;
		}
	
};
