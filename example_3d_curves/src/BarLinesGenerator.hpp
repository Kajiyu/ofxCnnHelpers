//
//  BarLinesGenerator.hpp
//  example_3d_curves
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#pragma once
#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"

#include "NetworkBar.hpp"

class BarLinesGenerator {
public:
    void setup();
    void draw(NetworkBar *bars, vector<ofVec3f> layersPos);
    
    
protected:
    ofPath lines[4];
};
