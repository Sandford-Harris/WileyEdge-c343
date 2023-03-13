#include <iostream>

using namespace std;


class Intersection{
	
	public:
		enum TokenType{
		
			NONE = 0,
			TOWN = 1,
			CITY = 2,
			ROAD = 3
		};
	
		enum IntersectionType{
			
			EDGE = 0,
			CORNER = 1
		};
	
	private:
		IntersectionType type;
		TokenType token;
		int ownerID;
		int id;
		
	public:
		Intersection(IntersectionType intType, int i){
			type = intType;
			token = NONE;
			ownerID = -1;
			id = i;
		}
		void setTokenType(TokenType tokenType){
			
			token = tokenType;
		}
		TokenType getTokenType(){
			return token;
		}
		//returns true if the owner id is set (only set if tile is unowned)
		bool setOwnerID(int id){
			if(ownerID == -1){
				ownerID = id;
				return true;
			}
			return false;
		}
		int getOwnerID(){
			return ownerID;
		}
		int getID(){
			return id;
		}
};
