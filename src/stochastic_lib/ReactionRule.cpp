#include "ReactionRule.hpp"

namespace stochastic
{
    std::ostream& operator<<(std::ostream& os, const ReactionRule& rule)
    {
        for (size_t i = 0; i < rule.reactants.size(); ++i) {
            os << rule.reactants[i].name();
            if (i < rule.reactants.size() - 1)
                os << " + ";
        }
        os << " >> " << rule.delay << " >>= ";

        for (size_t i = 0; i < rule.products.size(); ++i) {
            os << rule.products[i].name();
            if (i < rule.products.size() - 1)
                os << " + ";
        }
        return os;
    }
}  // namespace stochastic
