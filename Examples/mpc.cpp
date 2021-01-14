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

    auto cost = [traj](auto x, auto , auto t) {
        return (x - traj[t]) * (x - traj[t]);
    };

    auto term = [](auto err) {
        return err < 0.0001;
    };

    auto mpc = grad::mpc::make_mpc<HORIZ, double, double>(predict, cost);

    mpc.getX().set(-3);

    using opt = grad::opt::SimpleGradientDescent<decltype(mpc)::E, double, double>;

    mpc.update<decltype(term), opt, double>(term, 0.01);

    auto x = mpc.getX().resolve();

    for (auto c = 0U; c < HORIZ; ++c) {
        auto u = mpc.getU(c).resolve();

        std::cout << "t=" << c << "\tx=" << x << "\tu=" << u << std::endl;

        x = predict(x, u, c);
    }
}

