//
//  NetworkBar.cpp
//  example_3d_curves
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#include "NetworkBar.hpp"

void NetworkBar::setup() {
    for (int i = 0; i < 64; i++) {
        ofVec3f temp = ofVec3f(0, 0, i*100);
        pointsPos.push_back(temp);
        pointValues.push_back(0.0f);
        animated.push_back(false);
        animStartTime[i] = 0.0f;
        valueBuffers[i] = 0.0f;
    }
}


void NetworkBar::update(ofxJSON &json, string conv_name) {
    if (!isInitialized) {
        for (int i = 0; i < 64; i++) {
            float temp = ofToFloat(json[conv_name][i].toStyledString());
            pointValues[i] = temp;
            valueBuffers[i] = temp;
        }
        isInitialized = true;
    }
    for (int i = 0; i < 64; i++) {
        float temp = ofToFloat(json[conv_name][i].toStyledString());
        if (temp != valueBuffers[i] && animated[i] == false){
            animated[i] = true;
            valueBuffers[i] = temp;
            float t = pointValues[i];
            Tweenzor::add(&pointValues[i], t, temp, 0.f, 1.0f);
            Tweenzor::addCompleteListener( Tweenzor::getTween(&pointValues[i]), this, &NetworkBar::onComplete);
            //            animStartTime[i] = ofGetElapsedTimef();
        }
        else {
            if (animated[i]) {
                if (pointValues[i] == valueBuffers[i]) {
                    animated[i] = false;
                }
            }
        }
    }
}


void NetworkBar::draw(float x, float y, float z, ofColor mainColor) {
    ofPushMatrix();
    ofTranslate(x, y, z);
    for (int i = 0; i < 64; i++) {
        ofPushMatrix();
        ofPushStyle();
        float alpha = ofMap(pointValues[i], 0.0, 1.0, 0.0, 250.0);
        if (alpha < 40) alpha = 0;
        ofSetColor(mainColor, alpha);
        ofRotate(int(ofGetElapsedTimef()*60)%360);
        if (alpha > 0) {
            ofDrawBox(pointsPos[i].x, pointsPos[i].y, pointsPos[i].z, 50);
        } else {
            ofSetColor(255, 40 + 20*sin(ofGetElapsedTimef()));
            ofDrawBox(pointsPos[i].x, pointsPos[i].y, pointsPos[i].z, 50);
        }
        ofPopStyle();
        ofPopMatrix();
    }
    ofPopMatrix();
}


void NetworkBar::onComplete(float* arg) {
    
}
