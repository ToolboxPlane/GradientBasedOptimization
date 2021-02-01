/**
 * @file Div.hpp
 * @author paul
 * @date 21.10.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_DIV_HPP
#define GRADIENTOPTIMIZATION_DIV_HPP

#include "Add.hpp"
#include "Constant.hpp"
#include "Mul.hpp"

namespace grad::sym {
    namespace impl {
        template<typename T>
        struct IsDiv {
            static constexpr auto val = false;
        };
    } // namespace impl

    template<Expression Lhs, Expression Rhs>
    class Div {
      public:
        using type = decltype(std::declval<Lhs>().resolve() / std::declval<Rhs>().resolve());

        Div(Lhs lhs, Rhs rhs);

        auto resolve() const -> type;

        template<typename div>
        requires(impl::IsDiv<div>::val) friend auto gradient(const div &x, const Variable<typename div::type> &d);

        template<typename div>
        requires(impl::IsDiv<div>::val) friend auto toString(const div &x) -> std::string;

        static constexpr auto isConstant() -> bool;

      private:
        Lhs lhs;
        Rhs rhs;
    };

    namespace impl {
        template<Expression lhs, Expression rhs>
        struct IsDiv<Div<lhs, rhs>> {
            static constexpr auto val = true;
        };
    } // namespace impl

    template<Expression Lhs, Expression Rhs>
    Div<Lhs, Rhs>::Div(Lhs lhs, Rhs rhs) : lhs{lhs}, rhs{rhs} {
    }

    template<Expression Lhs, Expression Rhs>
    auto Div<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() / rhs.resolve();
    }

    template<typename div>
    requires(impl::IsDiv<div>::val) auto gradient(const div &x, const Variable<typename div::type> &d) {
        auto neg = Constant<typename div::type>{-1};
        return Div{Add{Mul{gradient(x.lhs, d), x.rhs}, Mul{Mul{x.lhs, gradient(x.rhs, d)}, neg}}, Mul{x.rhs, x.rhs}};
    }

    template<typename div>
    requires(impl::IsDiv<div>::val) auto toString(const div &x) -> std::string {
        return "(" + x.lhs.toString() + "/" + x.rhs.toString() + ")";
    }

    template<Expression Lhs, Expression Rhs>
    constexpr auto Div<Lhs, Rhs>::isConstant() -> bool {
        return Lhs::isConstant() and Rhs::isConstant();
    }
} // namespace grad::sym

#endif // GRADIENTOPTIMIZATION_DIV_HPP
