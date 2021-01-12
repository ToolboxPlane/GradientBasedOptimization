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

    auto error = [](auto x, auto ) {
        Constant<double> target{1};
        return (x - target) * (x - target);
    };

    auto term = [](auto err) {
        return err < 0.001;
    };

    auto optim = [](auto expr, auto x) {
        grad::opt::simple_gradient_descent::optimizeIterations(expr, x, 0.1, 1);
    };

    Variable<double> x{-5};

    auto mpc = grad::mpc::make_mpc<HORIZ>(predict, error, x);

    auto u = mpc.get(0);

    for (auto c = 0U; c < HORIZ; ++c) {
        auto err = mpc.update(term, optim);
        std::cout << "t=" << c << "\tx=" << x.resolve() << "\tu=" << u.resolve() << "\terr=" << err << std::endl;

        x.set(predict(x.resolve(), u.resolve(), 0));
    }
}

