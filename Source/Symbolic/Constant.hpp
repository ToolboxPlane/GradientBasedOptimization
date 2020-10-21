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
    template <typename T>
    class Constant {
        public:
            using type = T;

            Constant(T val);

            auto resolve() const -> T;

            template <typename T_>
            friend auto gradient(const Constant<T_>&, const Variable<T_>&);

        private:
            T val;
    };

    template<typename T>
    Constant<T>::Constant(T val) : val{val} {}

    template<typename T>
    auto Constant<T>::resolve() const -> T {
        return val;
    }

    template<typename T_>
    auto gradient(const Constant<T_>&, const Variable<T_>&) {
        return Constant<T_>{0};
    }



}

#endif //GRADIENTOPTIMIZATION_CONSTANT_HPP
