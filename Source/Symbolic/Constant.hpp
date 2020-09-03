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
            using dtype = Constant<T, 0>;

            auto resolve() const -> T;

            auto grad(const Variable<T>&) const -> dtype;
    };

    template<typename T, T val>
    auto Constant<T, val>::resolve() const -> T {
        return val;
    }

    template<typename T, T val>
    auto Constant<T, val>::grad(const Variable<T>&) const -> dtype {
        return Constant<T, 0>();
    }

}

#endif //GRADIENTOPTIMIZATION_CONSTANT_HPP