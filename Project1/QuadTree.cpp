#include <iostream>
#include "QuadTree.h"
#include <list>
#include <string>
#include <cmath>

using namespace std;



void Quad::insert( Node* P)
{
	Node *temp;

	if (R==NULL)
	{
		R=P;
		return;
	}

	//Indicates West side of Tree
	if(P->location.x < R->location.x)
	{
		//Indicates SouthWest side of Tree
		if (P->location.y < R->location.y)
		{
			if(SW == NULL)
			{
				SW= new Quad (Point((origin.x+boundary.x)/2,(origin.y+boundary.y)/2), Point(origin.x, origin.y));
				SW->R=P;
			}
			else
			{
				SW->insert(P);
			}
			
		}

		//Indicates NorthWest side of Tree
		else if(P->location.y >= R->location.y) 
		{
			if(NW == NULL)
			{
				NW= new Quad(Point((origin.x+boundary.x)/2,boundary.y),Point(origin.x, (origin.y+boundary.y)/2));
				NW->R=P;
			}
			else
			{
				NW->insert(P);
			}
		}
	}



	//Indicates East side of Tree
	else if(P->location.x > R->location.x)
	{
		//(P->location.y < R->location.y)
		//Indicates SouthEast side of Tree
		if(P->location.y < R->location.y)
		{
			if(SE == NULL)
			{
				SE= new Quad(Point(boundary.x, (origin.y+boundary.y)/2),Point((boundary.x+origin.x)/2,origin.y));
				SE->R=P;
			}
			else
			{
				SE->insert(P);
			}
		}
		else if(P->location.y >= R->location.y)
		{
			if(NE == NULL)
			{
				NE= new Quad(Point(boundary.x, (origin.y+boundary.y)/2),Point((boundary.x+origin.x)/2,origin.y));
				NE->R=P;
			}
			else
			{
				NE->insert(P);
			}
		}


	}
	//Indicates NorthEast side of Tree
	else
	{
		if(P->location.y > R->location.y)
		{
			if(NE==NULL)
			{
				NE= new Quad(Point(boundary.x,boundary.y),Point((boundary.x+origin.x)/2,(boundary.y+origin.y)/2));
				NE->R=P;
			}
			else
			{
				NE->insert(P);
			}
		}
		else
		{
			if(SE==NULL)
			{
				SE= new Quad(Point(boundary.x,boundary.y),Point((boundary.x+origin.x)/2,(boundary.y+origin.y)/2));
				SE->R=P;
			}
			else
			{
				SE->insert(P);
			}

		}
		
	}
};	
	




void Quad:: pretty_print (Quad *q)
{
	
	if (q->R != NULL)
	{
		cout<<q->R->city<<endl;
	}
	if(q->SE!=NULL){

		pretty_print(q->SE);
	}
	if(q->SW!=NULL){

		pretty_print(q->SW);
	}
	if(q->NE!=NULL){

		pretty_print(q->NE);
	}
	if(q->NW!=NULL){
	
		pretty_print(q->NW);
	}


};

bool Quad:: inBound(Point p)
{
	return (p.x >= origin.x && p.x <= boundary.x &&
		p.y>= origin.y && p.y <=boundary.y);
}

void Quad::search (Query* p, Quad* q, list<string> & found ,list<string> & visited )
{
	if(q==NULL)
	{
		return;
	}

	visited.push_back(q->R->city);

	if(sqrt(pow(q->R->location.x-p->coordinate.x,2)+pow(q->R->location.y-p->coordinate.y,2))<=p->radius)
	{
		found.push_back(q->R->city);
		q->search(p,q->SE,found,visited);
		q->search(p,q->SW,found,visited);
		q->search(p,q->NE,found,visited);
		q->search(p,q->NW,found,visited);
	}


	else if (p->coordinate.x - p->radius >  q->R->location.x  && p->coordinate.y + p->radius  < q->R->location.y)
	{//1
		q->search(p,q->SE,found,visited);
	}
	else if (p->coordinate.x + p->radius <  q->R->location.x  && p->coordinate.y + p->radius  < q->R->location.y)
	{//3
		q->search(p,q->SW,found,visited);
	}
	else if (p->coordinate.x - p->radius >  q->R->location.x  && p->coordinate.y - p->radius  > q->R->location.y)
	{//6
		q->search(p,q->NE,found,visited);
	}
	else if (p->coordinate.x + p->radius <  q->R->location.x  && p->coordinate.y - p->radius  > q->R->location.y)
	{//8
		q->search(p,q->NW,found,visited);
	}
	else if (p->coordinate.x + p->radius >  q->R->location.x  && p->coordinate.x - p->radius <  q->R->location.x  && p->coordinate.y + p->radius  < q->R->location.y)
	{//2
		q->search(p,q->SE,found,visited);
		q->search(p,q->SW,found,visited);
	}
	else if (p->coordinate.x - p->radius >  q->R->location.x  && p->coordinate.y - p->radius <  q->R->location.y  && p->coordinate.y + p->radius  > q->R->location.y)
	{//4
		q->search(p,q->SE,found,visited);
		q->search(p,q->NE,found,visited);
	}
	else if (p->coordinate.x + p->radius > q->R->location.x  && p->coordinate.x - p->radius <  q->R->location.x  && p->coordinate.y - p->radius  > q->R->location.y)
	{//7
		q->search(p,q->NE,found,visited);
		q->search(p,q->NW,found,visited);
	}
	else if (p->coordinate.x + p->radius <  q->R->location.x  && p->coordinate.y - p->radius <  q->R->location.y  && p->coordinate.y + p->radius  > q->R->location.y)
	{//5
		q->search(p,q->SE,found,visited);
		q->search(p,q->SW,found,visited);
	}
	else if (p->coordinate.y < q->R->location.y && p->coordinate.x - p->radius <  q->R->location.x && p->coordinate.y + p->radius >  q->R->location.y  && p->coordinate.y - p->radius  > q->R->location.y)
	{//9
		q->search(p,q->SE,found,visited);
		q->search(p,q->SW,found,visited);
		q->search(p,q->NE,found,visited);
	}
	else if (p->coordinate.y > q->R->location.y && p->coordinate.x - p->radius <  q->R->location.x && p->coordinate.y + p->radius >  q->R->location.y  && p->coordinate.y - p->radius  > q->R->location.y)
	{//11
		q->search(p,q->SE,found,visited);
		q->search(p,q->NE,found,visited);
		q->search(p,q->NW,found,visited);
	}
	else if (p->coordinate.y < q->R->location.y && p->coordinate.x + p->radius >  q->R->location.x && p->coordinate.y + p->radius >  q->R->location.y  && p->coordinate.y - p->radius  < q->R->location.y)
	{//10
		q->search(p,q->SE,found,visited);
		q->search(p,q->SW,found,visited);
		q->search(p,q->NW,found,visited);
	}
	else if (p->coordinate.y > q->R->location.y && p->coordinate.x + p->radius >  q->R->location.x && p->coordinate.y + p->radius >  q->R->location.y  && p->coordinate.y - p->radius  < q->R->location.y)
	{//12
		q->search(p,q->NE,found,visited);
		q->search(p,q->SW,found,visited);
		q->search(p,q->NW,found,visited);
	}



}