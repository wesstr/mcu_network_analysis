#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

class Vertex;

class Edge
{
public:
	Edge()
	{
		origin = nullptr;
		destination = nullptr;
		this->action = "";
		this->distance = -1;
	}

	Edge(Vertex *org, Vertex *dest, string action, int distance)
	{
		origin = org;
		destination = dest;
		this->action = action;
		this->distance = distance;

	}

	Vertex* getOrigin() { return origin; }
	Vertex* getDestination() { return destination; }
	int getDistance() { return distance; }
	string getAction() { return action; }
	void addDistance()
	{ 
		++distance;
	}


private:
	Vertex* origin;
	Vertex* destination;
	string action;
	int distance;
};


class Vertex
{
public:
	Vertex()
	{
		name = "";
	}

	Vertex(string name, int id)
	{
		this->name = name;
		this->id = id;
	}

	void addEdge(Vertex *org, Vertex *dest, string action,int distance)
	{
		Vertex temp = *org;
		//temp.get
		if (edges.size() == 0)
		{
			Edge newEdge(org, dest, action, distance);
			edges.push_back(newEdge);
		}
		else
		{
			string currnet_edge_name = dest->getName();
			int count = 0;

			for (auto &edge : edges)
			{
				Vertex destination = *edge.getDestination();
				if (destination.getName() == currnet_edge_name && action == edge.getAction() && edges.size() > 1)
				{
					edge.addDistance();
					return;
				}

				++count;
			}
			Edge newEdge(org, dest, action, distance);
			edges.push_back(newEdge);
		}
	}

	Edge maxEdge(string action)
	{
		if (edges.size() == 0)
		{
			return Edge();
		}

		Edge max_person = edges[0];
		int max_distance = 0;
		for (auto &edge : edges)
		{
			Vertex current_edge = *edge.getDestination();
			string temp = edge.getAction();
			int  current_distance = edge.getDistance();
			if ((current_distance > max_distance) && (temp == action))
			{
				max_person = edge;
				max_distance = edge.getDistance();
			}
		}
		return max_person;
	}

	Edge minEdge()
	{
		if (edges.size() == 0)
		{
			return Edge();
		}

		Edge max_person = edges[0];
		int max_distance = 0;
		for (auto &edge : edges)
		{
			Vertex current_edge = *edge.getDestination();
			string temp = edge.getAction();
			int  current_distance = edge.getDistance();
			if (current_distance < max_distance && (temp == "teamedUp"))
			{
				max_person = edge;
				max_distance = edge.getDistance();
			}
		}
		return max_person;
	}

	string getName() { return name; }
	vector<Edge> getEdges() { return edges; }
	int getId() { return id; }

private:
	string name;
	int id;
	vector<Edge> edges;
};


class Graph
{
public:
	Graph()
	{
		graph[-1] = Vertex();
	}


	void setGraph(string name, int id)
	{
		Vertex names = Vertex(name , id);
		graph[id] = names;
	}

	void setVertics(int id1, int id2, string action, int distance)
	{
		graph[id1].addEdge(&graph[id1], &graph[id2], action, distance);

	}

	unordered_map<int, Vertex> getGraph() { return graph; }

	void mostTeamups()
	{
		graph.erase(-1);
		Edge max_person = graph[0].maxEdge("teamedUp");
		int max_distance = 0;
		while (max_distance != graph.size())
		{
			Edge current_person = graph[max_distance].maxEdge("teamedUp");
			if (current_person.getDistance() > max_person.getDistance())
			{
				max_person = current_person;
			}
			max_distance++;
		}
		Vertex temp = *max_person.getDestination();
		Vertex temp2 = *max_person.getOrigin();
		cout << "The max team up's are " << temp2.getName() << " and " << temp.getName() << " with " << max_person.getDistance() << " team up's." <<endl;
	}

	void mostFought()
	{
		graph.erase(-1);
		Edge max_person = graph[0].maxEdge("fought");
		int max_distance = 0;
		while (max_distance != graph.size())
		{
			Edge current_person = graph[max_distance].maxEdge("fought");
			if (current_person.getDistance() > max_person.getDistance())
			{
				max_person = current_person;
			}
			max_distance++;
		}
		Vertex temp = *max_person.getDestination();
		Vertex temp2 = *max_person.getOrigin();
		cout << "The max fights are " << temp2.getName() << " and " << temp.getName() << " with " << max_person.getDistance() << " figths." << endl;
	}

	void minspantree()
	{
		vector<Vertex> parent; //used to store the smt
		vector<Edge> key;      //used to store the smts edges

		// Initialize all keys as INFINITE

		//Gets the starting vertex
		parent.push_back(graph[0]);

		//Gets the first minium edge for the starting node
		key.push_back(parent[0].minEdge());

		//Gets the smallest edges destinaion
		parent.push_back(*key[0].getDestination());

		for (int i = 1 ; i != graph.size(); ++i)
		{
			int count = 0;

			//Gets the smallest edges for the current stored vertics
			for (auto a_parent : parent)
			{
				for (int j = 0; j != key.size(); j++)
				{
					//checks to see if the edge has not already been visited
					if ((!(a_parent.minEdge().getDestination() == key[j].getDestination())
						&& !(a_parent.minEdge().getOrigin() == key[j].getOrigin()))
						|| a_parent.minEdge().getDistance() < key[j].getDistance())
					{
							key.push_back(a_parent.minEdge());
							count++;
					}
					else if ((a_parent.minEdge().getDistance() == key[j].getDistance())
							&& (!(a_parent.minEdge().getDestination() == key[j].getDestination())
							&& !(a_parent.minEdge().getOrigin() == key[j].getOrigin())))
					{
						key.push_back(a_parent.minEdge());
						count++;
					}
				}
			}

			parent.push_back(graph[i]);
		}

		for (auto a_key : key)
		{
			Vertex temp1 = *a_key.getDestination();
			Vertex temp2 = *a_key.getOrigin();
			cout << temp2.getName() << " team up with " << temp1.getName() << " " << a_key.getDistance() << " times." << endl;
		}
	//	Edge min = graph[0].minEdge();
	//	cout << min.getDistance() << endl;
	}

private:
	unordered_map<int, Vertex> graph;
};