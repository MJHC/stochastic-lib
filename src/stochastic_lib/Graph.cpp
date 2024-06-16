#include "Graph.hpp"

namespace stochastic
{
    Node Graph::addNode(const std::string name, const int r, const int g, const int b)
    {
        auto n = Node(_nextId, name, r, g, b);
        _graph.emplace(n, std::set<Node, NodeCmp>{});
        _nextId++;
        return n;
    }

    bool Graph::containsEdge(const Node& n1, const Node& n2)
    {
        if (!containsNode(n1) && !containsNode(n2))
            return false;

        auto& edges = _graph[n1];
        auto found = edges.find(n2) != edges.end();
        return found;
    }

    Node NetworkGraph::addNode(std::string name, bool is_agent)
    {
        const int r = is_agent ? 0 : 255;
        const int g = 255;
        const int b = is_agent ? 255 : 0;
        if (is_agent && !_agents.contains(name))
            _agents.insert(std::make_pair(name, Graph::addNode(name, r, g, b)));
        if (is_agent)
            return _agents.at(name);
        return Graph::addNode(name, r, g, b);
    }

}  // namespace stochastic
