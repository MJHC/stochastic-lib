#ifndef REACTIONEXPRVISITOR_HPP
#define REACTIONEXPRVISITOR_HPP

namespace stochastic
{
    class BinaryTerm;
    class ConstTerm;
    class Symbol;
    class ReactionExprVisitor
    {
    public:
        virtual void visit(const BinaryTerm& t) = 0;
        virtual void visit(const ConstTerm& t) = 0;
        virtual void visit(const Symbol& t) = 0;
        virtual ~ReactionExprVisitor() noexcept = default;
    };
}  // namespace stochastic

#endif  // !REACTIONEXPRVISITOR_HPP