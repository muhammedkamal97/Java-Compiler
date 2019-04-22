//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_FOLLOW_H
#define PROJECT_FOLLOW_H

#endif //PROJECT_FOLLOW_H
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <parser/ProductionRules.h>

using namespace std;

typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::vector< Vertex > container;

map<string, vector<string> *> *
compute_follow(ProductionRules *productions, map<string, vector<string>*>* first_sets);
Graph to_dag(Graph graph, int nodes_count, map<int, vector<int>*>* component_to_nodes);
vector<int>* topological_sort(Graph graph);