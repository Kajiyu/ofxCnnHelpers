//
//  LifeGageComponent.cpp
//  SongCnn
//
//  Created by KajiharaYuma on 2017/01/03.
//
//

#include "LifeGageComponent.hpp"


void LifeGageComponent::setup() {
    animStartTime = ofGetElapsedTimef();
}


void LifeGageComponent::update(float _smallValue, float _middleValue) {
    if (smallCurveValue != _smallValue) {
        isAnimated = true;
        if (smallCurveValue < _smallValue) {
            isUp = true;
        } else {
            isUp = false;
        }
    } else if (middleCurveValue != _middleValue) {
        isAnimated = true;
    }
    smallCurveValue = _smallValue;
    middleCurveValue = _middleValue;
    
    if (isAnimated) {
        float duration = ofGetElapsedTimef() - animStartTime;
        bigCurveValue = duration;
        if (duration > 1) {
            isAnimated = false;
        }
    } else {
        animStartTime = ofGetElapsedTimef();
        bigCurveValue = 0;
    }
}


void LifeGageComponent::drawSmallCurve (float x, float y, ofPath * _smallCurve) {
    float small_arc = ofMap(smallCurveValue, 0, 1, 0, 361);
    _smallCurve->arc(ofPoint(x, y), 40, 40, 0, small_arc);
    _smallCurve->arcNegative(ofPoint(x, y), 39, 39, small_arc, 0);
}


void LifeGageComponent::drawMiddleCurve (float x, float y, ofPath * _middleCurve) {
    float middle_arc = ofMap(middleCurveValue, 0, 1, 0, 361);
    if (isAnimated) {
    } else {
        _middleCurve->arc(ofPoint(x, y), 55, 55, 0, middle_arc);
        _middleCurve->arcNegative(ofPoint(x, y), 54, 54, middle_arc, 0);
    }
}


void LifeGageComponent::drawBigCurve (float x, float y, ofPath * _bigCurve) {
    float big_arc = ofMap(bigCurveValue, 0, 1, 0, 361);
    if (isAnimated) {
        if (isUp) {
            _bigCurve->arc(ofPoint(x, y), 65, 65, 0, big_arc);
            _bigCurve->arcNegative(ofPoint(x, y), 60, 60, big_arc, 0);
        }
    } else {
        
    }
}


void LifeGageComponent::drawBadCurve(float x, float y, ofPath *_badCurve) {
    float big_arc = ofMap(bigCurveValue, 0, 1, 0, 361);
    if (isAnimated) {
        if (!isUp) {
            _badCurve->arc(ofPoint(x, y), 70, 70, 0, big_arc);
            _badCurve->arcNegative(ofPoint(x, y), 69, 69, big_arc, 0);
        }
    } else {
        
    }
}


/*
 * When the values of ConvNet are changed, this function will be called.
 * For make the middle arc animating.
 */
void LifeGageComponent::startAnime() {
}
