#ifndef REACTIONRULE_HPP
#define REACTIONRULE_HPP

#include <vector>

#include "Terms.hpp"

namespace stochastic
{
    struct ReactionRule
    {
        const std::vector<Symbol> reactants;
        const double delay;
        const std::vector<Symbol> products;

    public:
        ReactionRule(std::vector<Symbol>&& reactants, double delay, std::vector<Symbol>&& products):
            reactants{std::move(reactants)}, delay{delay}, products{std::move(products)} {};

        friend std::ostream& operator<<(std::ostream& os, const ReactionRule& rule);
    };
}  // namespace stochastic

#endif  // !REACTIONRULE_HPP