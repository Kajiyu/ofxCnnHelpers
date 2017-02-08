#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(200, 255, 255, 255);
    ofSetVerticalSync(true);
    
    filterManager.setup("");
    filterManager.start(FILTER_SOCK);
    inputManager.start(INPUT_IMAGE_SOCK, 302, 64);
    
    font.load("verdana.ttf", 20);
    
    // 4以下にするとクラッシュが起きる。
    for (int i = 0; i < 10; i++) {
        FiltersLayer layer;
        ofxCnnHelpers::FilterOutputLayer cnnLayer = filterManager.getLayerAtIndex(i+1);
        layer.setup(cnnLayer, 4000);
        layers.push_back(layer);
        cout << cnnLayer.name << " Setupped" << endl;
    }
    
    cam.setFarClip(100000);
    
    light.setup();
    light.setAreaLight(50000, 50000);
    light.setAmbientColor(ofColor(255, 255));
    light.enable();
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    cout << "Completed Setup" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    vector<vector<ofPixels>> pixels = filterManager.getAllPixels();
    for (int i = 0; i < layers.size(); i++) {
        layers[i].update(pixels[i]);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cam.begin();
    inputManager.draw(0, 0, 300, ofGetWidth()/4, ofGetHeight()/4);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    for (int i = 0; i < layers.size(); i++) {
        layers[i].draw(0, 0, (-4000)*i);
    }
    glDisable(GL_CULL_FACE);
    cam.end();
    ofDisableDepthTest();
    ofPushStyle();
    ofSetColor(0, 255, 0);
    font.drawString("3D Filters", 35, 35);
    ofPopStyle();
    
    ofSetColor(255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
//        filterManager.debugSave();
        inputManager.save();
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
