//
//  BarLinesGenerator.cpp
//  example_3d_curves
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#include "BarLinesGenerator.hpp"

void BarLinesGenerator::setup() {
    for (int i = 0; i < 4; i++) {
        lines[i].setStrokeColor(ofColor(255, 120));
        lines[i].setStrokeWidth(0.1f);
        lines[i].setFilled(false);
        lines[i].setCircleResolution(200);
        lines[i].setCurveResolution(1000);
    }
    ofEnableSmoothing();
}


void BarLinesGenerator::draw(NetworkBar *bars, vector<ofVec3f> layersPos) {
//    cout << bars[1].pointsPos[10].z << endl;
    for (int i = 0; i < 4; i++) {
        lines[i].clear();
        for (int j = 0; j < 64; j++) {
            ofVec3f beginPos = bars[i].pointsPos[j] + layersPos[i];
            for (int k = 0; k < 64; k++) {
                if(bars[i].pointValues[j]>0.4 && bars[i+1].pointValues[k]>0.4){
                    ofVec3f endPos = bars[i+1].pointsPos[k] + layersPos[i+1];
                    ofVec3f circleCenter = ofVec3f(0, 0,
                                                   (pow(beginPos.x,2)+pow(beginPos.y,2)+pow(beginPos.z,2)
                                                    -(pow(endPos.x,2)+pow(endPos.y,2)+pow(endPos.z,2)))/
                                                   (2*(beginPos.z - endPos.z)));
                    ofVec3f bezierCenter = (beginPos+endPos)/2.0;
                    float radius = (beginPos-circleCenter).length();
                    ofVec3f normalVec = (bezierCenter-circleCenter).normalize()*radius;
                    lines[i].moveTo(beginPos);
                    lines[i].quadBezierTo(beginPos+normalVec*0.000001, beginPos+normalVec, endPos);
                    //                    lines[i].close();
                }
            }
        }
        lines[i].draw();
    }
}
