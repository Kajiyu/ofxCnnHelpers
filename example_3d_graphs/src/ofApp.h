#pragma once

#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"
#include "BuildingCity.hpp"

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
    void exit();
		
    ofxCnnHelpers::ActivationLayerManager layerManager;
    vector<BuildingCity> cities;
    
    ofEasyCam cam;
    ofLight light;
};
