/**
 * @file Variable.hpp
 * @author paul
 * @date 28.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_VARIABLE_HPP
#define GRADIENTOPTIMIZATION_VARIABLE_HPP

#include <memory>

#include "Expression.hpp"

namespace grad::sym {
    template <typename T>
    class Variable {
        public:
            using type = T;

            explicit Variable(T val);

            auto resolve() const -> T;

            void set(T t);

            template <typename T_>
            friend auto gradient(const Variable<T_> &x, const Variable<T_> &d);

            auto toString() const -> std::string {
                return "{" + std::to_string(*val) + "}";
            }
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

    template<typename T_>
    auto gradient(const Variable<T_> &x, const Variable<T_> &d) {
        return Variable<T_>(x.val.get() == d.val.get()? 1 : 0);
    }
}

#endif //GRADIENTOPTIMIZATION_VARIABLE_HPP
