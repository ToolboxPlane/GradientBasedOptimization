/**
 * @file Add.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_ADD_HPP
#define GRADIENTOPTIMIZATION_ADD_HPP

#include "../Util/EnableOr.hpp"

#include "Expression.hpp"
#include "Grad.hpp"

#include "Variable.hpp"

namespace grad::sym {
    template <Expression Lhs, Expression Rhs>
    class Add {
            static_assert(std::is_same_v<typename Lhs::type, typename Rhs::type>, "Types do not match!");
        public:
            using type = typename Lhs::type;
            static constexpr auto isGrad = IsGrad<Lhs>::val && IsGrad<Rhs>::val;
            using lgrad = util::EnableOrType<isGrad,
                    decltype(std::declval<Lhs>().grad(std::declval<const Variable<type>&>())),
                    void>;
            using rgrad = util::EnableOrType<isGrad,
                    decltype(std::declval<Rhs>().grad(std::declval<const Variable<type>&>())),
                    void>;
            using dtype = util::EnableOrType<isGrad, Add<lgrad, rgrad>, void>;

            Add(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            auto grad(const Variable<type> &d) const -> std::enable_if_t<isGrad, dtype>;
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
    auto Add<Lhs, Rhs>::grad(const Variable<type> &d) const -> std::enable_if_t<isGrad, Add::dtype> {
        return dtype{lhs.grad(d), rhs.grad(d)};
    }

}

#endif //GRADIENTOPTIMIZATION_ADD_HPP
