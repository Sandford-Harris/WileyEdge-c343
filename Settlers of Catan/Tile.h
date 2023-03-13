#include <iostream>
#include <vector>
#include <tr1/memory>
#include "Intersection.h"

using namespace std;

enum TerrainType{
	
	DESERT = 0,
	FIELD = 1,
	FOREST = 2,
	PASTURE = 3,
	MOUNTAINS = 4,
	HILLS = 5
	
};

class Tile{
	
	private:
		TerrainType type;
		int numberToken;
		vector<std::tr1::shared_ptr<Intersection> > intersections; // list of 6 points of the tile (0 = topleft, 1 = top, 2 = top right, 3 = botleft, 4 = bot, 5 = bot right)
		vector<std::tr1::shared_ptr<Intersection> > edges; // list of 6 edges of the tile (0 = top left, 1 = top right, 2 = left, 3 = right, 4 = botleft, 5 = bot right)
		vector<Tile*> adjacentTiles; // list of 6 adjacent tiles (0 = top left,  going clockwise)
	
	public:
		Tile(TerrainType t, int number){
			
			type = t;
			numberToken = number;
		}
		void setNumberToken(int number){
			numberToken = number;
		}
		int getNumberToken(){
			return numberToken;
		}
		void setTerrainType(TerrainType t){
			type = t;
		}
		TerrainType getTerrainType(){
			return type;
		}
		void setEdgeOwnerID(int edgeInd, int id){
			edges.at(edgeInd)->setOwnerID(id);
		}
		void setIntersectionOwnerID(int intInd, int id){
			intersections.at(intInd)->setOwnerID(id);
		}
		
		//0 = top, 1 = top right, 2 = bottom right, 3 = bottom, 4 = bottom left, 5 = top left
		std::tr1::shared_ptr<Intersection>& getIntersection(int index){
			return (intersections.at(index));
		}
		std::tr1::shared_ptr<Intersection>& getEdge(int index){
			//cout << "\nedges at index in tile = " << edges.at(index) << endl;
			return (edges.at(index));
		}
		void addIntersections(std::tr1::shared_ptr<Intersection> *top, std::tr1::shared_ptr<Intersection> *topRight, std::tr1::shared_ptr<Intersection> *bottomRight, std::tr1::shared_ptr<Intersection> *bottom, std::tr1::shared_ptr<Intersection> *bottomLeft, std::tr1::shared_ptr<Intersection> *topLeft){
			
			intersections.push_back(*top);
			intersections.push_back(*topRight);
			intersections.push_back(*bottomRight);
			intersections.push_back(*bottom);
			intersections.push_back(*bottomLeft);
			intersections.push_back(*topLeft);
		}
		//0 = top left, 1 = top right, 2 = right, 3 = bottom right, 4 = bottom left, 5 = left
		void addEdges(std::tr1::shared_ptr<Intersection> *topLeft, std::tr1::shared_ptr<Intersection> *topRight, std::tr1::shared_ptr<Intersection> *right, std::tr1::shared_ptr<Intersection> *bottomRight, std::tr1::shared_ptr<Intersection> *bottomLeft, std::tr1::shared_ptr<Intersection> *left){
			
			//cout << *topLeft << endl;
			edges.push_back(*topLeft);
			edges.push_back(*topRight);
			edges.push_back(*right);
			edges.push_back(*bottomRight);
			edges.push_back(*bottomLeft);
			edges.push_back(*left);
		}
};
