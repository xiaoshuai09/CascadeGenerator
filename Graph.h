/*

Definition of the Graph Class.  

Author : Nan Du (dunan@gatech.edu)

*/

#ifndef GRAPH_H
#define GRAPH_H
#include "Common.h"

using namespace std;

struct Node {

	set<unsigned> children;
	set<unsigned> parents;
	
};

struct Parameter { 
	float scale;
	float shape;
};

class Graph{
	
public:

	unsigned N;
	
	Graph(string g_filename, unsigned numNodes);
	~Graph(){};

	vector<Node> nodes;
	map<unsigned, map<unsigned, float> > edge_weight;
	map<unsigned, map<unsigned, Parameter> > edge_parameter;

	void PrintWblNetwork();

	void PrintProbabilityNetwork();

	void LoadProbabilityFormatNetwork(string splitter, bool reverse);

	void LoadWeibullFormatNetwork(string splitter, bool reverse);

	void SampleEdgeWeightWbl();

	pair<unsigned, unsigned> MaximumOutDegree();

	vector<string> SeperateLineWordsVector(string lineStr,string splitter);

private:

	string filename;

	SimpleRNG RNG;
	
	

};

#endif