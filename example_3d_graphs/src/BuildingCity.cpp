//
//  BuildingCity.cpp
//  example_3d_graphs
//
//  Created by KajiharaYuma on 2017/02/03.
//
//

#include "BuildingCity.hpp"


void BuildingCity::setup(int building_num, ofxCnnHelpers::ActivationLayer &layer) {
    for (int i = 0; i < building_num; i++) {
        Building building;
        building.setup(ofFloatColor(0.16,0.36,0.89, 1.0), 50, layer.values[i]*1000, 50);
        buildings.push_back(building);
    }
    width = 50*building_num + 60;
}


void BuildingCity::update(ofxCnnHelpers::ActivationLayer &layer) {
    for (int i = 0; i < buildings.size(); i++) {
        if (buildings[i].height != layer.values[i]*1000 && !buildings[i].isAnimating) {
            buildings[i].startAnimation(layer.values[i]*1000);
        }
    }
}


void BuildingCity::draw(float _x, float _y, float _z) {
    ofPushMatrix();
    ofTranslate(_x, _y, _z);
    ofSetColor(50, 100);
    ofDrawBox(width/2, 0, 0, width, 5, 200);
    for (int i = 0; i < buildings.size(); i++) {
        buildings[i].draw(30 + 50*i, 0, 0);
    }
    ofPopMatrix();
}
