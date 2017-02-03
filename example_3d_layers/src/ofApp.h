#pragma once

#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"
#include "LifeGagesPlateComponent.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    ofxJSON density_json;
    
    /**************************
     3D
     **************************/
    ofCamera cam;
    ofEasyCam easyCam;
    float pulse = 0;
    
    vector<ofPoint> conv1_points;
    vector<ofPoint> conv2_points;
    vector<ofPoint> conv3_points;
    vector<ofPoint> conv4_points;
    vector<ofPoint> conv5_points;
    
    LifeGagesPlateComponent plates[5];
    
    ofColor color1;
    ofColor color2;
    ofColor color3;
    
    ofPath plateUnitingLines;
    ofTrueTypeFont font;
    
    ofxCnnHelpers::ActivationLayerManager layerManager;
};
