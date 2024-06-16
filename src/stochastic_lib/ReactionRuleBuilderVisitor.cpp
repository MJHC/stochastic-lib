#include "ReactionRuleBuilderVisitor.hpp"

namespace stochastic
{
    void ReactionRuleBuilderVisitor::visit(const BinaryTerm& t)
    {
        auto op = t.operation();
        if (t.operation() == op_t::crshift && _state == State::DELAY) {
            t.lhs()->accept(*this);
            _state = State::PRODUCTS;
            t.rhs()->accept(*this);
        } else if (t.operation() == op_t::rshift && _state == State::DELAY) {
            t.rhs()->accept(*this);
            _state = State::REACTANTS;
            t.lhs()->accept(*this);
        } else if (t.operation() == op_t::plus && (_state == State::REACTANTS || _state == State::PRODUCTS)) {
            t.lhs()->accept(*this);
            t.rhs()->accept(*this);
        } else
            throw std::invalid_argument("invalid expression!");
    }

    void ReactionRuleBuilderVisitor::visit(const ConstTerm& t)
    {
        if (_state != State::DELAY)
            throw std::invalid_argument("invalid expression!");
        _delay = t.value();
    }

    void ReactionRuleBuilderVisitor::visit(const Symbol& t)
    {
        switch (_state) {
        case State::REACTANTS: _reactants.push_back(t); break;
        case State::PRODUCTS: _products.push_back(t); break;
        default: throw std::invalid_argument("invalid expression!");
        }
    }
}  // namespace stochastic
