//
//  Building.hpp
//  example_3d_graphs
//
//  Created by KajiharaYuma on 2017/02/03.
//
//

#pragma once
#include "addon_common.h"
#include "const_common.h"

class Building {
public:
    void setup(ofFloatColor _color, float _width, float _height, float _depth);
    void startAnimation(float endHeight);
    void onComplete(float *arg);
    void draw(float _x, float _y, float _z);
    
    float height;
    float width;
    float depth;
    bool isAnimating = false;
    ofFloatColor color;
    ofBoxPrimitive box;
    float animStarttime;
    float endHeight;
};
