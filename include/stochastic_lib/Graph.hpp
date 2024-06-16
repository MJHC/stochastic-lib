#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <set>
#include <string>

#include "utils.hpp"
#include "Node.hpp"

namespace stochastic
{
    class Graph
    {
    private:
        graph_t _graph;
        int _nextId = 0;

    public:
        Graph() {}
        Node addNode(const std::string name, const int r, const int g, const int b);
        void addEdge(const Node& n1, const Node& n2) { _graph[n1].insert(n2); }

        bool containsNode(const Node& node) { return _graph.find(node) != _graph.end(); }
        bool containsEdge(const Node& n1, const Node& n2);

        const graph_t graph() const { return _graph; }
    };

    class NetworkGraph : public Graph
    {
    private:
        std::unordered_map<std::string, Node> _agents;

    public:
        Node addNode(std::string name, bool is_agent);
    };
}  // namespace stochastic

#endif  // !GRAPH_HPP