/**
 * @file Mul.hpp
 * @author paul
 * @date 05.09.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_MUL_HPP
#define GRADIENTOPTIMIZATION_MUL_HPP

#include "Expression.hpp"
#include "Add.hpp"

namespace grad::sym {
    namespace impl {
        template<typename T>
        struct IsMul {
            static constexpr auto val = false;
        };
    }

    template <Expression Lhs, Expression Rhs>
    class Mul {
        public:
            using type = decltype(std::declval<Lhs>().resolve() * std::declval<Rhs>().resolve());

            Mul(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            template <typename mul> requires (impl::IsMul<mul>::val)
            friend auto gradient(const mul &x, const Variable<typename mul::type> &d);

            template <typename mul> requires (impl::IsMul<mul>::val)
            friend auto toString(const mul &x) -> std::string;

            static constexpr auto isConstant() -> bool;
        private:
            Lhs lhs;
            Rhs rhs;
    };

    namespace impl {
        template<Expression lhs, Expression rhs>
        struct IsMul<Mul<lhs, rhs>> {
            static constexpr auto val = true;
        };
    }

    template<Expression Lhs, Expression Rhs>
    Mul<Lhs, Rhs>::Mul(Lhs lhs, Rhs rhs) : lhs{lhs}, rhs{rhs} {}

    template<Expression Lhs, Expression Rhs>
    auto Mul<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() * rhs.resolve();
    }

    template <typename mul> requires (impl::IsMul<mul>::val)
    auto gradient(const mul &x, const Variable<typename mul::type> &d) {
        using lgrad = decltype(gradient(x.lhs, d));
        using rgrad = decltype(gradient(x.rhs, d));
        using lsum = Mul<lgrad, decltype(x.rhs)>;
        using rsum = Mul<rgrad, decltype(x.lhs)>;
        using dtype = Add<lsum, rsum>;

        return dtype{lsum{gradient(x.lhs, d), x.rhs},
                     rsum{gradient(x.rhs, d), x.lhs}};
    }

    template <typename mul> requires (impl::IsMul<mul>::val)
    auto toString(const mul &x) -> std::string {
        return x.lhs.toString() + "*" + x.rhs.toString();
    }

    template<Expression Lhs, Expression Rhs>
    constexpr auto Mul<Lhs, Rhs>::isConstant() -> bool {
        return Lhs::isConstant() and Rhs::isConstant();
    }

}

#endif //GRADIENTOPTIMIZATION_MUL_HPP
