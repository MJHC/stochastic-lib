#ifndef VESSEL_HPP
#define VESSEL_HPP

#include <vector>

#include "SymbolTable.hpp"
#include "Graph.hpp"
#include "ReactionRuleBuilderVisitor.hpp"
#include "ReactionRule.hpp"
#include "Terms.hpp"

namespace stochastic
{
    class Vessel
    {
    private:
        SymbolTable<std::string, int> sys{};
        NetworkGraph graph{};
        ReactionRuleBuilderVisitor builder{};
        std::vector<ReactionRule> rules{};

    public:
        Vessel() {}
        const SymbolTable<std::string, int>& symbols() const { return sys; }
        const graph_t networkGraph() const { return graph.graph(); }
        const std::vector<ReactionRule>& reactionRules() const { return rules; }

        const Symbol addSymbol(std::string name, int initial_value);
        const Symbol addInternalSymbol(std::string name, int initial_value);

        const ReactionRule addRule(const ReactionExpr& expr);
    };
}  // namespace stochastic

#endif  // !VESSEL_HPP
