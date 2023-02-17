#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "QuadTree.h"
#include <list>

using namespace std;




int main()
{
	Quad* quadTree;
	
	fstream city;
	city.open("cities.txt");
	string line;
	int bound_x=0,bound_y=0;
	
	if(city.is_open())
	{
		city>>bound_x>>bound_y;	
	}
	
	quadTree= new Quad(Point(bound_x,bound_y), Point (0,0));

	while(city!=NULL)
	{
		string name;
		int city_x, city_y;
		city>>name>>city_x>>city_y;
		if(name!="")
		{
			Node* N;
			N = new Node(name,Point(city_x,city_y));
			quadTree->insert(N);
		}
		//quadTree->insert();
	
	}

	city.close();
	quadTree->pretty_print(quadTree);

	// the queries.txt file is read. In this file, every line corresponds to a query in the form x y r 
	int qx,qy,qr;
	fstream query;
	Query *Q;


	

	query.open("queries0.txt");
	if (query.is_open())
	{
		while(getline(query,line))
		{

			list<string> visited;
			list<string> found;


			string dump;
			istringstream iss(line);
			iss>>qx>>dump>>qy>>dump>>qr;

			Q = new Query(Point(qx,qy),qr);

			quadTree->search(Q,quadTree,found,visited);


			cout<<endl;
			if(found.empty())
			{
				cout<<"<None>"<<endl;
			}
			else
			{
				for(string i : found)
				{
					cout<<i<<", ";
				}
				cout<<endl;
			}

	
			for(string i : visited)
			{
				cout<<i<<", ";
			}
			cout<<endl;
			
		}
	}

	
	
	





	int i= 0;


	return 0;
}