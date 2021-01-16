#include <ModelPredictiveController/MPC.hpp>
#include <Optimization/Momentum.hpp>

#include <iostream>

constexpr auto HORIZ = 5;

int main() {
    auto predict = [](auto x, auto u, auto) {
        return x * 2.0 - u;
    };

    std::array<double, HORIZ> trajectory{
        1, 1, 5, 1, 1,
    };

    auto cost = [trajectory](auto x, auto , auto t) {
        return (x - trajectory[t]) * (x - trajectory[t]);
    };

    auto term = [](auto err) {
        return err < 0.1;
    };

    auto mpc = grad::mpc::make_mpc<HORIZ, double, double>(predict, cost, grad::opt::make_momentum, 0.001, 0.1);

    mpc.getX().set(-3);

    mpc.optimize(term);

    auto x = mpc.getX().resolve();

    for (auto c = 0U; c < HORIZ; ++c) {
        auto u = mpc.getU(c).resolve();

        std::cout << "t=" << c << "\tx=" << x << "\tu=" << u << std::endl;

        x = predict(x, u, c);
    }
}

