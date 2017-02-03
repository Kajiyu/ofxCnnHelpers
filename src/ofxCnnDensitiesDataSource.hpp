//
//  ofxCnnDensitiesDataSource.hpp
//  example_3d_curves
//
//  Created by KajiharaYuma on 2017/02/02.
//
//

#pragma once
#include "ofMain.h"
#include "ofxCereal.h"
#include "ofxZmq.h"
#include "ofxJSON.h"


struct DensityLayer {
    string layerName;
    int filtersNum = 0;
    vector<float> density_values;
    
    OFX_CEREAL_DEFINE(CEREAL_NVP(layerName), CEREAL_NVP(filtersNum), CEREAL_NVP(density_values));
};


class DensitiesDomain {
public:
    ofxJSON tmpJson;
    
    void getAsDensityLayers (vector<DensityLayer> * _densityLayers) {
        if (_densityLayers->size() > 0) {
            _densityLayers->clear();
        }
        int layerNums;
        layerNums = ofToInt(tmpJson["layerNum"].toStyledString());
//        cout << layerNums << endl;
        for (int i = 0; i < layerNums; i++) {
            DensityLayer layer;
            layer.layerName = tmpJson["layers"][i]["layerName"].toStyledString();
            int valuesNum = ofToInt(tmpJson["layers"][i]["valuesNum"].toStyledString());
            layer.filtersNum = valuesNum;
            for (int j = 0; j < valuesNum; j++) {
                float tmp_value = ofToFloat(tmpJson["layers"][i]["values"][j].toStyledString());
                layer.density_values.push_back(tmp_value);
//                cout << tmp_value << endl;
            }
            _densityLayers->push_back(layer);
        }
    }
};


class ofxCnnDensitiesDataSource : ofThread {
public:
    void setup(string filename);
    void update();
    vector<DensityLayer> getDensityDatas();
    void start(string port, int waiting_time);
    void stop();
    void threadedFunction();
    void save();
    void debugSave();
    
protected:
    unsigned int zmq_get_count = 0;
    unsigned int save_count = 0;
    int zmq_waiting_time = 500;
    bool isZmqMode;
    bool isSetup = false;
    string jsonFileName;
    vector<DensityLayer> densityLayers;
    ofxZmqSubscriber zmqSubscriber;
    
    
    DensitiesDomain densitiesDomain;
    ofBuffer private_buffer;
};
