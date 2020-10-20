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

namespace grad::sym {
    template <typename T, T val>
    class Constant {
        public:
            using type = T;
            using dtype = Constant<T, 0>;

            auto resolve() const -> T;

            template <typename T_, T_ val_>
            friend auto gradient(const Constant<T_, val_>&, const Variable<T_>&);
    };

    template<typename T, T val>
    auto Constant<T, val>::resolve() const -> T {
        return val;
    }

    template<typename T_, T_ val_>
    auto gradient(const Constant<T_, val_>&, const Variable<T_>&) {
        return Constant<T_, 0>();
    }


}

#endif //GRADIENTOPTIMIZATION_CONSTANT_HPP
