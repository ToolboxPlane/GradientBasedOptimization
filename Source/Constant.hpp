/**
 * @file Constant.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_CONSTANT_HPP
#define GRADIENTOPTIMIZATION_CONSTANT_HPP

#include "Expression.hpp"
#include "Variable.hpp"

namespace grad {
    template <typename T, T val>
    class Constant {
        public:
            using type = T;

            auto resolve() const -> T;

            template<T initialVal>
            auto grad(const Variable<T, initialVal> &d) const -> Constant<T, 0>;
    };

    template<typename T, T val>
    auto Constant<T, val>::resolve() const -> T {
        return val;
    }

    template<typename T, T val>
    template<T initialVal>
    auto Constant<T, val>::grad(const Variable<T, initialVal> &d) const -> Constant<T, 0> {
        return Constant<T, 0>();
    }

}

#endif //GRADIENTOPTIMIZATION_CONSTANT_HPP
