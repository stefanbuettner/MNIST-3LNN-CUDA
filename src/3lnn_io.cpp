/*
 * 3lnn_io.cpp
 *
 *  Created on: 05.07.2017
 *      Author: Stefan
 */
#include "3lnn_io.h"
#include "3lnn.h"
#include <fstream>
#include <yaml-cpp/yaml.h>

using namespace std;

ostream& operator<< (ostream& out, Network const& net) {

	YAML::Emitter netDef;

	netDef << YAML::BeginMap;
	netDef << YAML::Key << "learningRate";
	netDef << YAML::Value << net.learningRate;
	for (Layer* layer : net.layers) {
		switch (layer->layerType) {
			case INPUT:
				netDef << YAML::Key << "INPUT";
				break;
			case OUTPUT:
				netDef << YAML::Key << "OUTPUT";
				break;
			case HIDDEN:
				netDef << YAML::Key << "HIDDEN";
				break;
		}
		netDef << YAML::Value << YAML::BeginMap;
		// Activation function
		netDef << YAML::Key << "activationFunction";
		switch (layer->actFctType) {
		case SIGMOID:
			netDef << YAML::Value << "SIGMOID";
			break;
		case TANH:
			netDef << YAML::Value << "TANH";
			break;
		case NONE:
			netDef << YAML::Value << "NONE";
			break;
		default:
			cerr << "Activation function type not handled, yet." << endl;
		}
		netDef << YAML::Key << "Nodes";
		netDef << YAML::Value;
		netDef << YAML::BeginSeq;
		for (Node* node : layer->nodes) {
			// Sequence of nodes
			// Node as a map
			netDef << YAML::BeginMap;
			netDef << YAML::Key << "bias";
			netDef << YAML::Value << node->bias;
			netDef << YAML::Key << "weights";
			netDef << YAML::Flow << node->weights;
			netDef << YAML::EndMap;
		}
		netDef << YAML::EndSeq;
		netDef << YAML::EndMap;
	}
	netDef << YAML::EndMap;

	return out << netDef.c_str();
}

bool saveNet(string const& path, Network const& net) {
	ofstream fout(path);

	fout << net;

	return true;
}