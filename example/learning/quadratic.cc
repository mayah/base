#include <iostream>

#include "learning/multi_layer_perceptron.h"

int main()
{
    learning::MultiLayerPerceptron mlp(3, 12, 2);
    auto data = mlp.make_forwading_storage();
    auto error_data = mlp.make_backpropagation_storage();

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
        mlp.train(0, t000, &data, &error_data);
        mlp.train(0, t001, &data, &error_data);
        mlp.train(0, t010, &data, &error_data);
        mlp.train(0, t011, &data, &error_data);
        mlp.train(0, t100, &data, &error_data);
        mlp.train(1, t101, &data, &error_data);
        mlp.train(1, t110, &data, &error_data);
        mlp.train(0, t111, &data, &error_data);
    }

    std::cout << mlp.predict(t000, &data) << std::endl;
    std::cout << mlp.predict(t001, &data) << std::endl;
    std::cout << mlp.predict(t010, &data) << std::endl;
    std::cout << mlp.predict(t011, &data) << std::endl;
    std::cout << mlp.predict(t100, &data) << std::endl;
    std::cout << mlp.predict(t101, &data) << std::endl;
    std::cout << mlp.predict(t110, &data) << std::endl;
    std::cout << mlp.predict(t111, &data) << std::endl;

    return 0;
}
