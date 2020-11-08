#include <Symbolic/Operators.hpp>
#include <iostream>

using namespace grad::sym;

template<grad::sym::Expression X>
auto predict(X x, const grad::sym::Variable<double> &u) {
    // Assuming dt=1
    grad::sym::Constant<double> T{0.5};
    grad::sym::Constant<double> mu{2};
    return x + (mu * u - x) / T;
}

template<grad::sym::Expression X, grad::sym::Expression Setpoint>
auto costFunction(X x, Setpoint setpoint) {
    auto error = (x - setpoint) * (x - setpoint);
    return error; // Additional weighting possible for final time step
}

template<grad::sym::Expression X, grad::sym::Expression Setpoint, grad::sym::Expression Input,
        grad::sym::Expression... Inputs>
auto costFunction(X x, Setpoint setpoint, Input input, Inputs... inputs) {
    auto error = (x - setpoint) * (x - setpoint);
    return error + costFunction(predict(x, input), setpoint, inputs...);
}

int main() {
    grad::sym::Constant<double> x{0};

    grad::sym::Variable<double> u0{1};
    grad::sym::Variable<double> u1{1};
    grad::sym::Variable<double> u2{1};

    grad::sym::Constant<double> setpoint{1};

    auto loss = costFunction(predict(x, u0), setpoint, u1, u2);

    auto diff0 = gradient(loss, u0);
    auto diff1 = gradient(loss, u1);
    auto diff2 = gradient(loss, u2);

    constexpr auto nu = 0.01;

    auto c = 0U;

    while (loss.resolve() > 0.001) {
        auto update0 = diff0.resolve() * nu;
        auto update1 = diff1.resolve() * nu;
        auto update2 = diff2.resolve() * nu;
        u0.set(u0.resolve() - update0);
        u1.set(u1.resolve() - update1);
        u2.set(u2.resolve() - update2);

        auto x1 = predict(x, u0);
        auto x2 = predict(x1, u1);
        auto x3 = predict(x2, u2);

        std::cout << c << ":\tLoss:" << loss.resolve() <<
                  "\tInputs{" << u0.resolve() << ", " << u1.resolve() << ", " << u2.resolve() << "} -> " <<
                  "States{" << x1.resolve() << ", " << x2.resolve() << ", " << x3.resolve() << "}\t" <<
                  "Updates{" << update0 << ", " << update1 << ", " << update2 << "}" << std::endl;
        c += 1;
    }

    std::cout << "{" << u0.resolve() << ", " << u1.resolve() << ", " << u2.resolve() << "}";

    return 0;
}

