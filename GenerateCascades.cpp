#include <fstream>
#include <string>
#include "Common.h"
#include "Graph.h"
#include "Simulation.h"
#include "Snap.h"

void GenerateCascades(const double &T, const unsigned &N, const unsigned &C, const string &graph_filename, const string &cascade_filename, const string &visitedFile)
{
	cout << graph_filename << endl;

	Graph G(graph_filename, N);

	G.LoadWeibullFormatNetwork(",", false);

	Simulation cascade_generator(&G);

	cascade_generator.OutputCascadeBySingleNode(T, C, cascade_filename, visitedFile);
}

int main(int argc, char **argv)
{
	Env = TEnv(argc, argv, TNotify::StdNotify);
 	Env.PrepArgs(TStr::Fmt("\nGenerate synthetic kronecker networks. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
 	TExeTm ExeTm;
 
	const int N = Env.GetIfArgPrefixInt("-n:", 10240, "Number of nodes (default:1024)\n");

	const int C = Env.GetIfArgPrefixInt("-c:", 12, "Number of cascades per source (default:128)\n");

	const double T = Env.GetIfArgPrefixFlt("-t:", 20, "Observation window (default:10.0)\n");

	const TStr network_filename = Env.GetIfArgPrefixStr("-fg:", TStr("weibull_kronecker_synthetic"), "Name of the network (default:weibull_kronecker_synthetic)\n");

	const TStr cascade_filename = Env.GetIfArgPrefixStr("-fc:", TStr("weibull_kronecker_synthetic_cascade"), "Name of the network (default:weibull_kronecker_synthetic_cascade)\n");
	
	const TStr visited_filename = Env.GetIfArgPrefixStr("-fc:", TStr("weibull_kronecker_synthetic_vistedNodes"), "Name of the network (default:weibull_kronecker_synthetic_vistedNodes)\n");

	GenerateCascades(T, N, C, network_filename.CStr(), cascade_filename.CStr(), visited_filename.CStr());

	return 0;

}
