//
//  BoxelFilter.cpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#include "BoxelFilter.hpp"


void BoxelFilter::setup(ofxCnnHelpers::FilterOutputLayer &_layer, int _filter_id) {
    width = _layer.widthImage;
    height = _layer.heightImage;
    filter_id = _filter_id;
    layer_name = _layer.name;
    
    
    for (int i = 0; i < height; i++) {
        vector<ofBoxPrimitive> tmp_boxes_part;
        for (int j = 0; j < width; j++) {
            ofBoxPrimitive box;
            box.set(20, 20, 20);
            box.setPosition(i*30, j*(-30), 0);
            tmp_boxes_part.push_back(box);
        }
        boxes.push_back(tmp_boxes_part);
    }
}




void BoxelFilter::update(ofPixels &_pixels) {
    pixels = _pixels;
}


void BoxelFilter::draw(float x, float y, float z) {
    ofPushMatrix();
    ofTranslate(x, y, z);
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            ofxYCrCb color = ofxYCrCb(125, 127, pixels.getColor(j, i).r);
            ofSetColor(color.toRgb());
            boxes[i][j].draw();
        }
    }
    ofPopMatrix();
}

