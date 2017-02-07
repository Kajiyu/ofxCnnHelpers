//
//  FilterImageManager.hpp
//  example_2d_images
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#pragma once

#include "Constants.h"
#include "ofxCereal.h"
#include "ofxZmq.h"
#include "ofxJSON.h"


OFX_CNN_HELPERS_BEGIN_NAMESPACE

struct FilterOutputLayer {
    string name;
    int numImages {0};
    int widthImage;
    int heightImage;
    int widthFilter;
    int heightFilter;
    vector<string> imagePaths;
    
    /* not serializing data*/
    
    OFX_CEREAL_DEFINE(CEREAL_NVP(name), CEREAL_NVP(numImages), CEREAL_NVP(widthImage), CEREAL_NVP(heightImage), CEREAL_NVP(widthFilter), CEREAL_NVP(heightFilter), CEREAL_NVP(imagePaths));
};

#pragma mark --

class FilterImageManager : ofThread {

public:
    void setup(string filename);
    void start(string port);
    void stop();
    void threadedFunction();
    void save();
    void debugSave();
    int getLayersNum();
    vector<FilterOutputLayer> get();
    vector<vector<ofPixels>> getAllPixels();
    vector<ofPixels> getPixelsAtIndexLayer(int index); /// index 1-numOfLayers
    FilterOutputLayer getLayerAtIndex(int index); /// index 1-numOfLayers
    
protected:
    vector<FilterOutputLayer> layers;
    vector<FilterOutputLayer> layers_buffer;
    vector<vector<ofPixels>> pixelsVectors;
    ofxZmqSubscriber zmqSubscriber;
};


OFX_CNN_HELPERS_END_NAMESPACE
