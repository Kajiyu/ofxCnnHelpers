//
//  LifeGageComponent.hpp
//  SongCnn
//
//  Created by KajiharaYuma on 2017/01/03.
//
//

#pragma once
#include "ofMain.h"
#include "addon_common.h"
#include "const_common.h"

class LifeGageComponent {
public:
    void setup();
    void update(float _smallValue, float _middleValue);
//    void draw(float x, float y);
    void startAnime();
    
    void drawSmallCurve(float x, float y, ofPath *_smallCurve);
    void drawMiddleCurve(float x, float y, ofPath * _middleCurve);
    void drawBigCurve(float x, float y, ofPath * _bigCurve);
    void drawBadCurve(float x, float y, ofPath * _badCurve);
    
    bool isAnimated = false;
    bool isUp = false;
    float smallCurveValue = 0;
    float middleCurveValue = 0;
    float bigCurveValue = 0;
    
protected:
    ofPath smallCurve;
    ofPath middleCurve;
    ofPath bigCurve;
    ofPath badCurve;
    ofColor smallCurveColor;
    ofColor middleCurveColor;
    ofColor bigCurveColor;
    float animStartTime;
};
