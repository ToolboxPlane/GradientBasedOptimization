#include <ModelPredictiveController/MPC.hpp>
#include <Symbolic/Operators.hpp>
#include <Optimization/SimpleGradientDescent.hpp>

#include <iostream>

using namespace grad::sym;

constexpr auto HORIZ = 10;

int main() {
    auto predict = [](auto x, auto u, auto) {
        return x + u;
    };

    std::array<double, HORIZ> traj{
        1, 1, 1, 1, 1,
        2, 2, 0, 0, 3
    };

    auto cost = [traj](auto x, auto u, auto t) {
        return (x - traj[t]) * (x - traj[t]) + u*u*0.01;
    };

    auto term = [](auto err) {
        return err < 1;
    };

    auto optim = [](auto expr, auto x) {
        grad::opt::simple_gradient_descent::optimizeIterations(expr, x, 0.1, 1);
    };

    Variable<double> x{-5};

    auto mpc = grad::mpc::make_mpc<HORIZ, double>(predict, cost, x);

    auto err = mpc.update(term, optim);

    for (auto c = 0U; c < HORIZ; ++c) {
        auto u = mpc.get(c).resolve();

        std::cout << "t=" << c << "\tx=" << x.resolve() << "\tu=" << u << "\terr=" << err << std::endl;

        x.set(predict(x.resolve(), u, 0));
    }
}

