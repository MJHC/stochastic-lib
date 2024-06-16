#include "Vessel.hpp"

using namespace stochastic;

const Symbol Vessel::addSymbol(std::string name, int initial_value)
{
    sys.add(name, initial_value);
    return Symbol(name);
}

const Symbol stochastic::Vessel::addInternalSymbol(std::string name, int initial_value)
{
    sys.add(name, initial_value, true);
    return Symbol(name);
}

const ReactionRule stochastic::Vessel::addRule(const ReactionExpr& expr)
{
    auto rule = builder.build(expr);

    auto dnode = graph.addNode(std::to_string(rule.delay), false);

    for (const auto& a : rule.reactants) {
        auto node = graph.addNode(a.name(), true);
        graph.addEdge(node, dnode);
    }
    for (const auto& a : rule.products) {
        auto node = graph.addNode(a.name(), true);
        graph.addEdge(dnode, node);
    }

    rules.push_back(rule);
    return rule;
}
