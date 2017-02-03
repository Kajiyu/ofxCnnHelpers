#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetCircleResolution(200);
    Tweenzor::init();
    
    easyCam.setFarClip(90000);
    easyCam.setNearClip(1);
    
    cam.setFarClip(90000);
    cam.setNearClip(1);
    
    color1 = ofColor(255, 0, 255);
    color2 = ofColor(0, 200, 255, 250);
    color3 = ofColor(0, 255, 0, 150);
    
    for (int i = 0; i < 5; i++) {
        plates[i].setup(color1, color2, color3);
    }
    font.load("verdana.ttf", 200);
    
    densitiesDataSource.setup("");
    densitiesDataSource.start(URA_SOCK, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    densitiesDataSource.update();
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < POINT_NUM; j++) {
            float small_value = ofMap(densitiesDataSource.getDensityDatas()[i].density_values[j], 0, 0.5, 0, 1);
            float middle_value = ofMap(densitiesDataSource.getDensityDatas()[i].density_values[j], 0, 0.8, 0, 1);
            if (i == 0) {
            } else if (i == 1) {
            } else if (i == 2) {
            } else if (i == 3) {
            } else if (i == 4){
                small_value = ofMap(densitiesDataSource.getDensityDatas()[i].density_values[j], 0, 10, 0, 1);
                middle_value = ofMap(densitiesDataSource.getDensityDatas()[i].density_values[j], 0, 10, 0, 1);
                //                cout << ofToFloat(density_json[conv_name][j].toStyledString()) << endl;
            }
            plates[i].updateLifeGageVslues(j, small_value, middle_value);
            //            int r = ofRandom(400);
            //            if (r % 200 == 0) {
            //                plates[i].lifeGageAnimStart(j);
            //            }
        }
    }
    
//    int time = ofGetElapsedTimef()*0.2;
//    if (time % 5 == 0) {
//        ofVec3f center = ofVec3f(1250, 1250, 3000*sin(ofGetElapsedTimef()*M_PI*0.3));
//        easyCam.setPosition(4000*cos(ofGetElapsedTimef()), 4000*sin(ofGetElapsedTimef()),3000*sin(ofGetElapsedTimef()*M_PI*0.3+3000));
//        easyCam.lookAt(center);
//    } else if (time % 5 == 1) {
//    } else if (time % 5 == 2) {
//    } else if (time % 5 == 3) {
//    } else if (time % 5 == 4) {
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    plateUnitingLines.clear();
    
    plateUnitingLines.setFilled(false);
    plateUnitingLines.setStrokeColor(ofColor(0, 200, 250, 120 * abs(sin(ofGetElapsedTimef()*M_PI/2)+0.3)));
    plateUnitingLines.setStrokeWidth(1.1);
    
    ofVec3f preUnderCenter;
    
    easyCam.begin();
    
    ofPushMatrix();
    ofRotate(90, 1, 0, 0);
    
    ofVec3f layerCenters[5];
    for (int i = 0; i < 5; i++) {
        plates[i].draw(0, 0, i*(-12500) + 3000*sin(ofGetElapsedTimef()*M_PI*0.3 + i*M_PI));
        layerCenters[i] = ofVec3f(2250, 0 + 2250, i*(-12500) + 3000*sin(ofGetElapsedTimef()*M_PI*0.3 + i*M_PI));
        string conv_name = "Conv" + ofToString(i+1) + " Layer";
        
        ofPushMatrix();
        ofTranslate(0, 0, i*(-12500) + 1000*sin(ofGetElapsedTimef()*M_PI*0.3 + i*M_PI));
        ofVec3f cameraPos = easyCam.getPosition();
        ofVec3f letterPos = ofVec3f(-2500, 3000, i*(-12500) + 3000*sin(ofGetElapsedTimef()*M_PI*0.3 + i*M_PI));
        ofVec3f sabun = cameraPos - letterPos;
        ofVec3f destination = sabun.getCrossed(ofVec3f(0, 0, 1)).normalize();
        float cosDes = sabun.dot(ofVec3f(0, 0, 1)) / (cameraPos.length());
        float deg = acos(cosDes);
        ofRotate(deg*360, destination.x, destination.y, destination.z);
        font.drawString(conv_name, -2500, 3000);
        ofPopMatrix();
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < POINT_NUM; j++) {
            plateUnitingLines.moveTo(plates[i].points[j].x, plates[i].points[j].y, i*(-12500)
                                     + 3000*sin(ofGetElapsedTimef()*M_PI*0.3 + i*M_PI));
            if (plates[i].lifeGages[j].isAnimated) {
                if (i == 0) {
                    ofVec3f above = (layerCenters[i] + layerCenters[i+1]) / 2.0;
                    plateUnitingLines.lineTo(above);
                } else if (i == 4) {
                    ofVec3f below = (layerCenters[i] + layerCenters[i-1]) / 2.0;
                    plateUnitingLines.lineTo(below);
                } else {
                    ofVec3f above = (layerCenters[i] + layerCenters[i+1]) / 2.0;
                    plateUnitingLines.lineTo(above);
                    
                    plateUnitingLines.moveTo(plates[i].points[j].x, plates[i].points[j].y, i*(-12500)
                                             + 3000*sin(ofGetElapsedTimef()*M_PI*0.3 + i*M_PI));
                    
                    ofVec3f below = (layerCenters[i] + layerCenters[i-1]) / 2.0;
                    plateUnitingLines.lineTo(below);
                }
            }
        }
    }
    plateUnitingLines.close();
    plateUnitingLines.draw();
    ofPopMatrix();
    
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        densitiesDataSource.debugSave();
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
