//
//  LifeGagesPlateComponent.hpp
//  SongCnn
//
//  Created by KajiharaYuma on 2017/01/08.
//
//

#pragma once
#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"

#include "LifeGageComponent.hpp"

#define POINT_NUM 64

class LifeGagesPlateComponent {
public:
    void setup(ofColor & smallColor, ofColor & middleColor, ofColor & bigColor);
    void updateLifeGageVslues(int index, float small_value, float middle_value);
    void draw(float x, float y, float z);
    void lifeGageAnimStart(int index);
    
    vector<LifeGageComponent> lifeGages;
    vector<ofPoint> points;
    
    
protected:
    ofColor color1;
    ofColor color2;
    ofColor color3;
    
    ofPath smallCurves;
    ofPath middleCurves;
    ofPath bigCurves;
    ofPath badCurves;
    ofPath backLines;
    ofPath highlightenLines;
    ofPath badHighlightenLines;
    ofTrueTypeFont font;
};
