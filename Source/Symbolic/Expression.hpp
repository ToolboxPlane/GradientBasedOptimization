/**
 * @file Expression.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_EXPRESSION_HPP
#define GRADIENTOPTIMIZATION_EXPRESSION_HPP

namespace grad {
    template<typename T>
    concept Expression = requires(const T t) {
        typename T::type;
        {t.resolve()} -> std::same_as<typename T::type>;
    };
}

#endif //GRADIENTOPTIMIZATION_EXPRESSION_HPP
