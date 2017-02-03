//
//  DensitiesDataSource.h
//
//  Created by KajiharaYuma on 2017/02/02.
//
//

#pragma once

#include "Constants.h"
#include "ofxCereal.h"
#include "ofxZmq.h"
#include "ofxJSON.h"

OFX_CNN_HELPERS_BEGIN_NAMESPACE

struct ActivationLayer {
    string name;
    int numFilters {0};
    vector<float> values;
    
    OFX_CEREAL_DEFINE(CEREAL_NVP(name), CEREAL_NVP(numFilters), CEREAL_NVP(values));
};

#pragma mark --

class ActivationLayerManager : ofThread {

public:
    void setup(string filename);
    void start(string port);
    void stop();
    void threadedFunction();
    void save();
    void debugSave();
    int getLayersNum();
    
    vector<ActivationLayer> get();
    
protected:
    vector<ActivationLayer> layers;
    vector<ActivationLayer> layers_buffer;
    ofxZmqSubscriber zmqSubscriber;
    
};

OFX_CNN_HELPERS_END_NAMESPACE
