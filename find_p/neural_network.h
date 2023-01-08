#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>



class NeuralNetwork{
public:
    std::vector<Layer> layers;  // 层向量
    double learning_rate;  // 学习率
    NeuralNetwork(std::vector<int> topology){
        // 初始化网络结构
        int num_layers = topology.size();
        layers.resize(num_layers);
        for(int i = 0; i < num_layers; i++){
            int num_neurons = topology[i];
            int num_weights_per_neuron = (i == 0) ? num_neurons : topology[i - 1];
            layers[i] = Layer(num_neurons, num_weights_per_neuron);
        }
    };  // 构造函数，初始化网络结构
    void feed_forward(std::vector<double> input){
        // 设置输入层的输出
        for(int i = 0; i < input.size(); i++){
            layers[0].neurons[i].output = input[i];
        }
        // 计算隐藏层和输出层的输出
        for(int i = 1; i < layers.size(); i++){
            Layer &previous_layer = layers[i - 1];
            for(int j = 0; j < layers[i].neurons.size(); j++){
                Neuron &neuron = layers[i].neurons[j];
                // 计算加权和
                double weighted_sum = neuron.bias;
                for(int k = 0; k < previous_layer.neurons.size(); k++){
                    weighted_sum += previous_layer.neurons[k].output * neuron.weights[k];
                }
                // 计算输出
                neuron.output = neuron.activation(weighted_sum);
            }
        }
    };  // 前向传播
    void back_propagate(std::vector<double> target){
        // 计算输出层的误差
        int num_outputs = layers.back().neurons.size();
        for(int i = 0; i < num_outputs; i++){
            Neuron &neuron = layers.back().neurons[i];
            neuron.delta = neuron.activation_derivative(neuron.output) * (target[i] - neuron.output);
        }
        // 计算隐藏层的误差
        for(int i = layers.size() - 2; i > 0; i--){
            Layer &layer = layers[i];
            Layer &next_layer = layers[i + 1];
            for(int j = 0; j < layer.neurons.size(); j++){
                Neuron &neuron = layer.neurons[j];
                neuron.delta = neuron.activation_derivative(neuron.output);
                double error = 0.0;
                for(int k = 0; k < next_layer.neurons.size(); k++){
                    error += next_layer.neurons[k].weights[j] * next_layer.neurons[k].delta;
                }
                neuron.delta *= error;
            }
        }
    };  // 反向传播
    void update_weights(){
        // 更新每个权重
        for(int i = 1; i < layers.size(); i++){
            Layer &layer = layers[i];
            Layer &previous_layer = layers[i - 1];
            for(int j = 0; j < layer.neurons.size(); j++){
                Neuron &neuron = layer.neurons[j];
                for(int k = 0; k < previous_layer.neurons.size(); k++){
                    neuron.weights[k] += learning_rate * neuron.delta * previous_layer.neurons[k].output;
                }
                neuron.bias += learning_rate * neuron.delta;
            }
        }
    };  // 更新权重
    double calculate_error(std::vector<double> target){
        // 计算均方误差
        double error = 0.0;
        int num_outputs = layers.back().neurons.size();
        for(int i = 0; i < num_outputs; i++){
            double diff = target[i] - layers.back().neurons[i].output;
            error += diff * diff;
        }
        return error / num_outputs;
    }
    ;  // 计算误差
    double calculate_accuracy(std::vector<std::vector<double>> inputs, std::vector<std::vector<double>> targets){
        // 计算准确率
        int num_correct = 0;
        int num_samples = inputs.size();
        for(int i = 0; i < num_samples; i++){
            feed_forward(inputs[i]);
            if(layers.back().neurons[0].output > 0.5){
                num_correct += (targets[i][0] > 0.5) ? 1 : 0;
            }
            else{
                num_correct += (targets[i][0] <= 0.5) ? 1 : 0;
            }
        }
        return (double) num_correct / num_samples;
    }
    ;  // 计算准确率

    Layer get_output(){
        return layers.back();
    }
};
