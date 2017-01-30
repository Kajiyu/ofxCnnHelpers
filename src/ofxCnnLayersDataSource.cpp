//
//  ofxCnnLayersDataSource.cpp
//  ofxCnnHelpers
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#include "ofxCnnLayersDataSource.hpp"

void ofxCnnLayersDataSource::setup(int _layer_num, vector<vector<int>> &layers, ofxCnnLayersDataSource::CnnDataMode _mode) {
    if (this->layersState.size() > 0) this->layersState.clear();
    if (this->densities.size() > 0) this->densities.clear();
    if (this->filters.size() > 0) this->filters.clear();
    if (this->outputs.size() > 0) this->outputs.clear();
    
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
                for (int i = 0; i < this->layer_num; i++) {
                    string filename = "cnnDatas/conv" + ofToString(i+1) + "_filters.json";
                    ofxJSON json;
                    if (json.openLocal(filename)) {
                        vector<vector<vector<float>>> tmp_filters;
                        for (int j = 0; j < this->layersState[i][2]; j++) {
                            vector<vector<float>> tmp_filter;
                            for (int k = 0; k < this->layersState[i][0]; k++) {
                                vector<float> tmp_row;
                                for (int l = 0; l < this->layersState[i][1]; l++) {
                                    float tmp = ofToFloat(json[j][k][l].toStyledString());
                                    tmp_row.push_back(tmp);
                                }
                                tmp_filter.push_back(tmp_row);
                            }
                            tmp_filters.push_back(tmp_filter);
                        }
                        this->filters.push_back(tmp_filters);
                    } else {
                        ofLogError("Cannot open density.json for unexpected reason.");
                        return;
                    }
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
            case CNN_FILTER: {
                if (densities.size() > 0) densities.clear();
                if (outputs.size() > 0) outputs.clear();
                ofxJSON json;
                string filename = "cnnDatas/conv" + ofToString(usingLayerIndex) + "_filters.json";
                int i = usingLayerIndex - 1;
                if (json.openLocal(filename)) {
                    for (int j = 0; j < this->layersState[i][2]; j++) {
                        for (int k = 0; k < this->layersState[i][0]; k++) {
                            for (int l = 0; l < this->layersState[i][1]; l++) {
                                float tmp = ofToFloat(json[j][k][l].toStyledString());
                                filters[i][j][k][l] = tmp;
                            }
                        }
                    }
                }
                break;
            }
            case CNN_OUTPUT: {
                if (densities.size() > 0) densities.clear();
                if (filters.size() > 0) filters.clear();
                break;
            }
            default:
                break;
        }
    } else {
        ofLogError("This instance has not been setupped. You need to execute 'setup()' before this function.");
    }
}


void ofxCnnLayersDataSource::changeMode(ofxCnnLayersDataSource::CnnDataMode _mode) {
    if (this->isSetuped) {
        this->mode = _mode;
    } else {
        ofLogError("This instance has not been setupped. You need to execute 'setup()' before this function.");
    }
}

void ofxCnnLayersDataSource::changeUsingLayerIndex(int index) {
    if (this->isSetuped) {
        this->usingLayerIndex = index;
    } else {
        ofLogError("This instance has not been setupped. You need to execute 'setup()' before this function.");
    }
}

void ofxCnnLayersDataSource::getDensityDatas(vector<vector<float>> * _densities) {
    _densities->clear();
    *_densities = this->densities;
}


void ofxCnnLayersDataSource::getFilterDatas(vector<vector<vector<vector<float>>>> * _filters){
    _filters->clear();
    *_filters = this->filters;
}

void ofxCnnLayersDataSource::getOutputDatas(vector<vector<vector<vector<float>>>> * _outputs){
    _outputs->clear();
    *_outputs = this->outputs;
}
