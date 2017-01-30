//
//  NetworkBar.hpp
//  example_3d_curves
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#pragma once
#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"

class NetworkBar {
public:
    void setup();
    void update(vector<vector<float>> & paramators, int conv_index);
    void draw(float x, float y, float z, ofColor mainColor);
    
    vector<float> pointValues;
    vector<ofVec3f> pointsPos;
    vector<bool> animated;
    float animStartTime[64];
    float valueBuffers[64];
    bool isInitialized = false;
    
protected:
    void onComplete(float* arg);
};
