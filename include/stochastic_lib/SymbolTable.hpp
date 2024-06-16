#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <vector>
#include <set>

#include "utils.hpp"

namespace stochastic
{
    /*
    3. Implement a generic symbol table to store and lookup objects of user-defined key and value types. Support
        failure cases when a) the table does not contain a looked up symbol, b) the table already contains a symbol that
        is being added. Demonstrate the usage of the symbol table with the reactants (names and initial counts).
    */
    template <typename Key, typename Value>
    class SymbolTable
    {
    private:
        state_t<Key, Value> _state;
        std::set<Key> _internalSymbols;

    public:
        SymbolTable(){};

        const std::vector<Key> keys(bool exclude_internal) const
        {
            std::vector<Key> keys{};
            if (exclude_internal)
                keys.reserve(_state.size() - _internalSymbols.size());
            else
                keys.reserve(_state.size());

            for (const auto& pair : _state) {
                if (exclude_internal && _internalSymbols.contains(pair.first))
                    continue;
                keys.emplace_back(pair.first);
            }
            return keys;
        }

        const std::vector<Value> values(bool exclude_internal) const
        {
            std::vector<Value> values{};
            if (exclude_internal)
                values.reserve(_state.size() - _internalSymbols.size());
            else
                values.reserve(_state.size());

            for (const auto& pair : _state) {
                if (exclude_internal && _internalSymbols.contains(pair.first))
                    continue;
                values.emplace_back(pair.second);
            }
            return values;
        }

        void add(Key name, Value val, bool internal)
        {
            add(name, val);
            if (internal)
                _internalSymbols.insert(name);
        }

        void add(Key name, Value val)
        {
            if (contains(name)) {
                std::stringstream ss{};
                ss << "Name '" << name << "' already exists";
                throw std::runtime_error(ss.str());
            }
            _state.emplace(std::move(name), std::move(val));
        }

        Value& get(Key name)
        {
            if (!contains(name)) {
                std::stringstream ss{};
                ss << "Name '" << name << "' does not exist";
                throw std::runtime_error(ss.str());
            }
            return _state.find(name)->second;
        }

        const Value& get(Key name) const
        {
            if (!contains(name)) {
                std::stringstream ss{};
                ss << "Name '" << name << "' does not exist";
                throw std::runtime_error(ss.str());
            }
            return _state.find(name)->second;
        }

        bool contains(Key name) const { return _state.contains(name); }
        bool is_internal(Key name) const { return _internalSymbols.contains(name); }
        const state_t<Key, Value> state() const { return {_state}; }
        state_t<Key, Value>::iterator begin() { return _state.begin(); }
        state_t<Key, Value>::iterator end() { return _state.end(); }
        state_t<Key, Value>::const_iterator begin() const { return _state.begin(); }
        state_t<Key, Value>::const_iterator end() const { return _state.end(); }
    };
}  // namespace stochastic

#endif  // !SYMBOLTABLE_HPP