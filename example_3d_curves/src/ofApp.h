#pragma once

#include "ofMain.h"
#include "addon_common.h"
#include "NetworkBar.hpp"
#include "BarLinesGenerator.hpp"

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
		
protected:
    ofEasyCam easyCam;
    ofCamera cam;
    vector<ofVec3f> layerPos;
    vector<ofColor> layerColors;
    ofColor lineColor;
    
    ofTrueTypeFont font;
    ofxJSON density_json;
    
    NetworkBar bars[5];
    BarLinesGenerator linesGenerator;
    
    ofxCnnLayersDataSource cnnDataSource;
};
