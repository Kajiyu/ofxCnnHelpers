//
//  FiltersLayer.hpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#pragma once
#include "addon_common.h"
#include "const_common.h"
#include "BoxelFilter.hpp"


class FiltersLayer {
public:
    void setup(ofxCnnHelpers::FilterOutputLayer &_layer);
    void update(vector<ofPixels> &pixelsVector);
    void draw(float x, float y, float z);
    
    
protected:
    vector<BoxelFilter> filters;
};
