//
//  ofxCnnZmq.hpp
//  cnnHelpersTest1
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#pragma once
#include "ofMain.h"
#include "ofxZmq.h"
#include "ofxJSON.h"

// MARK :: This class needs "ofxZmq".

class ofxCnnZmq : public ofThread{
public:
    void start(string port);
    void stop();
    void threadedFunction();
    
protected:
    ofxZmqRequest requestClient;
    ofxJSON json;
};
