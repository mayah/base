#include "learning/multi_layer_perceptron.h"

#include <gtest/gtest.h>

TEST(MultiLayerPerceptronTest, xor_test)
{
    const float zero_zero[2] = { 0, 0 };
    const float zero_one[2]  = { 0, 1 };
    const float one_zero[2]  = { 1, 0 };
    const float one_one[2]   = { 1, 1 };

    learning::MultiLayerPerceptron mlp(2, 4, 2);
    auto data = mlp.make_forwading_storage();
    auto error_data = mlp.make_backpropagation_storage();

    for (int i = 0; i < 100000; ++i) {
        mlp.train(0, zero_zero, &data, &error_data);
        mlp.train(1, zero_one, &data, &error_data);
        mlp.train(1, one_zero, &data, &error_data);
        mlp.train(0, one_one, &data, &error_data);
    }

    EXPECT_EQ(0, mlp.predict(zero_zero, &data));
    EXPECT_EQ(1, mlp.predict(zero_one, &data));
    EXPECT_EQ(1, mlp.predict(one_zero, &data));
    EXPECT_EQ(0, mlp.predict(one_one, &data));
}
