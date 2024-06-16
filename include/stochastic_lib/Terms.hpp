#ifndef TERMS_HPP
#define TERMS_HPP

#include <string>
#include <memory>

#include "utils.hpp"
#include "ReactionExprVisitor.hpp"

namespace stochastic
{
    class Term
    {
    public:
        virtual ~Term() noexcept = default;
        virtual void accept(ReactionExprVisitor& v) const = 0;
    };

    class BinaryTerm : public Term
    {
    private:
        std::shared_ptr<Term> _lhs;
        op_t _op;
        std::shared_ptr<Term> _rhs;

    public:
        BinaryTerm(std::shared_ptr<Term> lhs, op_t op, std::shared_ptr<Term> rhs): _lhs{lhs}, _op{op}, _rhs{rhs} {}
        const std::shared_ptr<Term> lhs() const { return _lhs; }
        const op_t operation() const { return _op; }
        const std::shared_ptr<Term> rhs() const { return _rhs; }
        void accept(ReactionExprVisitor& v) const override { v.visit(*this); }
    };

    class ConstTerm : public Term
    {
    private:
        double _value;

    public:
        ConstTerm(double val): _value{val} {}
        double value() const { return _value; }
        void accept(ReactionExprVisitor& v) const override { v.visit(*this); }
    };

    class Symbol : public Term
    {
    private:
        const std::string _name;

    public:
        Symbol(): _name{} {}
        Symbol(const std::string name): _name{std::move(name)} {}
        const std::string name() const { return _name; }
        void accept(ReactionExprVisitor& v) const override { v.visit(*this); }
        bool operator==(const Symbol& other) const { return _name == other._name; }
    };

}  // namespace stochastic

#endif  // !TERMS_HPP