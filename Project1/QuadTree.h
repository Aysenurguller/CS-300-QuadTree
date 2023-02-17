#ifndef QUADTREE_H
#define QUADTREE_H
#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Point
{
	int x;
	int y;

	Point(int _x, int _y) : x(_x), y(_y){}
	Point(): x(0),y(0){}
};

struct Node
{
	string city;
	Point location;


	Node(string _city, Point _loc): city(_city), location(_loc){}
	Node(){city="";}

};

struct Query
{
	Point coordinate;
	int radius;

	Query(Point _coor,int _radius): coordinate(_coor), radius(_radius){}
	

};


class Quad
{
	Point boundary;
	Point origin;

	Node *R;

	
	Quad* SE;
	Quad* SW;
	Quad* NE;
	Quad* NW;
	

public:
	Quad()
	{
		boundary= Point(0,0);
		origin= Point(0,0);
		R=NULL;
		NW=NULL;
		NE=NULL;
		SW=NULL;
		SE=NULL;

	}

	Quad(Point _bound, Point _org)
	{
		boundary= _bound;
		origin= _org;
		R=NULL;
		NW=NULL;
		NE=NULL;
		SW=NULL;
		SE=NULL;
	}





	//COMPARE
	//IN$ERT
	void insert(Node *);
	void pretty_print(Quad *);
	bool inBound(Point P);
	void search(Query* query, Quad* Q, list<string> & l1, list<string> & l2);
	
	//Quad();
	//~Quad();

private:

};


#endif