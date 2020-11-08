/**
 * @file Div.hpp
 * @author paul
 * @date 21.10.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_DIV_HPP
#define GRADIENTOPTIMIZATION_DIV_HPP

#include "Mul.hpp"
#include "Add.hpp"
#include "Constant.hpp"

namespace grad::sym {
    namespace impl {
        template<typename T>
        struct IsDiv {
            static constexpr auto val = false;
        };
    }

    template <Expression Lhs, Expression Rhs>
    class Div {
        public:
            static_assert(std::is_same_v<typename Lhs::type, typename Rhs::type>, "Types do not match!");
        public:
            using type = typename Lhs::type;

            Div(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            template <typename div> requires (impl::IsDiv<div>::val)
            friend auto gradient(const div &x, const Variable<typename div::type> &d);

            auto toString() const -> std::string {
                return "(" + lhs.toString() + "+" + rhs.toString() + ")";
            }
        private:
            Lhs lhs;
            Rhs rhs;
    };

    namespace impl {
        template<Expression lhs, Expression rhs>
        struct IsDiv<Div<lhs, rhs>> {
            static constexpr auto val = true;
        };
    }

    template<Expression Lhs, Expression Rhs>
    Div<Lhs, Rhs>::Div(Lhs lhs, Rhs rhs) : lhs{lhs}, rhs{rhs} {}

    template<Expression Lhs, Expression Rhs>
    auto Div<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() / rhs.resolve();
    }

    template <typename div> requires (impl::IsDiv<div>::val)
    auto gradient(const div &x, const Variable<typename div::type> &d) {
        auto neg = Constant<typename div::type>{-1};
        return Div{
                Add{Mul{gradient(x.lhs, d), x.rhs}, Mul{Mul{x.lhs, gradient(x.rhs, d)}, neg}} ,
                    Mul{x.rhs, x.rhs}
            };
    }
}

#endif //GRADIENTOPTIMIZATION_DIV_HPP