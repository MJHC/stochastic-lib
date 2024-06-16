#include "utils.hpp"
#include "matplotlibcpp.h"

using namespace stochastic;

namespace plt = matplotlibcpp;
void stochastic::plot_time_series(std::string title, std::string file, const std::vector<double>& time,
                                  const std::vector<std::string>& labels, const std::vector<std::vector<int>>& series)
{
    if (labels.size() != series.size())
        throw std::runtime_error("labels and series are not the same size");

    for (int i = 0; i < series.size(); i++) {
        const auto& row = series[i];
        plt::plot(time, row, "-", {{"label", labels[i]}});
    }
    plt::title(title);
    plt::xlabel("Time");
    plt::ylabel("Symbol");
    plt::legend();
    plt::savefig(file);
    plt::clf();
}

std::string stochastic::op_t_str(op_t op)
{
    switch (op) {
    case op_t::plus: return " + ";
    case op_t::crshift: return " >>= ";
    case op_t::rshift: return " >> ";
    }
    return " ? ";
}

std::string stochastic::rgb_to_hex(int r, int g, int b)
{
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << r;
    std::string hexRed = ss.str();
    ss.str("");
    ss << std::hex << std::setw(2) << std::setfill('0') << g;
    std::string hexGreen = ss.str();
    ss.str("");
    ss << std::hex << std::setw(2) << std::setfill('0') << b;
    std::string hexBlue = ss.str();
    return "#" + hexRed + hexGreen + hexBlue;
}

void stochastic::write_dot_graph(std::ostream& os, const graph_t& graph)
{
    os << "digraph {\n";

    for (const auto& node_set : graph) {
        std::string hex = rgb_to_hex(node_set.first.r, node_set.first.g, node_set.first.b);
        auto is_delay = node_set.first.r == 255;

        os << "s" << node_set.first.id << "[label=\"" << node_set.first.name << "\",style=\"filled\",fillcolor=\""
           << hex << "\"";
        if (is_delay)
            os << ",shape=\"oval\"]\n";
        else
            os << ",shape=\"box\"]\n";
    }
    for (const auto& node_set : graph) {
        const auto& node = node_set.first;
        for (const auto& edge : node_set.second) {
            os << "s" << node.id << "->" << "s" << edge.id << ";\n";
        }
    }
    os << "}";
}
