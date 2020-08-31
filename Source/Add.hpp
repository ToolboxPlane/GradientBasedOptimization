/**
 * @file Add.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_ADD_HPP
#define GRADIENTOPTIMIZATION_ADD_HPP

#include "Expression.hpp"

namespace grad {
    template <Expression Lhs, Expression Rhs>
    class Add {
            static_assert(std::is_same_v<typename Lhs::type, typename Rhs::type>, "Types do not match!");
        public:
            using type = typename Lhs::type;
            Add(Lhs &&lhs, Rhs &&rhs);

            auto resolve() const -> type;
        private:
            Lhs lhs;
            Rhs rhs;
    };

    template<Expression Lhs, Expression Rhs>
    Add<Lhs, Rhs>::Add(Lhs &&lhs, Rhs &&rhs) : lhs{lhs}, rhs{rhs} {}

    template<Expression Lhs, Expression Rhs>
    auto Add<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() + rhs.resolve();
    }
}

#endif //GRADIENTOPTIMIZATION_ADD_HPP
