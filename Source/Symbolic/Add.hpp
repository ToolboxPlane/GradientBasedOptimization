/**
 * @file Add.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_ADD_HPP
#define GRADIENTOPTIMIZATION_ADD_HPP

#include "Expression.hpp"
#include "Variable.hpp"

namespace grad {
    template <Expression Lhs, Expression Rhs>
    class Add {
            static_assert(std::is_same_v<typename Lhs::type, typename Rhs::type>, "Types do not match!");
        public:
            using type = typename Lhs::type;
            using lgrad = decltype(std::declval<Lhs>().grad(std::declval<const Variable<type>&>()));
            using rgrad = decltype(std::declval<Rhs>().grad(std::declval<const Variable<type>&>()));
            using dtype =Add<lgrad, rgrad>;

            Add(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            auto grad(const Variable<type> &d) const -> dtype;
        private:
            Lhs lhs;
            Rhs rhs;
    };

    template<Expression Lhs, Expression Rhs>
    Add<Lhs, Rhs>::Add(Lhs lhs, Rhs rhs) : lhs{lhs}, rhs{rhs} {}

    template<Expression Lhs, Expression Rhs>
    auto Add<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() + rhs.resolve();
    }

    template<Expression Lhs, Expression Rhs>
    auto Add<Lhs, Rhs>::grad(const Variable<type> &d) const -> Add::dtype {
        return dtype{lhs.grad(d), rhs.grad(d)};
    }

}

#endif //GRADIENTOPTIMIZATION_ADD_HPP
