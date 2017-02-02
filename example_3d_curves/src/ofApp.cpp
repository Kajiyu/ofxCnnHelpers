#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    densityDataSource.setup("");
    densityDataSource.start(URA_SOCK);
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetCircleResolution(200);
    
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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    densityDataSource.update();
    layers = densityDataSource.getDensityDatas();
    if (cnnParamators.size() > 0) cnnParamators.clear();
    for (int i = 0; i < layers.size(); i++) {
        cnnParamators.push_back(layers[i].density_values);
    }
    
//    cnnDataSource.getDensityDatas(&cnnParamators);
    for (int i = 0; i < 5; i++) {
        bars[i].update(cnnParamators, i);
    }
    cam.setPosition(0, 0, ofGetElapsedTimef()*(-500)+10000);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cam.begin();
    for (int i = 0; i < 5; i++) {
        bars[i].draw(layerPos[i].x, layerPos[i].y, layerPos[i].z, layerColors[i]);
    }
    linesGenerator.draw(bars, layerPos);
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        densityDataSource.debugSave();
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
