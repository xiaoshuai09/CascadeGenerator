#include "stdafx.h"
#include "Snap.h"


void GenerateNetworkStructure(const int& NNodes, const int& NEdges, const TStr& NetworkParams, PIntFltNEDNet &network)
{
  network = TIntFltNEDNet::New();

  TKronMtx SeedMtx = TKronMtx::GetMtx(NetworkParams.CStr());

  PNGraph temp = TKronMtx::GenFastKronecker(SeedMtx, (int)TMath::Log2(NNodes), NEdges, true, 0);

  for(TNGraph::TNodeI NI = temp->BegNI(); NI < temp->EndNI(); NI++)
  {
    network->AddNode(NI.GetId());
  }

  for(TNGraph::TEdgeI EI = temp->BegEI(); EI < temp->EndEI(); EI++) 
  { 
    network->AddEdge(EI.GetSrcNId(),EI.GetDstNId(),1);  
  }
}

void SaveNetwork(const TStr& network_filename, const PIntFltNEDNet &network, const TStr &wbl_shape_range, const TStr &wbl_scale_range)
{

  TStrV shape, scale; 

  wbl_shape_range.SplitOnAllCh(';', shape);
  wbl_scale_range.SplitOnAllCh(';', scale);

  TFOut FOut(network_filename);

  // print the node information
  for (TIntFltNEDNet::TNodeI NI = network->BegNI(); NI < network->EndNI(); NI++) {
    FOut.PutStr(TStr::Fmt("%d,%d\r\n", NI.GetId(), NI.GetId())); 
  }

  FOut.PutStr("\r\n");

  // print the edges with Weibull parameters
  for (TIntFltNEDNet::TEdgeI EI = network->BegEI(); EI < network->EndEI(); EI++) {
    // get rid of the self loops 
    if (EI.GetSrcNId() != EI.GetDstNId())
      FOut.PutStr(TStr::Fmt("%d,%d,%f,%f\r\n", EI.GetSrcNId(), EI.GetDstNId(), shape[0].GetFlt() + TFlt::Rnd.GetUniDev() * (shape[1].GetFlt() - shape[0].GetFlt()), scale[0].GetFlt() + TFlt::Rnd.GetUniDev() * (scale[1].GetFlt() - scale[0].GetFlt())));
  }
}

int main(int argc, char* argv[]) {

  srand(time(NULL));

  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("\nGenerate synthetic kronecker networks. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm;
  Try

  //const TStr NetworkParams = Env.GetIfArgPrefixStr("-g:", TStr("0.9 0.5; 0.5 0.9"), "Parameters for the network (default:0.9 0.5; 0.5 0.9)\n");
  const TStr NetworkParams = Env.GetIfArgPrefixStr("-g:", TStr("0.9 0.5; 0.5 0.3"), "Parameters for the network (default:0.9 0.5; 0.5 0.3)\n");

  const int NNodes = Env.GetIfArgPrefixInt("-n:", 10240, "Number of nodes (default:1024)\n");
  const int NEdges = Env.GetIfArgPrefixInt("-e:", 11260, "Number of edges (default:1126)\n");
  const TStr wbl_shape_range = Env.GetIfArgPrefixStr("-a:", TStr("1;10"), "Minimum and maximum value for weibull shape (default:1;10)\n");
  const TStr wbl_scale_range = Env.GetIfArgPrefixStr("-b:", TStr("1;10"), "Minimum and maximum value for weibull scale (default:1;10)\n");
  const TStr network_filename = Env.GetIfArgPrefixStr("-f:", TStr("weibull_kronecker_synthetic"), "Name of the network (default:weibull_kronecker_synthetic)\n");

  PIntFltNEDNet network;

  GenerateNetworkStructure(NNodes, NEdges, NetworkParams, network);

  SaveNetwork(network_filename, network, wbl_shape_range, wbl_scale_range);

  Catch
  printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
  
  return 0;
}
