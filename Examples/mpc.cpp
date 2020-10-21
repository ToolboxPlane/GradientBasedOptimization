#include <tuple>

#include <Symbolic/Operators.hpp>
#include <Symbolic/Constant.hpp>
#include <Symbolic/Functions/Tan.hpp>
#include <utility>

template<grad::sym::Expression X_1, grad::sym::Expression X_2, grad::sym::Expression Psi>
auto predict(X_1 x1, X_2 x2, Psi psi, grad::sym::Variable<double> steer, const grad::sym::Variable<double> &vel) {
    // Assuming dt=1
    auto new_x_1 = x1 + vel * grad::sym::Cos(psi);
    auto new_x_2 = x2 + vel * grad::sym::Sin(psi);
    auto new_psi = psi + vel * grad::sym::Tan(std::move(steer));

    return std::make_tuple(new_x_1, new_x_2, new_psi);
}



int main() {
    grad::sym::Variable<double> x_1{0};
    grad::sym::Variable<double> x_2{0};
    grad::sym::Variable<double> psi{0};




    return 0;
}

