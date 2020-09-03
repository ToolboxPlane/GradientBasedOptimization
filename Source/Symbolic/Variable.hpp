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
            using type = T;
            using dtype = Variable<T>;

            explicit Variable(T val);

            auto resolve() const -> T;

            auto grad(const Variable<T> &d) const -> dtype;

            void set(T t);

        private:
            std::shared_ptr<T> val;
    };

    template<typename T>
    Variable<T>::Variable(T val) : val{std::make_shared<T>(std::move(val))}{}

    template<typename T>
    auto Variable<T>::resolve() const -> T {
        return *val;
    }

    template<typename T>
    void Variable<T>::set(T t) {
        *(this->val) = t;
    }

    template<typename T>
    auto Variable<T>::grad(const Variable<T> &d) const -> Variable<T> {
        return Variable<T>(this->val.get() == d.val.get()? 1 : 0);
    }
}

#endif //GRADIENTOPTIMIZATION_VARIABLE_HPP
