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
#include "util.h"

#include <boost/log/trivial.hpp>

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>

void DeBrujinGraph::init(std::vector<std::string> & kmers) {
  int length = kmers.at(0).size() - 1;

  for (std::string kmer : kmers) {
    std::string sourceNode = kmer.substr(0, length);
    std::string targetNode = kmer.substr(1, length);

    // get the node information of the source and target node
    NodeInfo * sourceNodeInfo = &(nodes[sourceNode]);
    sourceNodeInfo->outgoing++;
    NodeInfo * targetNodeInfo = &(nodes[targetNode]);
    targetNodeInfo->incoming++;

    // check if source node is already available in graph
    std::vector<int> * neighboursSourceNode = &(graph[sourceNode]);
    neighboursSourceNode->push_back(targetNodeInfo->id);
    std::vector<int> * neighboursTargetNode = &(graph[targetNode]);

    // update id table
    ids[sourceNodeInfo->id] = sourceNode;
    ids[targetNodeInfo->id] = targetNode;
  }
}

DeBrujinGraph::DeBrujinGraph(std::vector<std::string> kmers) : startNode(""), endNode("") {
  init(kmers);
  assert(graph.size() == ids.size());
  assert(ids.size() == nodes.size());
}

void DeBrujinGraph::print() {
  // print graph information
  std::map<std::string, std::vector<int>>::iterator it;
  for (it=graph.begin(); it!=graph.end(); it++) {
    std::string sourceNode = it->first;
    std::vector<int> neighbours = it->second;
    std::string neighboursStr = "";
    for (int i=0; i<neighbours.size(); i++) {
      neighboursStr.append(std::to_string(neighbours.at(i)));
      neighboursStr.append(", ");
    }
    BOOST_LOG_TRIVIAL(debug) << sourceNode << "\t" << neighboursStr;
  }
  // print node information
  std::map<std::string, NodeInfo>::iterator nodeInfoIt;
  for (nodeInfoIt=nodes.begin(); nodeInfoIt!=nodes.end(); nodeInfoIt++) {
    std::string nodeName = nodeInfoIt->first;
    NodeInfo nodeInfo = nodeInfoIt->second;
    BOOST_LOG_TRIVIAL(debug) << nodeName << ", " << "incoming: " << nodeInfo.incoming << ", outgoing: " << nodeInfo.outgoing;
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

  BOOST_LOG_TRIVIAL(debug) << "has eulerian path: " << hep;

  if (!hep) {
    return result;
  }

  // TODO: check if the graph has at least one edge

  // create data to store visited nodes
  std::map<std::string, std::vector<bool>> visitedEdges;
  std::map<std::string, bool> visitedNodes;
  std::vector<std::string> nodeNames;

  // fill in initial values for all nodes
  BOOST_LOG_TRIVIAL(debug) << "fill up initial values";
  std::map<std::string, std::vector<int>>::iterator gIt;
  for (gIt=graph.begin(); gIt!=graph.end(); gIt++) {
    std::string nodename = gIt->first;
    nodeNames.push_back(nodename);
    visitedNodes[nodename] = false;
    std::vector<int> neighbours = gIt->second;
    std::vector<bool> edges(neighbours.size());
    for (int i=0; i<edges.size(); i++) {
      edges[i] = false;
    }
    visitedEdges[nodename] = edges;
  }

  // check if start node is set
  BOOST_LOG_TRIVIAL(debug) << "check start node: " << startNode;
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
  BOOST_LOG_TRIVIAL(debug) << "start node: " << startNode;

  // start modified DFS
  BOOST_LOG_TRIVIAL(debug) << "start dfs...";
  recursiveCallCounter = 0;
  dfs(result, visitedNodes, visitedEdges, startNode);

  // start modified DFS iterative version
  //BOOST_LOG_TRIVIAL(debug) << "start dfs iterative...";
  //dfs(result, visitedNodes, visitedEdges, startNode);

  std::reverse(result.begin(), result.end());

  return result;
}

// TODO: Calling this method 34000 times causes a segmentation fault
void DeBrujinGraph::dfs(
  std::vector<std::string> & solution,
  std::map<std::string, bool> & visitedNodes,
  std::map<std::string, std::vector<bool>> & visitedEdges,
  std::string currentNode) {

  recursiveCallCounter++;

  // debug output
  //BOOST_LOG_TRIVIAL(debug) << "Current Node: " << currentNode << ", Call: " << recursiveCallCounter;

  // move forward with dfs until the end node
  std::vector<int> & outgoingEdgesIds = graph[currentNode];
  std::vector<bool> & visitedOutgoingEdges = visitedEdges[currentNode];

  // both vectors need to have the same size
  assert(outgoingEdgesIds.size() == visitedOutgoingEdges.size());

  // loop through all neighbours & edges
  for (int i=0; i<outgoingEdgesIds.size(); i++) {
    if (!visitedOutgoingEdges[i]) {
      int edgeId = outgoingEdgesIds[i];
      std::string targetNode = ids[edgeId];
      // mark node as visitedEdges
      visitedOutgoingEdges[i] = true;
      dfs(solution, visitedNodes, visitedEdges, targetNode);
    }
  }

  // no more unvisited edges from that node
  solution.push_back(currentNode);
}

void DeBrujinGraph::dfsIterative(
  std::vector<std::string> & solution,
  std::map<std::string, bool> & visitedNodes,
  std::map<std::string, std::vector<bool>> & visitedEdges,
  std::string currentNode) {

  std::vector<int> & outgoingEdgesIds = graph[currentNode];
  std::vector<bool> & visitedOutgoingEdges = visitedEdges[currentNode];


}

NodeInfo::NodeInfo() : incoming(0), outgoing(0) {
  id = Util::getUid();
}
