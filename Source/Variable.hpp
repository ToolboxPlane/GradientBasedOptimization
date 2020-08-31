/**
 * @file Variable.hpp
 * @author paul
 * @date 28.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_VARIABLE_HPP
#define GRADIENTOPTIMIZATION_VARIABLE_HPP

#include "Expression.hpp"

namespace grad {
    template <typename T>
    class Variable {
        public:
            explicit Variable(T val);

            auto resolve() const -> T;

            template<T _initialVal>
            auto grad(const Variable<T, _initialVal> &d) const -> Variable<T, 1>;

            void set(T t);

        private:
            T val;
    };

    template<typename T>
    Variable<T>::Variable(T val) : val{val}{}

    template<typename T>
    auto Variable<T>::resolve() const -> T {
        return val;
    }

    template<typename T>
    void Variable<T>::set(T t) {
        this->val = t;
    }
}

#endif //GRADIENTOPTIMIZATION_VARIABLE_HPP
