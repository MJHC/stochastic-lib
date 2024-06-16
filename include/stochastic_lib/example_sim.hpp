#include "SymbolTable.hpp"
#include "Vessel.hpp"
#include "Terms.hpp"

namespace stochastic
{
    Vessel abc(int a, int b, int c)
    {
        Vessel v{};
        const auto A = v.addSymbol("A", a);
        const auto B = v.addSymbol("B", b);
        const auto C = v.addSymbol("C", c);
        v.addRule(A + C >> 0.001 >>= B + C);
        return v;
    }

    Vessel circadian_rhythm()
    {
        const auto alphaA = 50;
        const auto alpha_A = 500;
        const auto alphaR = 0.01;
        const auto alpha_R = 50;
        const auto betaA = 50;
        const auto betaR = 5;
        const auto gammaA = 1;
        const auto gammaR = 1;
        const auto gammaC = 2;
        const auto deltaA = 1;
        const auto deltaR = 0.2;
        const auto deltaMA = 10;
        const auto deltaMR = 0.5;
        const auto thetaA = 50;
        const auto thetaR = 100;
        Vessel v{};
        const auto env = v.addInternalSymbol("env", 0);
        const auto DA = v.addSymbol("DA", 1);
        const auto D_A = v.addSymbol("D_A", 0);
        const auto DR = v.addSymbol("DR", 1);
        const auto D_R = v.addSymbol("D_R", 0);
        const auto MA = v.addSymbol("MA", 0);
        const auto MR = v.addSymbol("MR", 0);
        const auto A = v.addSymbol("A", 0);
        const auto R = v.addSymbol("R", 0);
        const auto C = v.addSymbol("C", 0);

        v.addRule(A + DA >> gammaA >>= D_A);
        v.addRule(D_A >> thetaA >>= DA + A);
        v.addRule(A + DR >> gammaR >>= D_R);
        v.addRule(D_R >> thetaR >>= DR + A);
        v.addRule(D_A >> alpha_A >>= MA + D_A);
        v.addRule(DA >> alphaA >>= MA + DA);
        v.addRule(D_R >> alpha_R >>= MR + D_R);
        v.addRule(DR >> alphaR >>= MR + DR);
        v.addRule(MA >> betaA >>= MA + A);
        v.addRule(MR >> betaR >>= MR + R);
        v.addRule(A + R >> gammaC >>= C);
        v.addRule(C >> deltaA >>= R);
        v.addRule(A >> deltaA >>= env);
        v.addRule(R >> deltaR >>= env);
        v.addRule(MA >> deltaMA >>= env);
        v.addRule(MR >> deltaMR >>= env);
        return v;
    }

    Vessel seihr(uint32_t N)
    {
        Vessel v{};
        const auto eps = 0.0009;
        const auto I0 = size_t(std::round(eps * N));
        const auto E0 = size_t(std::round(eps * N * 15));
        const auto S0 = N - I0 - E0;
        const auto R0 = 2.4;
        const auto alpha = 1.0 / 5.1;
        const auto gamma = 1.0 / 3.1;
        const auto beta = R0 * gamma;
        const auto P_H = 0.9e-3;
        const auto kappa = gamma * P_H * (1.0 - P_H);
        const auto tau = 1.0 / 10.12;
        const auto S = v.addSymbol("S", S0);  // susceptible
        const auto E = v.addSymbol("E", E0);  // exposed
        const auto I = v.addSymbol("I", I0);  // infectious
        const auto H = v.addSymbol("H", 0);   // hospitalized
        const auto R = v.addSymbol("R", 0);   // removed/immune (recovered + dead)
        v.addRule(S + I >> beta / N >>= E + I);
        v.addRule(E >> alpha >>= I);
        v.addRule(I >> gamma >>= R);
        v.addRule(I >> kappa >>= H);
        v.addRule(H >> tau >>= R);
        return v;
    }
}  // namespace stochastic
