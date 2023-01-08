#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>


class Layer{
public:
    std::vector<Neuron> neurons;  // 神經元向量
    Layer(){ neurons.clear(); }
    Layer(int num_neurons, int num_weights_per_neuron){
        // 初始化层中的神經元
        neurons.resize(num_neurons);
        for(int i = 0; i < num_neurons; i++){
            neurons[i] = Neuron(num_weights_per_neuron);
        }
    };  // 构造函数，初始化层中的神經元
};
