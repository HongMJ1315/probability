#include<bits/stdc++.h>
using namespace std;
#include "neuron.h"
#include "layer.h"
#include "neural_network.h"


int main(){
    vector<vector<double>> inputs;
    vector<vector<double>> targets;
    vector<int> topology = { 101,500,250,100,50,11 };
    NeuralNetwork nn(topology);
    nn.learning_rate = 0.1;
    ifstream train("bg.out");
    double tar;
    while(train >> tar){
        vector<double> input, target(11, 0);
        target[int(tar * 10.0)] = 1;
        targets.push_back(target);
        double x;
        for(int i = 0; i <= 100; i++){
            train >> x;
            input.push_back(x);
        }
        inputs.push_back(input);
    }
    int num_epochs = 50;
    for(int epoch = 0; epoch < num_epochs; epoch++){
        for(int i = 0; i < inputs.size(); i++){
            nn.feed_forward(inputs[i]);
            nn.back_propagate(targets[i]);
            nn.update_weights();
        }
    }
    ifstream test("test.out");
    int CNT = 1;
    while(test >> tar){
        vector<double> input;
        double x;
        for(int i = 0; i <= 100; i++){
            test >> x;
            input.push_back(x);
        }
        nn.feed_forward(input);
        Layer res = nn.get_output();
        int ans = 0;
        double ansp = -1;
        for(int i = 0; i <= res.neurons.size(); i++){
            if(res.neurons[i].output > ansp){
                ans = i;
                ansp = res.neurons[i].output;
            }
        }
        double finalp = double(ans) / 10;
        cout << "test " << CNT++ << " : ";
        cout << finalp << endl;
    }
}