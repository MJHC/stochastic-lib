#ifndef REACTIONEXPR_HPP
#define REACTIONEXPR_HPP

#include <memory>

#include "Terms.hpp"
#include "utils.hpp"

namespace stochastic
{
    class ReactionExpr
    {
    private:
        std::shared_ptr<Term> _term;

    public:
        ReactionExpr(double c): _term{std::make_shared<ConstTerm>(c)} {}
        ReactionExpr(const ConstTerm& c): _term{std::make_shared<ConstTerm>(c)} {}
        ReactionExpr(const Symbol& v): _term{std::make_shared<Symbol>(v)} {}
        ReactionExpr(std::shared_ptr<Term> term): _term{term} {}
        std::shared_ptr<Term> term() const { return _term; }
    };

    inline ReactionExpr operator+(const ReactionExpr& lhs, const ReactionExpr& rhs)
    {
        return ReactionExpr(std::make_shared<BinaryTerm>(lhs.term(), op_t::plus, rhs.term()));
    }

    inline ReactionExpr operator>>(const ReactionExpr& lhs, const ReactionExpr& rhs)
    {
        return ReactionExpr(std::make_shared<BinaryTerm>(lhs.term(), op_t::rshift, rhs.term()));
    }

    inline ReactionExpr operator>>=(const ReactionExpr& lhs, const ReactionExpr& rhs)
    {
        return ReactionExpr(std::make_shared<BinaryTerm>(lhs.term(), op_t::crshift, rhs.term()));
    }
}  // namespace stochastic

#endif  // !REACTIONEXPR_HPP