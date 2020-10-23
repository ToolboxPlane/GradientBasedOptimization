#include <Symbolic/Operators.hpp>
#include <iostream>

using namespace grad::sym;

template<grad::sym::Expression X>
auto predict(X x, const grad::sym::Variable<double> &u) {
    // Assuming dt=1
    grad::sym::Constant<double> T{0.5};
    return x + (u - x) / T;
}

template<grad::sym::Expression X, grad::sym::Expression Setpoint, grad::sym::Expression Input,
        grad::sym::Expression... Inputs>
auto costFunction(X x, Setpoint setpoint, Input input, Inputs... inputs) {
    auto error = (x - setpoint) * (x - setpoint);
    if constexpr (sizeof...(inputs) == 0) {
        return error; // additional weighting possible
    } else {
        return error + costFunction(predict(x, input), setpoint, inputs...);
    }
}

int main() {
    grad::sym::Variable<double> x{0};

    grad::sym::Variable<double> u0{1};
    grad::sym::Variable<double> u1{1};
    grad::sym::Variable<double> u2{1};

    grad::sym::Constant<double> setpoint{1};

    auto loss = costFunction(predict(x, u0), setpoint, u1, u2);

    auto diff0 = gradient(loss, u0);
    auto diff1 = gradient(loss, u1);
    auto diff2 = gradient(loss, u2);

    constexpr auto nu = 0.1;

    auto c = 0U;

    while (loss.resolve() > 0.01) {
        u0.set(u0.resolve() - diff0.resolve() * nu);
        u1.set(u1.resolve() - diff1.resolve() * nu);
        u1.set(u2.resolve() - diff2.resolve() * nu);
        std::cout << c << ":\t" << loss.resolve() << std::endl;
        c += 1;
    }

    std::cout << "{" << u0.resolve() << ", " << u1.resolve() << ", " << u2.resolve() << "}";

    return 0;
}

