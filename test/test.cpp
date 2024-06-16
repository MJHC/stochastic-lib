#include <doctest/doctest.h>

#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>

#include "stochastic_lib.hpp"
#include "example_sim.hpp"

using namespace stochastic;

class PrintExprVisitor : public ReactionExprVisitor
{
private:
    std::ostream& _stream;

public:
    PrintExprVisitor(std::ostream& stream): _stream{stream} {}
    void visit(const BinaryTerm& t) override
    {
        t.lhs()->accept(*this);
        _stream << op_t_str(t.operation());
        t.rhs()->accept(*this);
    }
    void visit(const ConstTerm& t) override { _stream << t.value(); }
    void visit(const Symbol& t) override { _stream << t.name(); }
};

TEST_CASE("Test Expressions")
{
    auto builder = ReactionRuleBuilderVisitor();
    std::stringstream ss;
    auto a = Symbol("a");
    auto b = Symbol("b");
    auto c = Symbol("c");
    double d = 5;

    SUBCASE("Test Operator Overloading")
    {
        auto expr = a + c >> d >>= a + b;
        auto visitor = PrintExprVisitor(ss);
        expr.term()->accept(visitor);

        CHECK(ss.str() == "a + c >> 5 >>= a + b");
    }

    SUBCASE("Test Build ReactionRule")
    {
        auto expr = a + c >> d >>= a + b;
        auto rule = builder.build(expr);
        CHECK(rule.delay == 5);
        CHECK(rule.reactants == std::vector<Symbol>{a, c});
        CHECK(rule.products == std::vector<Symbol>{a, b});
    }

    SUBCASE("Test Build ReactionRule missing >>=")
    {
        auto expr = a + c >> a + b;
        CHECK_THROWS_WITH(builder.build(expr), "invalid expression!");
    }

    SUBCASE("Test Build ReactionRule missing >>")
    {
        auto expr = a + c >>= a + b;
        CHECK_THROWS_WITH(builder.build(expr), "invalid expression!");
    }

    SUBCASE("Test Build ReactionRule missing >> and >>=")
    {
        auto expr = a + a + b;
        CHECK_THROWS_WITH(builder.build(expr), "invalid expression!");
    }

    SUBCASE("Test Build ReactionRule missing everything")
    {
        auto expr = a;
        CHECK_THROWS_WITH(builder.build(expr), "invalid expression!");
    }
}

TEST_CASE("Test Graph")
{
    Graph graph{};

    SUBCASE("Test addNode")
    {
        auto node = graph.addNode("a", 0, 0, 0);
        CHECK(graph.containsNode(node));
    }

    SUBCASE("Test addEdge")
    {
        auto n1 = graph.addNode("a", 0, 0, 0);
        auto n2 = graph.addNode("b", 0, 0, 0);
        graph.addEdge(n1, n2);
        CHECK(graph.containsEdge(n1, n2));
    }

    SUBCASE("Test Const Iterator")
    {
        auto n1 = graph.addNode("a", 0, 0, 0);
        auto n2 = graph.addNode("b", 0, 0, 0);
        graph.addEdge(n1, n2);
        graph.addEdge(n2, n1);
        std::stringstream ss{};
        for (const auto& pair : graph.graph()) {
            if (pair.second.size() == 0)
                continue;
            ss << pair.first.name << ":";
            for (const auto& edgeNode : pair.second)
                ss << edgeNode.name;
            ss << ";";
        }
        auto res = ss.str();
        CHECK(res == "b:a;a:b;");
    }
}

TEST_CASE("Test NetworkGraph")
{
    NetworkGraph graph{};

    SUBCASE("Test No Duplicate Agents")
    {
        auto n1 = graph.addNode("a", true);
        auto n2 = graph.addNode("b", false);
        auto n3 = graph.addNode("a", true);
        CHECK(n1 == n3);
    }
}

TEST_CASE("Test Symbol Table")
{
    SymbolTable<std::string, int> sys{};

    SUBCASE("Add")
    {
        sys.add("a", 5);
        CHECK(sys.contains("a"));
    }

    SUBCASE("Add throws")
    {
        sys.add("a", 5);
        CHECK_THROWS_WITH(sys.add("a", 5), "Name 'a' already exists");
    }

    SUBCASE("Get")
    {
        sys.add("a", 5);
        CHECK(sys.get("a") == 5);
    }

    SUBCASE("Get throws") { CHECK_THROWS_WITH(sys.get("a"), "Name 'a' does not exist"); }

    SUBCASE("Get and modify")
    {
        sys.add("a", 5);
        sys.get("a")++;
        CHECK(sys.get("a") == 6);
    }
}

TEST_CASE("Test Vessel")
{
    auto v = abc(100, 0, 1);
    SUBCASE("Test All Rules exist")
    {
        std::vector<std::string> expected = {"A + C >> 0.001 >>= B + C"};

        std::vector<std::string> actual = {};
        for (const auto& r : v.reactionRules()) {
            actual.push_back((std::stringstream{} << r).str());
        }
        CHECK(actual.size() == expected.size());
        CHECK(actual == expected);
    }
    SUBCASE("Test All Symbols exist")
    {
        std::vector<std::string> expected = {"A", "B", "C"};
        auto sys = v.symbols();

        for (const auto& n : expected) {
            CHECK(sys.contains(n));
        }
    }
    SUBCASE("Test Network Graph")
    {
        std::string expected = "C:0.001000;A:0.001000;0.001000:CB;";
        auto graph = v.networkGraph();

        std::stringstream ss{};
        for (auto& pair : graph) {
            if (pair.second.size() == 0)
                continue;
            ss << pair.first.name << ":";
            for (auto& edgeNode : pair.second)
                ss << edgeNode.name;
            ss << ";";
        }
        CHECK(ss.str() == expected);
    }
}

TEST_CASE("Test Simulator")
{
    SUBCASE("Correct Output")
    {
        auto v = abc(100, 0, 1);
        Simulator sim{v, 5};
        std::vector<int> t{0, 0, 18, 23, 63};
        std::vector<int> a{100, 99, 98, 97, 96};
        std::vector<int> c{1, 1, 1, 1, 1};

        std::vector<int> t_a{};
        std::vector<int> a_a{};
        std::vector<int> c_a{};
        t_a.reserve(10);
        a_a.reserve(10);
        c_a.reserve(10);
        for (const auto& serie : sim.simulate(63)) {
            t_a.emplace_back(static_cast<int>(serie.first));
            a_a.emplace_back(serie.second->get("A"));
            c_a.emplace_back(serie.second->get("C"));
        }

        CHECK(t == t_a);
        CHECK(a == a_a);
        CHECK(c == c_a);
    }
    SUBCASE("Parallel Simulation")
    {
        auto v = abc(100, 0, 1);
        Simulator sim{v, 5};
        int sim_rows = 0;
        for (const auto& sim_serie : sim.simulate_n_queue(10, 3)) {
            sim_rows++;
        }
        CHECK(sim_rows == 9);
    }
}
