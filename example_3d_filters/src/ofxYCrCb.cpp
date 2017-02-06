//
//  ofxYCrCb.cpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#include "ofxYCrCb.hpp"

ofxYCrCb::ofxYCrCb (int _y, int _cr, int _cb) {
    y = _y;
    cr = _cr;
    cb = _cb;
}


ofColor ofxYCrCb::toRgb() {
    ofColor color;
    int r = y + 1.40200*cr;
    int g = y - 0.34414*cb - 0.71414*cr;
    int b = y + 1.77200*cb;
    color.set(r, g, b);
    return color;
}


void ofxYCrCb::fromRgb(ofColor &color) {
    this->y = 0.29900*color.r + 0.58700*color.g + 0.11400*color.b;
    this->cr = -0.16874*color.r - 0.33126*color.g + 0.50000*color.b;
    this->cb = 0.50000*color.r - 0.41869*color.g - 0.081*color.b;
}
