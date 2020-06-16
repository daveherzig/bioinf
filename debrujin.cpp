/***
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Copyright 2020, David Herzig (dave.herzig@gmail.com)
***/

#include "debrujin.h"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>

void DeBrujinGraph::init(std::vector<std::string> kmers) {
  int length = kmers.at(0).size() - 1;

  for (std::string kmer : kmers) {
    std::string sourceNode = kmer.substr(0, length);
    std::string targetNode = kmer.substr(1, length);

    // check if source node is already available in graph
    std::vector<std::string> * neighbours = &(graph[sourceNode]);
    neighbours->push_back(targetNode);

    // get the node information of the source and target node
    NodeInfo * sourceNodeInfo = &(nodes[sourceNode]);
    sourceNodeInfo->outgoing++;
    NodeInfo * targetNodeInfo = &(nodes[targetNode]);
    targetNodeInfo->incoming++;
  }
}

DeBrujinGraph::DeBrujinGraph(std::vector<std::string> kmers) : startNode(""), endNode("") {
  init(kmers);
}

void DeBrujinGraph::print() {
  // print graph information
  std::map<std::string, std::vector<std::string>>::iterator it;
  for (it=graph.begin(); it!=graph.end(); it++) {
    std::string sourceNode = it->first;
    std::vector<std::string> neighbours = it->second;
    std::cout << sourceNode << "\t";
    for (int i=0; i<neighbours.size(); i++) {
      std::cout << neighbours.at(i) << ", ";
    }
    std::cout << std::endl;
  }
  // print node information
  std::map<std::string, NodeInfo>::iterator nodeInfoIt;
  for (nodeInfoIt=nodes.begin(); nodeInfoIt!=nodes.end(); nodeInfoIt++) {
    std::string nodeName = nodeInfoIt->first;
    NodeInfo nodeInfo = nodeInfoIt->second;
    std::cout << nodeName << ", " << "incoming: " << nodeInfo.incoming << ", outgoing: " << nodeInfo.outgoing << std::endl;
  }
}

bool DeBrujinGraph::hasEulerianPath() {
  std::map<std::string, NodeInfo>::iterator nodeInfoIt;

  int p1 = false; // incoming-outgoing=1
  int m1 = false; // incoming-outgoing=-1

  for (nodeInfoIt=nodes.begin(); nodeInfoIt!=nodes.end(); nodeInfoIt++) {
    std::string name = nodeInfoIt->first;
    int incoming = nodeInfoIt->second.incoming;
    int outgoing = nodeInfoIt->second.outgoing;
    if (incoming - outgoing == 0) {
      // do nothing
    } else if (incoming - outgoing == 1) {
      p1++;
      endNode = name;
    } else if (incoming - outgoing == -1) {
      m1++;
      startNode = name;
    } else {
      return false;
    }

    if (p1 > 1 || m1 > 1) {
      return false;
    }
  }

  return true;
}

std::vector<std::string> DeBrujinGraph::eulerianPath() {

  std::vector<std::string> result;

  bool hep = hasEulerianPath();

  if (!hep) {
    return result;
  }

  // TODO: check if the graph has at least one edge

  // create data to store visited nodes
  std::map<std::string, std::vector<bool>> visitedEdges;
  std::map<std::string, bool> visitedNodes;
  std::vector<std::string> nodeNames;

  // fill in initial values for all nodes
  std::map<std::string, std::vector<std::string>>::iterator gIt;
  for (gIt=graph.begin(); gIt!=graph.end(); gIt++) {
    std::string nodename = gIt->first;
    nodeNames.push_back(nodename);
    visitedNodes[nodename] = false;
    std::vector<std::string> neighbours = gIt->second;
    std::vector<bool> edges(neighbours.size());
    for (int i=0; i<edges.size(); i++) {
      edges[i] = false;
    }
    visitedEdges[nodename] = edges;
  }

  //std::cout << "StartNode: " << startNode << std::endl;

  // check if start node is set
  if (startNode == "") {
    // choose a random start node
    bool zeroDegreeNode = true;
    while (zeroDegreeNode) {
      int nodeIndex = rand() % nodeNames.size();
      std::string nodeName = nodeNames[nodeIndex];
      if (visitedEdges[nodeName].size() > 0) {
        startNode = nodeName;
        zeroDegreeNode = false;
      }
    }
  }

  // start modified DFS
  dfs(result, visitedNodes, visitedEdges, startNode);

  std::reverse(result.begin(), result.end());

  return result;
}

void DeBrujinGraph::dfs(
  std::vector<std::string> & solution,
  std::map<std::string, bool> & visitedNodes,
  std::map<std::string, std::vector<bool>> & visitedEdges,
  std::string currentNode) {

  // debug output
  //std::cout << "Current Node: " << currentNode << std::endl;

  // move forward with dfs until the end node
  std::vector<std::string> & outgoingEdges = graph[currentNode];
  std::vector<bool> & visitedOutgoingEdges = visitedEdges[currentNode];

  // both vectors need to have the same size
  assert(outgoingEdges.size() == visitedOutgoingEdges.size());

  // loop through all neighbours & edges
  for (int i=0; i<outgoingEdges.size(); i++) {
    if (!visitedOutgoingEdges[i]) {
      std::string targetNode = outgoingEdges[i];
      // mark node as visitedEdges
      visitedOutgoingEdges[i] = true;
      dfs(solution, visitedNodes, visitedEdges, targetNode);
    }
  }

  // no more unvisited edges from that node
  solution.push_back(currentNode);
}

NodeInfo::NodeInfo() : incoming(0), outgoing(0) {
}