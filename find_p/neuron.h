#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

class Neuron{
public:
    std::vector<double> weights;  // 权重向量
    double bias;  // 偏置项
    double output;  // 输出
    double delta;  // 误差
    Neuron(int num_weights){
        // 初始化权重和偏置项
        weights.resize(num_weights);
        for(int i = 0; i < num_weights; i++){
            weights[i] = 2.0 * rand() / RAND_MAX - 1.0;  // 随机初始化
        }
        bias = 2.0 * rand() / RAND_MAX - 1.0;
    };  // 构造函数，初始化权重
    Neuron(){ weights.clear(); }
    double activation(double x){
        // 使用 sigmoid 函数作为激活函数
        return 1.0 / (1.0 + exp(-x));
    };  // 激活函数
    double activation_derivative(double x){
        // 计算 sigmoid 函数的导数
        return x * (1.0 - x);
    };  // 激活函数的导数
};
