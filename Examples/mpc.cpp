#include <ModelPredictiveController/MPC.hpp>
#include <Symbolic/Operators.hpp>
#include <Optimization/SimpleGradientDescent.hpp>

#include <iostream>

using namespace grad::sym;

constexpr auto HORIZ = 10;

int main() {
    auto predict = [](auto x, auto u, auto) {
        return x + 0.5 * u;
    };

    std::array<double, HORIZ> traj{
        1, 1, 1, 1, 1,
        2, 2, 0, 0, 3
    };

    auto cost = [traj](auto x, auto , auto t) {
        return (x - traj[t]) * (x - traj[t]);
    };

    auto term = [](auto err) {
        return err < 0.0001;
    };

    auto optim = [](auto expr, auto x) {
        grad::opt::simple_gradient_descent::optimizeIterations(expr, x, 0.1, 1);
    };

    auto mpc = grad::mpc::make_mpc<HORIZ, double, double>(predict, cost);

    mpc.getX().set(-3);

    auto err = mpc.update(term, optim);

    auto x = mpc.getX().resolve();

    for (auto c = 0U; c < HORIZ; ++c) {
        auto u = mpc.getU(c).resolve();

        std::cout << "t=" << c << "\tx=" << x << "\tu=" << u << "\terr=" << err << std::endl;

        x = predict(x, u, c);
    }
}

