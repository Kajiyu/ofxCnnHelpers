//
//  BuildingCity.hpp
//  example_3d_graphs
//
//  Created by KajiharaYuma on 2017/02/03.
//
//

#pragma once

#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"
#include "Building.hpp"

class BuildingCity {
public:
    void setup(int building_num, ofxCnnHelpers::ActivationLayer &layer);
    void update(ofxCnnHelpers::ActivationLayer &layer);
    void draw(float _x, float _y, float _z);
    
    vector<Building> buildings;
    float width;
};
