#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackgroundGradient(ofColor(100, 255), ofColor(220, 255));
    ofSetVerticalSync(true);
    Tweenzor::init();
    layerManager.setup("");
    layerManager.start(URA_SOCK);
    
    for (int i = 0; i < layerManager.getLayersNum(); i++) {
        BuildingCity city;
        ofxCnnHelpers::ActivationLayer layer = layerManager.get()[i];
        city.setup(layer.numFilters, layer);
        cities.push_back(city);
    }
    
    cam.setFarClip(100000);
    
    light.setup();
    light.enable();
    light.setAreaLight(4000,4000);
    light.setPosition(0,3000, 500);
    light.setAmbientColor(ofColor(200, 200));
}

//--------------------------------------------------------------
void ofApp::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );
    for (int i = 0; i < cities.size(); i++) {
        ofxCnnHelpers::ActivationLayer layer = layerManager.get()[i];
        cities[i].update(layer);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cam.begin();
    ofSetColor(100, 240, 240, 50);
    ofPushMatrix();
    ofTranslate((cities[0].width + 400)/2, 0, (cities.size()*500)/2);
    ofDrawBox(-200, 0, -200, cities[0].width + 400, 10, cities.size()*500 + 400);
    ofPopMatrix();
    for (int i = 0; i < cities.size(); i++) {
        cities[i].draw(0, 0, i*500);
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        layerManager.debugSave();
    }
}

void ofApp::exit() {
    Tweenzor::destroy();
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
