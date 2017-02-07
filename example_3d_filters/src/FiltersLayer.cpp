//
//  FiltersLayer.cpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#include "FiltersLayer.hpp"


void FiltersLayer::setup(ofxCnnHelpers::FilterOutputLayer &_layer, int _intervalFilters){
    this->layer = _layer;
    numFilters = layer.numImages;
    
    for (int i = 0; i < numFilters; i++) {
        BoxelFilter filter;
        filter.setup(layer, i);
        filters.push_back(filter);
    }
    
    heightLayer = layer.heightImage;
    intervalFilters = _intervalFilters;
    widthLayer = layer.widthImage + (numFilters-1)*intervalFilters;
}


void FiltersLayer::update(vector<ofPixels> &pixelsVector){
    for (int i = 0; i < pixelsVector.size(); i++) {
        filters[i].update(pixelsVector[i]);
    }
}


void FiltersLayer::draw(float x, float y, float z){
    ofPushMatrix();
    ofTranslate(x, y, z);
    ofTranslate((-1)*widthLayer/2 + layer.widthImage/2, 0, 0);
    for (int i = 0; i < filters.size(); i++) {
        filters[i].draw(i*intervalFilters, 0, 0);
    }
    ofPopMatrix();
}
