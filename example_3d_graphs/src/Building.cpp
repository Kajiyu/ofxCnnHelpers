//
//  Building.cpp
//  example_3d_graphs
//
//  Created by KajiharaYuma on 2017/02/03.
//
//

#include "Building.hpp"

void Building::setup(ofFloatColor _color, float _width, float _height, float _depth) {
    this->color = _color;
    this->width = _width;
    this->height = _height;
    this->depth = _depth;
}


void Building::startAnimation(float endHeight) {
    Tweenzor::add(&height, height, endHeight, 0.f, 1.f, EASE_IN_OUT_CUBIC);
    ofFloatColor tmpColor = ofFloatColor(0.16,0.36,0.89, 0.7);
    ofFloatColor white = ofFloatColor(1.f, 1.f, 1.f, 1.f);
    Tweenzor::add(&color, white, tmpColor, 0, 1.f, EASE_IN_OUT_CUBIC);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&height), this, &Building::onComplete);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&color), this, &Building::onComplete);
    
    this->isAnimating = true;
}



void Building::onComplete(float *arg) {
    this->isAnimating = false;
    color = ofFloatColor(0.16,0.36,0.89, 0.7);
}


void Building::draw(float _x, float _y, float _z) {
    ofPushMatrix();
    ofTranslate(_x, _y+height/2, _z);
    box.setPosition(0, 0, 0);
    box.set(width, height, depth);
    ofSetColor(color);
    if (isAnimating) {
        box.draw();
    } else {
        box.draw(OF_MESH_FILL);
    }
    ofPopMatrix();
}
