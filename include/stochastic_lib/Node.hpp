#ifndef NODE_HPP
#define NODE_HPP

#include <string>

namespace stochastic
{
    struct Node
    {
        const int id;
        const std::string name;
        const int r;
        const int g;
        const int b;

        Node(): id{-1}, name{""}, r{0}, g{0}, b{0} {}
        Node(const int id, const std::string name, const int r, const int g, const int b):
            id{id}, name{std::move(name)}, r{r}, g{g}, b{b}
        {}

        bool operator==(const Node& other) const { return id == other.id; }
        bool operator<(const Node& other) const { return id < other.id; }
    };

    struct NodeHash
    {
        std::size_t operator()(const Node& node) const { return std::hash<int>()(node.id); }
    };

    struct NodeCmp
    {
        bool operator()(const Node& n1, const Node& n2) const { return n1 < n2; }
    };
}  // namespace stochastic

#endif  // !NODE_HPP