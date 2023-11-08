#pragma once
#include "activateFunction.h"
#include <vector>
#include <cuchar>
class Network
{
	size_t m_layers;
	std::vector<size_t> m_neurons_size;
	ActivateFunction m_act_func;
	std::vector<Matrix> m_weights;
    std::vector<Vector> m_bias;
	std::vector<Vector> m_neurons;
	std::vector<Vector> m_neurons_error;
public:
	Network(size_t layers, const std::vector<size_t>& neurons_size, ActivateFunction::FunctionType func_type);
	void input(const std::vector<double>& values);
	void forwardFeed();
	size_t prediction();
	void backPropogation(double expect);
    void backPropogation(const Vector& vec);
	void updateWeights(double lr);
    Vector getLastLayer();
};

