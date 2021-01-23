/**
 * @file Add.hpp
 * @author paul
 * @date 25.08.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_ADD_HPP
#define GRADIENTOPTIMIZATION_ADD_HPP

#include "Expression.hpp"

#include "Variable.hpp"
#include "Sub.hpp"


namespace grad::sym {
    namespace impl {
        template<typename T>
        struct IsAdd {
            static constexpr auto val = false;
        };
    }

    template <Expression Lhs, Expression Rhs>
    class Add {
        public:
            using type = decltype(std::declval<Lhs>().resolve() + std::declval<Rhs>().resolve());

            Add(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            template <typename add> requires (impl::IsAdd<add>::val)
            friend auto gradient(const add &x, const Variable<typename add::type> &d);

            template <typename add> requires(impl::IsAdd<add>::val)
            friend auto toString(const add &x) -> std::string;
        private:
            Lhs lhs;
            Rhs rhs;
    };

    namespace impl {
        template<Expression lhs, Expression rhs>
        struct IsAdd<Add<lhs, rhs>> {
            static constexpr auto val = true;
        };
    }

    template<Expression Lhs, Expression Rhs>
    Add<Lhs, Rhs>::Add(Lhs lhs, Rhs rhs) : lhs{lhs}, rhs{rhs} {}

    template<Expression Lhs, Expression Rhs>
    auto Add<Lhs, Rhs>::resolve() const -> type {
        return lhs.resolve() + rhs.resolve();
    }

    template<typename add> requires (impl::IsAdd<add>::val)
    auto gradient(const add &x, const Variable<typename add::type> &d) {
        using ldiff = decltype(gradient(x.lhs, d));
        using rdiff = decltype(gradient(x.rhs, d));
        using dtype = Add<ldiff, rdiff>;

        return dtype{gradient(x.lhs, d), gradient(x.rhs, d)};
    }

    template<typename add> requires (impl::IsAdd<add>::val)
    auto toString(const add &x) {
        return "(" + x.toString() + "+" + x.toString() + ")";
    }

}

#endif //GRADIENTOPTIMIZATION_ADD_HPP
