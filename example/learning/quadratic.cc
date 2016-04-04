#include <iostream>

#include "learning/multi_layer_perceptron.h"

int main()
{
    learning::MultiLayerPerceptron mlp(3, 12, 2);

    const float t000[] = { 0, 0, 0 };
    const float t001[] = { 0, 0, 1 };
    const float t010[] = { 0, 1, 0 };
    const float t011[] = { 0, 1, 1 };
    const float t100[] = { 1, 0, 0 };
    const float t101[] = { 1, 0, 1 };
    const float t110[] = { 1, 1, 0 };
    const float t111[] = { 1, 1, 1 };

    // training
    for (int i = 0; i < 1000; ++i) {
        mlp.train(0, t000);
        mlp.train(0, t001);
        mlp.train(0, t010);
        mlp.train(0, t011);
        mlp.train(0, t100);
        mlp.train(1, t101);
        mlp.train(1, t110);
        mlp.train(0, t111);
    }

    std::cout << mlp.predict(t000) << std::endl;
    std::cout << mlp.predict(t001) << std::endl;
    std::cout << mlp.predict(t010) << std::endl;
    std::cout << mlp.predict(t011) << std::endl;
    std::cout << mlp.predict(t100) << std::endl;
    std::cout << mlp.predict(t101) << std::endl;
    std::cout << mlp.predict(t110) << std::endl;
    std::cout << mlp.predict(t111) << std::endl;

    return 0;
}
