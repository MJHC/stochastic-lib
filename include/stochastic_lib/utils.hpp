#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <set>
#include <iterator>
#include <map>
#include <unordered_map>

#include "Node.hpp"

namespace stochastic
{
    template <typename Key, typename Value>
    using state_t = std::map<Key, Value>;

    using graph_t = std::unordered_map<Node, std::set<Node, NodeCmp>, NodeHash>;

    enum class op_t { rshift, crshift, plus };

    template <typename T>
    void write_csv(std::ostream& os, const std::vector<std::string> headers, const std::vector<T>& rows)
    {
        std::copy(headers.begin(), headers.end() - 1, std::ostream_iterator<std::string>(os, ","));
        os << headers.back() << "\n";

        for (const auto& row : rows) {
            std::copy(row.begin(), row.end() - 1, std::ostream_iterator<std::string>(os, ","));
            os << row.back() << "\n";
        }
    }

    void plot_time_series(std::string title, std::string file, const std::vector<double>& time,
                          const std::vector<std::string>& labels, const std::vector<std::vector<int>>& series);

    std::string op_t_str(op_t op);
    std::string rgb_to_hex(int r, int g, int b);

    void write_dot_graph(std::ostream& os, const graph_t& graph);
}  // namespace stochastic

#endif  // !UTILS_HPP