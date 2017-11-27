/*

Definition of the Naive Simulation Class.  

Author : Nan Du (dunan@gatech.edu)

*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Common.h"
#include "Graph.h"

using namespace std;

struct Node2Time{
	unsigned nodeID;
	double time;
	
	bool operator < (const Node2Time& n2t) const{
		if (time < n2t.time) {
			return true;
		}else {
			return false;
		}
	}
};

class Simulation{

private:

	Graph* G;

	SimpleRNG RNG;


private:

	void GenerateCascade(vector<Node2Time>& cascade, vector<Node2Time>& visitedNodes,  set<unsigned>& initialSet, double TimeHorizon, map<unsigned, unsigned>& infectedBy);

public:
	Simulation(Graph *G);
	Simulation(const Graph &G);
	~Simulation(){};

	double RandomSimulation(double T, set<unsigned>& initialSet, unsigned C);

	void OutputCascadeBySingleNode(const double &T, const unsigned &C, const string &filename, const string &visitedFile);

	void LoadCascade(const string &filename, vector<vector<set<unsigned> > > &node_to_cascades);

};

#endif