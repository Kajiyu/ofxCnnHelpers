//
//  InputImageManager.hpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/07.
//
//

#pragma once

#include "Constants.h"
#include "ofxCereal.h"
#include "ofxZmq.h"
#include "ofxJSON.h"
#include "ofMain.h"


OFX_CNN_HELPERS_BEGIN_NAMESPACE

class InputImageManager : ofThread {
public:
    void start(string port, int w, int h);
    void stop();
    void threadedFunction();
    void save();
    void draw(int x, int y, int z, int w, int h);
    
    ofImage image;
    ofxZmqSubscriber zmqSubscriber;
};

OFX_CNN_HELPERS_END_NAMESPACE
