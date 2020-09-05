/**
 * @file enable_or.hpp
 * @author paul
 * @date 05.09.20
 * Description here TODO
 */
#ifndef GRADIENTOPTIMIZATION_ENABLE_OR_HPP
#define GRADIENTOPTIMIZATION_ENABLE_OR_HPP

namespace grad::util {
    template <bool cond, typename TrueType, typename FalseType>
    struct EnableOr {
        using type = FalseType;
    };

    template <typename TrueType, typename FalseType>
    struct EnableOr<true, TrueType, FalseType> {
        using type = TrueType;
    };

    template <bool cond, typename TrueType, typename FalseType>
    using EnableOrType = typename EnableOr<cond, TrueType, FalseType>::type;
}

#endif //GRADIENTOPTIMIZATION_ENABLE_OR_HPP
