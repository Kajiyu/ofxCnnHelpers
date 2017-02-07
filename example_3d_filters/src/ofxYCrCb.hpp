//
//  ofxYCrCb.hpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#pragma once
#include "const_common.h"
#include "addon_common.h"

class ofxYCrCb {
public:
    ofxYCrCb(int _y, int _cr, int _cb);
    ofColor toRgb();
    void fromRgb(ofColor &color);
    
protected:
    int y;
    int cr;
    int cb;
};
