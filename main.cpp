#include <iostream>
#include "graph.hpp"

class tempclass{
public:
    tempclass(int a, int b):a(a),b(b){}
    int a;
    int b;

    // overload to print the value of the class
    friend std::ostream& operator<<(std::ostream& os, const tempclass& temp){
        os << temp.a << " " << temp.b;
        return os;
    }
};

int main()
{

    // graph::graph<tempclass> g;
    // g.add_node(tempclass(1,2));
    // g.add_node(tempclass(3,4));
    // g.add_node(tempclass(5,6));
    // g.add_node(tempclass(7,8));


    // g.add_edge(g.nodes[0]->id, g.nodes[1]->id);
    // g.add_edge(g.nodes[1]->id, g.nodes[0]->id);
    // g.add_edge(g.nodes[0]->id, g.nodes[1]->id, 5);
    // g.add_edge(g.nodes[1]->id, g.nodes[2]->id);
    // g.add_edge(g.nodes[2]->id, g.nodes[3]->id);
    // g.add_edge(g.nodes[3]->id, g.nodes[0]->id);

    graph::graph<std::string> g;

    g.add_node("a");
    g.add_node("b");
    g.add_node("c");
    g.add_node("d");
    g.add_node("e");
    g.add_node("f");

    g.add_edge(g.nodes[0]->id, g.nodes[1]->id, 3);
    g.add_edge(g.nodes[1]->id, g.nodes[0]->id, 3);
    g.add_edge(g.nodes[0]->id, g.nodes[3]->id, 2);
    g.add_edge(g.nodes[3]->id, g.nodes[0]->id, 2);
    g.add_edge(g.nodes[0]->id, g.nodes[4]->id, 1);
    g.add_edge(g.nodes[4]->id, g.nodes[0]->id, 1);

    g.add_edge(g.nodes[1]->id, g.nodes[3]->id, 1);
    g.add_edge(g.nodes[3]->id, g.nodes[1]->id, 1);
    g.add_edge(g.nodes[1]->id, g.nodes[4]->id, 5);
    g.add_edge(g.nodes[4]->id, g.nodes[1]->id, 5);

    g.add_edge(g.nodes[3]->id, g.nodes[4]->id, 2);
    g.add_edge(g.nodes[4]->id, g.nodes[3]->id, 2);

    g.add_edge(g.nodes[2]->id, g.nodes[5]->id, 2);
    g.add_edge(g.nodes[5]->id, g.nodes[2]->id, 2);


    g.describe();

    std::vector<std::vector<graph::node<std::string> *>> paths = g.bfs();
    std::cout << "\nBFS routes:" << std::endl;
    for (std::vector<graph::node<std::string>*> path : paths){
        for(graph::node<std::string>* n : path)
            std::cout << n->value << " ";
        std::cout << std::endl;
    }

    paths = g.dfs();
    std::cout << "\nDFS routes:" << std::endl;
    for (std::vector<graph::node<std::string>*> path : paths){
        for(graph::node<std::string>* n : path)
            std::cout << n->value << " ";
        std::cout << std::endl;
    }

    // std::pair<std::vector<graph::node<std::string>*>, uint32_t> shortest_path = g.dijkstra(g.nodes[1]->id, g.nodes[4]->id);
    // std::cout << "\nShortest path:" << std::endl;
    // for(graph::node<std::string>* n : shortest_path.first)
    //     std::cout << n->value << " ";

    // std::cout << "\nWeight: " << shortest_path.second << std::endl;


    return 0;
}
