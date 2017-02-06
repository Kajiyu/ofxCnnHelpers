#pragma once

#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"

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
    
    ofxCnnHelpers::FilterImageManager filterManager;
    ofxCnnHelpers::FilterOutputLayer layer;
    vector<vector<ofPixels>> allPixels;
    ofTexture images[10][8];
    int mode = 1; // mode 1-10 :: 1-5:convX, 6-10:poolX
    ofTrueTypeFont font;
};
