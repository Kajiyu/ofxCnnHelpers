#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetCircleResolution(200);
    Tweenzor::init();
    
    cam.setFarClip(10000);
    for (int i = 0; i < 5; i++) {
        float degree = 2*M_PI*i/float(3);
        float depth = i*5000*(-1);
        ofVec3f temp = ofVec3f(2000*sin(degree), 2000*cos(degree), depth);
        layerPos.push_back(temp);
        
        ofColor tempColor;
        tempColor.setHsb(255.0f*float(i)/5.0f+20, 255, 255);
        layerColors.push_back(tempColor);
        
        bars[i].setup();
    }
    linesGenerator.setup();
    font.load("verdana.ttf", 200);
    ofEnableDepthTest();
    
    vector<vector<int>> layersState;
    vector<int> layer1;
    layer1.push_back(300);
    layer1.push_back(62);
    layer1.push_back(64);
    vector<int> layer2;
    layer2.push_back(148);
    layer2.push_back(29);
    layer2.push_back(64);
    vector<int> layer3;
    layer3.push_back(72);
    layer3.push_back(13);
    layer3.push_back(64);
    vector<int> layer4;
    layer4.push_back(34);
    layer4.push_back(5);
    layer4.push_back(64);
    vector<int> layer5;
    layer5.push_back(15);
    layer5.push_back(1);
    layer5.push_back(64);
    layersState.push_back(layer1);
    layersState.push_back(layer2);
    layersState.push_back(layer3);
    layersState.push_back(layer4);
    layersState.push_back(layer5);
    cnnDataSource.setup(5, layersState, ofxCnnLayersDataSource::CnnDataMode::CNN_DENSITY);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cnnDataSource.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
