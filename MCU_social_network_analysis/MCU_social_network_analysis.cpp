// MCU_social_network_analysis.cpp : Defines the entry point for the console application.
//


#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//file reading and error checking are
//not mine.
Graph populateGraph(Graph graph)
{
	string filename = "names.txt";
	ifstream namesFile(filename);
	if (!namesFile.good())
	{
		cerr << "Could't open file." << endl;
		namesFile.close();
		system("pause");
	}
	while (!namesFile.eof())
	{
		int id;
		string name;
		namesFile >> id >> name;

		if (!namesFile.good() && !namesFile.eof())
		{
			cerr << "Error Reading" << endl;
			namesFile.close();
			system("pause");
		}
		graph.setGraph(name, id);
	}
	namesFile.close();
	filename = "teams.txt";
	ifstream teamsFile(filename);
	if (!teamsFile.good())
	{
		cerr << "Could't open file." << endl;
		teamsFile.close();
		system("pause");
	}
	while (!teamsFile.eof())
	{
		int id, id2;
		string action;
		teamsFile >> id >> action >> id2;
		if (!teamsFile.good() && !teamsFile.eof())
		{
			cerr << "Error Reading" << endl;
			teamsFile.close();
			system("pause");
		}
		graph.setVertics(id, id2, action, 1);
	}
	namesFile.close();
	return graph;
}


int main()
{

	Graph graph;
	graph = populateGraph(graph);

	cout << "The most team up's and fights are..." << endl;
	graph.mostTeamups();
	graph.mostFought();
	graph.minspantree();

	system("pause");

	return 0;
}