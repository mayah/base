#ifndef LEARNING_MULTILAYER_PERCEPTRON_H_
#define LEARNING_MULTILAYER_PERCEPTRON_H_

#include <memory>

namespace learning {

// Defines a 3-layer perceptron.
// train() is not thread-safe. Using predict() only is thread-safe.
class MultiLayerPerceptron {
public:
    struct ForwardingIntermediateStorage {
        std::unique_ptr<float[]> o1; // input layer output (= input layer input)
        std::unique_ptr<float[]> i2; // hidden layer input
        std::unique_ptr<float[]> o2; // hidden layer output
        std::unique_ptr<float[]> i3; // output layer input (= output layer output)
    };
    struct BackPropagationIntermediateStorage {
        std::unique_ptr<float[]> e2; // hidden layer error
        std::unique_ptr<float[]> e3; // output layer error
    };

    MultiLayerPerceptron(int in, int hid, int out);
    ~MultiLayerPerceptron();

    ForwardingIntermediateStorage make_forwading_storage() const;
    BackPropagationIntermediateStorage make_backpropagation_storage() const;

    // Returns the label.
    // |x| should have |num_input_| size.
    int predict(const float x[], ForwardingIntermediateStorage* data) const;

    // Train single data.
    // |x| should have |num_input_| size.
    void train(int label,
               const float x[],
               ForwardingIntermediateStorage* data,
               BackPropagationIntermediateStorage* error_data,
               float learning_rate = 0.1,
               float l2_normalization = 0.001);

    bool save_parameter(const char* path) const;
    bool save_parameter_as_c_source(const char* path, const char* prefix) const;
    bool load_parameter(const char* path);

private:
    int hidden_layer_weight_size() const;
    int output_layer_weight_size() const;

    void forward(const float x[], ForwardingIntermediateStorage* storage) const;

    const int num_input_;  // the number of input layer neuron.
    const int num_hidden_; // the number of hidden layer nueron.
    const int num_output_; // the number of output layer nueron.

    std::unique_ptr<float[]> w2_; // hidden layer weight
    std::unique_ptr<float[]> w3_; // output layer weight
};

} // namespace learning

#endif // LEARNING_MULTILAYER_PERCEPTRON_H_
