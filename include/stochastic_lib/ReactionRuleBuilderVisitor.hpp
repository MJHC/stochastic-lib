#ifndef REACTIONRULEBUILDERVISITOR_HPP
#define REACTIONRULEBUILDERVISITOR_HPP

#include <vector>

#include "ReactionExprVisitor.hpp"
#include "ReactionExpr.hpp"
#include "ReactionRule.hpp"
#include "utils.hpp"

namespace stochastic
{
    class ReactionRuleBuilderVisitor : public ReactionExprVisitor
    {
    private:
        enum class State { REACTANTS, DELAY, PRODUCTS } _state;
        std::vector<Symbol> _reactants;
        double _delay;
        std::vector<Symbol> _products;
        void reset()
        {
            _state = State::DELAY;
            _reactants.clear();
            _delay = 0.0;
            _products.clear();
        }

    public:
        ReactionRule build(const ReactionExpr& expr)
        {
            reset();
            expr.term()->accept(*this);
            return {std::move(_reactants), _delay, std::move(_products)};
        }
        void visit(const BinaryTerm& t) override;
        void visit(const ConstTerm& t) override;
        void visit(const Symbol& t) override;
    };
}  // namespace stochastic

#endif  // !REACTIONRULEBUILDERVISITOR_HPP