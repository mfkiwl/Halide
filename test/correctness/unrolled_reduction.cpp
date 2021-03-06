#include <stdio.h>
#include <Halide.h>

using namespace Halide;

int main(int argc, char **argv) {
    Var x("x"), y("y"), z("z");

    Image<float> noise(32);
    for (int i = 0; i < 32; i++) {
        noise(i) = (float)rand() / RAND_MAX;
    }

    Func f("f");
    Func g("g");
    RDom r(0, 32);

    g(x, y) = 0.0f;
    g(r.x, y) += noise(r.x);

    f(x, y, z) = g(x, y) + g(x+1, y);

    g.compute_at(f, y);
    f.unroll(z, 2);

    Image<float> im = f.realize(64, 64, 4);

    printf("Success!\n");
    return 0;
}
