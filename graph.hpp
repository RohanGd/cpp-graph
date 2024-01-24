#pragma once
#include "uuid.hpp"
#include <queue>
#include <stack>

namespace graph
{
    using std::string, std::vector, std::queue, std::stack, std::pair;
    // node class for the graph.
    // T is the type of the value of the node
    // id is a unique identifier for the node
    template <typename T>
    class node
    {
    public:
        node(T value) : value(value) {}
        T value;
        const string id = uuid::generate_uuid();
    };

    // edge class for the graph.
    // from and to are the ids of the nodes
    // weight is the weight of the edge
    class edge
    {
    public:
        edge(string from, string to, uint32_t weight=0) : from(from), to(to), weight(weight) {}
        bool is_copy(edge e) { return (e.from == from && e.to == to); }
        const string from;
        const string to;
        uint32_t weight = 0;
    };

    // graph class
    // T is the type of the value of the node
    // nodes is a vector of pointers to the nodes
    // edges is a vector of pointers to the edges
    template <typename T>
    class graph
    {
    public:
        graph() {}

        void add_node(T value) {
            // add a node to the graph
            node<T> * n = new node<T>(value);
            nodes.push_back(n);
        }
        void add_edge(string from, string to, uint32_t weight = 0) {
            // add an edge to the graph
            // if the edge already exists, update the weight
            // if the edge does not exist, create it
            for(edge* e : edges)
                if(e->is_copy(edge(from, to))) {
                    e->weight = weight;
                    return;
                }
            edge* e = new edge(from, to, weight);
            edges.push_back(e);
        }
        void describe() {
            std::cout << "\nGraphNodes:" << std::endl;
            for (auto &node : nodes) {
                std::cout << node->id << ": [" << node->value << "]" << std::endl;
            }
            std::cout << "\nEdges:" << std::endl;
            for (auto &edge : edges) {
                std::cout << edge->from << " -> " << edge->to << " (" << edge->weight << ")" << std::endl;
            }
            std::cout << "Shape: (nodes, edges) = (" << nodes.size() << ", " << edges.size() << ")" << std::endl;
        }
        node<T>* get_node(string& node_id) { 
            // get a pointer to a node by its id
            for(node<T>* n : nodes)
                if(n->id == node_id)
                    return n;
            return nullptr;
        }
        vector<vector<node<T>*>> bfs() {
            // breadth first search
            // returns a vector of pointers to the nodes in the order they were visited
            vector<vector<node<T>*>> paths;
            vector<bool> visited(nodes.size(), false);
            while (std::find(visited.begin(), visited.end(), false) != visited.end()) {
                vector<node<T>*> path;
                queue<node<T>*> q;
                q.push(nodes[std::distance(visited.begin(), std::find(visited.begin(), visited.end(), false))]);
                while(!q.empty()) {
                    node<T>* n = q.front();
                    q.pop();
                    if(visited[std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), n))])
                        continue;
                    path.push_back(n);
                    visited[std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), n))] = true;
                    for(edge* e : edges) {
                        if(e->from == n->id) {
                            for(node<T>* n2 : nodes) {
                                if(n2->id == e->to) {
                                    q.push(n2);
                                }
                            }
                        }
                    }
                }
                paths.push_back(path);
            }
            return paths;        
        }
        vector<vector<node<T>*>> dfs() {
            // depth first search
            // returns a vector of pointers to the nodes in the order they were visited
            vector<vector<node<T>*>> paths;
            vector<bool> visited(nodes.size(), false);
            while (std::find(visited.begin(), visited.end(), false) != visited.end()) {
                vector<node<T>*> path;
                stack<node<T>*> s;
                s.push(nodes[std::distance(visited.begin(), std::find(visited.begin(), visited.end(), false))]);
                while(!s.empty()) {
                    node<T>* n = s.top();
                    s.pop();
                    if(visited[std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), n))])
                        continue;
                    path.push_back(n);
                    visited[std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), n))] = true;
                    for(edge* e : edges) {
                        if(e->from == n->id) {
                            for(node<T>* n2 : nodes) {
                                if(n2->id == e->to) {
                                    s.push(n2);
                                }
                            }
                        }
                    }
                }
                paths.push_back(path);
            }
            return paths;
        }
       
        vector<node<T>*> nodes;
        vector<edge*> edges;
    };

} // namespace graph
