//
//  BoxelFilter.hpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#pragma once
#include "addon_common.h"
#include "const_common.h"


class BoxelFilter {
public:
    void setup(ofxCnnHelpers::FilterOutputLayer &_layer, int _filter_id);
    void update(ofPixels &_pixels);
    void draw(float x, float y, float z);
    
    
protected:
    ofPixels pixels;
    int width;
    int height;
    int filter_id;
    string layer_name;
    vector<vector<ofBoxPrimitive>> boxes;
};
