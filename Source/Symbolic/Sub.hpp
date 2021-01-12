/**
 * @file Sub.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_SUB_HPP
#define GRADIENTOPTIMIZATION_SUB_HPP

#include "Expression.hpp"

#include "Variable.hpp"


namespace grad::sym {
    namespace impl {
        template<typename T>
        struct IsSub {
            static constexpr auto val = false;
        };
    }

    template <Expression Lhs, Expression Rhs>
    class Sub {
        public:
            using type = decltype(std::declval<Lhs>().resolve() - std::declval<Rhs>().resolve());

            Sub(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            template <typename sub> requires (impl::IsSub<sub>::val)
            friend auto gradient(const sub &x, const Variable<typename sub::type> &d);

            auto toString() const -> std::string {
                return "(" + lhs.toString() + "-" + rhs.toString() + ")";
            }
        private:
            Lhs lhs;
            Rhs rhs;
    };

    namespace impl {
        template<Expression lhs, Expression rhs>
        struct IsSub<Sub<lhs, rhs>> {
            static constexpr auto val = true;
        };
    }

    template<Expression Lhs, Expression Rhs>
    Sub<Lhs, Rhs>::Sub(Lhs lhs, Rhs rhs) : lhs{lhs}, rhs{rhs} {}

    template<Expression Lhs, Expression Rhs>
    auto Sub<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() - rhs.resolve();
    }

    template<typename sub> requires (impl::IsSub<sub>::val)
    auto gradient(const sub &x, const Variable<typename sub::type> &d) {
        using ldiff = decltype(gradient(x.lhs, d));
        using rdiff = decltype(gradient(x.rhs, d));
        using dtype = Sub<ldiff, rdiff>;

        return dtype{gradient(x.lhs, d), gradient(x.rhs, d)};
    }
}

#endif //GRADIENTOPTIMIZATION_SUB_HPP
