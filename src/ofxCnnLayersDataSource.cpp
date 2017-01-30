//
//  ofxCnnLayersDataSource.cpp
//  ofxCnnHelpers
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#include "ofxCnnLayersDataSource.hpp"

void ofxCnnLayersDataSource::setup(int _layer_num, vector<vector<int>> &layers, ofxCnnLayersDataSource::CnnDataMode _mode) {
    this->layer_num = _layer_num;
    if (this->layer_num != layers.size()) {
        ofLogError("Value Error :: The number of layers vector is illegal.");
    } else {
        this->layersState = layers;
        this->mode = _mode;
        cout << "***CnnLayersDataSource***" << endl;
        cout << "Layer Num : " << this->layer_num << endl;
        for (int i = 0; i < this->layersState.size(); i++) {
            cout << i << " Layer: ";
            for (int j = 0; j < this->layersState[i].size(); j++) {
                cout << this->layersState[i][j] << " ";
            }
            cout << ";" << endl;
        }
        switch (this->mode) {
            case CNN_DENSITY: {
                ofxJSON json;
                if (json.openLocal("cnnDatas/density.json")) {
                    for(int i = 0; i < this->layer_num; i++) {
                        vector<float> tmp_layer;
                        for (int j = 0; j < this->layersState[i][2]; j++) {
                            string conv_name = "conv" + ofToString(i+1);
                            float tmp_value = ofToFloat(json[conv_name][j].toStyledString());
                            tmp_layer.push_back(tmp_value);
                        }
                        densities.push_back(tmp_layer);
                    }
                } else {
                    ofLogError("Cannot open density.json for unexpected reason.");
                    return;
                }
                cout << "Mode : Density" << endl;
                break;
            }
            case CNN_FILTER: {
                ofxJSON json;
                if (json.openLocal("cnnDatas/filter.json")) {
                } else {
                    ofLogError("Cannot open filter.json for unexpected reason.");
                    return;
                }
                cout << "Mode : Filter" << endl;
                break;
            }
            case CNN_OUTPUT: {
                ofxJSON json;
                if (json.openLocal("cnnDatas/output.json")) {
                    
                } else {
                    ofLogError("Cannot open output.json for unexpected reason.");
                    return;
                }
                cout << "Mode : Output" << endl;
                break;
            }
            default:
                break;
        }
        cout << "Completed Setup." << endl;
        this->isSetuped = true;
    }
}


void ofxCnnLayersDataSource::update() {
    if (this->isSetuped) {
        switch (mode) {
            case CNN_DENSITY:{
                if (filters.size() > 0) filters.clear();
                if (outputs.size() > 0) outputs.clear();
                ofxJSON json;
                if (json.openLocal("cnnDatas/density.json")) {
                    for(int i = 0; i < this->layer_num; i++) {
                        for (int j = 0; j < this->layersState[i][2]; j++) {
                            string conv_name = "conv" + ofToString(i+1);
                            float tmp_value = ofToFloat(json[conv_name][j].toStyledString());
                            densities[i][j] = tmp_value;
                        }
                    }
                } else {
                    ofLogError("Cannot open density.json for unexpected reason.");
                    return;
                }
                break;
            }
            case CNN_FILTER:
                if (densities.size() > 0) densities.clear();
                if (outputs.size() > 0) outputs.clear();
                break;
            case CNN_OUTPUT:
                if (densities.size() > 0) densities.clear();
                if (filters.size() > 0) filters.clear();
                break;
            default:
                break;
        }
    } else {
    }
}


void ofxCnnLayersDataSource::changeMode(ofxCnnLayersDataSource::CnnDataMode _mode) {
    if (this->isSetuped) {
        this->mode = _mode;
    } else {
    }
}



void ofxCnnLayersDataSource::getDensityDatas(vector<vector<float>> * _densities) {
    _densities->clear();
    *_densities = this->densities;
}
