/*

Implementation of the Graph Class.  

Author : Nan Du (dunan@gatech.edu)

*/

#include "Graph.h"

Graph::Graph(string g_filename, unsigned numNodes)
{
	filename = g_filename;
	N = numNodes;
	RNG.SetState(0, 0);
}


vector<string> Graph::SeperateLineWordsVector(string lineStr,string splitter)
{
	string::size_type pos = 0;
	string::size_type prePos = 0;
	string filtChars(splitter); 
	string lastWord = "";
	string tempWord;
	
	int count = 0;
	vector<string> temp;
	
	while((pos = lineStr.find_first_of(filtChars,pos)) != string::npos)
	{
		if(lineStr.substr(pos, filtChars.size()) == filtChars)
		{
			count++;
			tempWord = "";
			tempWord = lineStr.substr(prePos,pos - prePos);
			if (tempWord != "")
			{
				temp.push_back(tempWord);
			}
			pos += filtChars.size();
			prePos = pos;
			
		}else
		{
			++ pos;
		}
	}
	if(prePos < lineStr.length())
	{
		temp.push_back(lineStr.substr(prePos,lineStr.length() - prePos));                
	}                
	
	return temp;
}

void Graph::PrintWblNetwork()
{
	for (unsigned i = 0; i < nodes.size(); ++ i) {
		for (set<unsigned>::iterator u = nodes[i].children.begin(); u != nodes[i].children.end(); ++ u) {
			cout << i << "\t" << *u << "\t" << edge_parameter[i][*u].scale << "\t" <<edge_parameter[i][*u].shape<< endl;
		}
	}
}

void Graph::PrintProbabilityNetwork()
{
	for (unsigned i = 0; i < nodes.size(); ++ i) {
		for (set<unsigned>::iterator u = nodes[i].children.begin(); u != nodes[i].children.end(); ++ u) {
			cout << i << "\t" << *u << "\t" << edge_weight[i][*u] << endl;
		}
	}	
}

void Graph::LoadProbabilityFormatNetwork(string splitter, bool reverse)
{
	nodes.reserve(N);

	stringstream ss;
	for (unsigned i = 0; i < N; ++ i) {
		
		Node node;
		nodes.push_back(node);
	
	}
	
	ifstream fin(filename.c_str(),ios::in);
	string str = "",str1 = "",str2 = "", str3 = "";
	unsigned readline = 1, count = 0;

	while(getline(fin,str))
	{
		
		if(readline >= N + 2)
		{
			vector<string> line = SeperateLineWordsVector(str,splitter);
			str1 = line[0];
			str2 = line[1];
			str3 = line[3];
			
			if(str1 == str2)
			{
				cout <<str<<endl;
			}else {
				
				int idx1, idx2;
				
				if(!reverse)
				{
					idx1 = atoi(str1.c_str());
					idx2 = atoi(str2.c_str());
				}else {
					idx2 = atoi(str1.c_str());
					idx1 = atoi(str2.c_str());
				}
				
				float weight = atof(str3.c_str());
				
				nodes[idx1].children.insert(idx2);
				nodes[idx2].parents.insert(idx1);
				
				if(edge_weight.find(idx1) == edge_weight.end())
				{
					map<unsigned, float> temp;
					temp.insert(make_pair(idx2, weight));
					
					edge_weight.insert(make_pair(idx1, temp));
					
				}else {
					edge_weight[idx1].insert(make_pair(idx2, weight));
				}
				
			}
			
			++ count;
			
		}
		
		++ readline;
		
	}
	
	fin.close();
	
	
	cout<<count<<" edges"<<endl;	
}

void Graph::LoadWeibullFormatNetwork(string splitter, bool reverse)
{

	nodes.reserve(N);

	stringstream ss;
	for (unsigned i = 0; i < N; ++ i) {
		
		Node node;
		nodes.push_back(node);
	
	}
	
	ifstream fin(filename.c_str(),ios::in);
	string str = "",str1 = "",str2 = "", str3 = "", str4 = "";
	unsigned readline = 1, count = 0;
	while(getline(fin,str))
	{
		
		if(readline >= N + 2)
		{
			vector<string> line = SeperateLineWordsVector(str,splitter);
			str1 = line[0];
			str2 = line[1];
			str3 = line[2];
			str4 = line[3];
			
			if(str1 == str2)
			{
				cout <<str<<endl;
			}else {
				
				int idx1, idx2;
				
				if(!reverse)
				{
					idx1 = atoi(str1.c_str());
					idx2 = atoi(str2.c_str());
				}else {
					idx2 = atoi(str1.c_str());
					idx1 = atoi(str2.c_str());
				}
				
				Parameter param;
				param.shape = atof(str3.c_str());
				param.scale = atof(str4.c_str());
				
				nodes[idx1].children.insert(idx2);
				nodes[idx2].parents.insert(idx1);
				
				if(edge_parameter.find(idx1) == edge_parameter.end())
				{
					map<unsigned, Parameter> temp;
					temp.insert(make_pair(idx2, param));
					
					edge_parameter.insert(make_pair(idx1, temp));
					
				}else {
					edge_parameter[idx1].insert(make_pair(idx2, param));
				}
			
				
			}
			
			++ count;
			
		}
		
		++ readline;
		
	}
	
	fin.close();
}


void Graph::SampleEdgeWeightWbl()
{
	for (unsigned i = 0; i < nodes.size(); ++ i) 
	{
		for (set<unsigned>::iterator c = nodes[i].children.begin(); c != nodes[i].children.end(); ++ c) {
			
			const Parameter &param = edge_parameter[i][*c];

			edge_weight[i][*c] = RNG.GetWeibull(param.shape, param.scale);
			
		}

	}
}

pair<unsigned, unsigned> Graph::MaximumOutDegree()
{
	unsigned d = 0;
	unsigned mark = 0;
	
	for (unsigned i = 0; i < nodes.size(); ++ i) {
		unsigned tmp = nodes[i].children.size();
		if(d < tmp)
		{
			d = tmp;
			mark = i;
		}
		
	}
	return make_pair(mark, d);	
}

