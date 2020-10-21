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

namespace grad::sym {
    namespace impl {
        template<typename T>
        struct IsAdd {
            static constexpr auto val = false;
        };
    }

    template <Expression Lhs, Expression Rhs>
    class Add {
            static_assert(std::is_same_v<typename Lhs::type, typename Rhs::type>, "Types do not match!");
        public:
            using type = typename Lhs::type;

            Add(Lhs lhs, Rhs rhs);

            auto resolve() const -> type;

            template <typename add> requires (impl::IsAdd<add>::val)
            friend auto gradient(const add &x, const Variable<typename add::type> &d);
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
        using rdiff = decltype(gradient(x.lhs, d));
        using dtype = Add<ldiff, rdiff>;

        return dtype{gradient(x.lhs, d), gradient(x.rhs, d)};
    }
}

#endif //GRADIENTOPTIMIZATION_ADD_HPP
