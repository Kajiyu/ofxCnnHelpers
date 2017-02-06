#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255);
    ofSetVerticalSync(true);
    ofSetFrameRate(0);
    
    filterManager.setup("");
    filterManager.start(FILTER_SOCK);
    
    layer = filterManager.getLayerAtIndex(mode);
    allPixels = filterManager.getAllPixels();
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            images[i][j].allocate(allPixels[i][j]);
        }
    }
    
    font.load("verdana.ttf", 20);
}

//--------------------------------------------------------------
void ofApp::update(){
    vector<ofPixels> tmpPixels = filterManager.getPixelsAtIndexLayer(mode);
    allPixels = filterManager.getAllPixels();
    layer = filterManager.getLayerAtIndex(mode);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            images[i][j].loadData(allPixels[i][j]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
//    ofSetColor(0, 255, 0);
//    font.drawString(layer.name, 5, 5);
    ofSetColor(255, 255);
    for (int i = 0; i < 10; i++) {
        float _x;
        if (i > 4) {
            _x = ofGetWidth()/2;
        } else {
            _x = 0;
        }
        for (int j = 0; j < 8; j++) {
            ofPushMatrix();
            ofTranslate(_x + ofGetWidth()*j/16, ofGetHeight()*(i%5)/5);
            if (mode-1 == i) {
                ofSetColor(255, 0, 0);
            } else {
//                ofSetColor(0, 255);
            }
            ofDrawRectangle(0, 0, ofGetWidth()/16, ofGetHeight()/5);
            ofFill();
            ofSetColor(255, 255);
            ofPushMatrix();
            ofTranslate(5, 5);
            images[i][j].draw(0, 0, ofGetWidth()/16 -10, ofGetHeight()/5 - 10);
            ofPopMatrix();
            ofPopMatrix();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        filterManager.debugSave();
    }
    if (key == '0') {
        mode = 10;
    }
    if (key == '1') {
        mode = 1;
    }
    if (key == '2') {
        mode = 2;
    }
    if (key == '3') {
        mode = 3;
    }
    if (key == '4') {
        mode = 4;
    }
    if (key == '5') {
        mode = 5;
    }
    if (key == '6') {
        mode = 6;
    }
    if (key == '7') {
        mode = 7;
    }
    if (key == '8') {
        mode = 8;
    }
    if (key == '9') {
        mode = 9;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
