//
// Created by mario_hunter on 4/19/19.
//

#include <boost/config.hpp>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <iostream>
#include "Follow.h"



// initialize follow sets as empty
// initialize map<non_terminal, node_id>
// initialize map<node_id, non_terminal>
// initialize initial graph

// loop through productions
// for each non-terminal in production:
// append its follow set with next terminal if exists
// append its follow set with next non-terminal's first set if exists
// if current symbol is last in its production, let its node point to the lhs node
// if next non-terminal has epsilon in its first set, remove it and repeat for next symbol in production

// create DAG from graph
// get topological sort of the nodes
// resolve dependencies and adjust follow sets in topological order

map<string, vector<string> *> *
compute_follow(ProductionRules *productions, map<string, vector<string>*>* first_sets) {
    // Initialize necessary structures
    map<string, set<string>*>* follow_sets = new map<string, set<string>*>;
    map<string, int>* node_id_map = new map<string, int>;
    map<int, string>* non_terminal_map = new map<int, string>;
    int non_terminals_count = productions->non_terminals->size();
    Graph graph(non_terminals_count);

    int id = 0;
    for(auto non_terminal : *productions->non_terminals) {
        follow_sets->insert(make_pair(non_terminal, new set<string>));
        node_id_map->insert(make_pair(non_terminal, id));
        non_terminal_map->insert(make_pair(id, non_terminal));
        id++;
    }

    // Put $ in for the non terminal in the initial production
    follow_sets->at(productions->production_rules[0]->name->value)->insert("$");

    // Iterate on productions to fill initial follow sets and build dependency graph
    for (int i = 0; i < productions->size; i++) {
        Production* production = productions->production_rules[i];
        string lhs_non_terminal = production->name->value;

        for (vector<GrammarSymbol*>* partial_production : *production->productions) {
            for (int i = 0; i < partial_production->size(); i++) {
                GrammarSymbol* current_symbol = partial_production->at(i);
                string current_symbol_string = current_symbol->value;
                if (current_symbol->type == symbol_type::Terminal) continue;

                int j = i+1;
                bool terminal_found = false;
                bool has_epsilon = true;
                // Iterate to the end of the production till a terminal is found
                // or a non-terminal without epsilon in its first set is found
                while (j < partial_production->size() && !terminal_found && has_epsilon) {
                    GrammarSymbol* neighbour_symbol = partial_production->at(j);
                    string neighbour_symbol_string = neighbour_symbol->value;

                    if (neighbour_symbol->type == symbol_type::Terminal) {
                        terminal_found = true;
                        follow_sets->at(current_symbol_string)->insert(neighbour_symbol_string);
                    }
                    else {
                        has_epsilon = false;
                        for (auto terminal : *first_sets->at(neighbour_symbol_string)) {
                            if (terminal == "\\L") has_epsilon = true;
                            else {
                                follow_sets->at(current_symbol_string)->insert(terminal);
                            }
                        }
                        j++;
                    }
                }

                if (j == partial_production->size()) {      // Reached end of the partial production
                    // Add dependency
                    int source_node = node_id_map->at(current_symbol_string);
                    int destination_node = node_id_map->at(lhs_non_terminal);
                    boost::add_edge(source_node, destination_node, graph);
                }
            }
        }
    }

    // Convert dependency graph to DAG and perform topological sorting

    map<int, vector<int>*>* component_to_nodes = new map<int, vector<int>*>;
    map<int, set<string>*>* component_follow_set_map = new map<int, set<string>*>;
    Graph dag = to_dag(graph, non_terminals_count, component_to_nodes);
    vector<int>* topological_order = topological_sort(dag);

    // Resolve follow set dependencies

    for (int i = 0; i < topological_order->size(); i++) {
        int component = topological_order->at(i);
        vector<int>* nodes = component_to_nodes->at(component);
        set<string>* component_follow_set = new set<string>;

        // Merge follow sets of component into one set
        for (int node : *nodes) {
            string non_terminal = non_terminal_map->at(node);
            set<string>* non_terminal_follow_set = follow_sets->at(non_terminal);

            for (auto symbol : *non_terminal_follow_set) component_follow_set->insert(symbol);
        }


        // Resolve dependencies from other components
        if (i != 0) {   // Sink component has no dependencies
            boost::graph_traits<Graph>::vertices_size_type dag_nodes_count = boost::num_vertices(dag);
            auto neighbours = boost::adjacent_vertices(component, dag);
            for (auto neighbour : make_iterator_range(neighbours)) {
                set<string>* neighbour_follow_set = component_follow_set_map->at(neighbour);
                for (auto symbol : *neighbour_follow_set) component_follow_set->insert(symbol);
            }
        }

        // Reassign full follow sets to all non terminals in the component
        for (int node : *nodes) {
            string non_terminal = non_terminal_map->at(node);
            (*follow_sets)[non_terminal] = new set<string>(*component_follow_set);
        }

        // Place component follow set in map to be used with dependant components
        component_follow_set_map->insert(make_pair(component, component_follow_set));
    }


    // Format output
    map<string, vector<string>*>* follow_vectors = new map<string, vector<string>*>;
    for(auto non_terminal : *productions->non_terminals) {
        set<string>* follow_set = follow_sets->at(non_terminal);
        follow_vectors->insert(make_pair(non_terminal, new vector<string>(follow_set->begin(), follow_set->end())));
    }
    return follow_vectors;
}

Graph to_dag(Graph graph, int nodes_count, map<int, vector<int>*>* component_to_nodes) {
    std::vector<int> strong_components(nodes_count);
    int strong_components_count = boost::strong_components(graph, boost::make_iterator_property_map(
            strong_components.begin(), boost::get(boost::vertex_index, graph), strong_components[0]));

    Graph dag(strong_components_count);

    for (int i = 0; i < strong_components_count; i++) {
        component_to_nodes->insert(make_pair(i, new vector<int>));
    }
    for (int i = 0; i < strong_components.size(); ++i) {
        int v1 = i;
        int component1 = strong_components[i];
        component_to_nodes->at(component1)->push_back(v1);
        auto neighbours = boost::adjacent_vertices(v1, graph);
        for (auto v2 : make_iterator_range(neighbours)) {
            int component2 = strong_components[v2];
            if (component1 != component2)
                boost::add_edge (component1, component2, dag);
        }
    }

    return dag;
}

vector<int>* topological_sort(Graph graph) {
    vector<int>* order = new vector<int>;
    container c;
    boost::topological_sort(graph, std::back_inserter(c));

    for ( container::iterator ii=c.begin(); ii!=c.end(); ++ii)
        order->push_back(*ii);

    return order;
}
