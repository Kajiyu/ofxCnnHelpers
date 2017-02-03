//
//  LifeGagesPlateComponent.cpp
//  SongCnn
//
//  Created by KajiharaYuma on 2017/01/08.
//
//

#include "LifeGagesPlateComponent.hpp"

void LifeGagesPlateComponent::setup(ofColor & _smallColor, ofColor & _middleColor, ofColor & _bigColor) {
    int col = 0;
    int row = 0;
    for (int i = 0; i < POINT_NUM; i++) {
        ofPoint p = ofPoint(col * 500, row * 500);
        points.push_back(p);
        col++;
        if (col % 8 == 0) {
            row++;
            col = 0;
        }
        
        LifeGageComponent tmp_comp = LifeGageComponent();
        tmp_comp.setup();
        lifeGages.push_back(tmp_comp);
        cout << col << " : " << row << endl;
    }
    color1 = _smallColor;
    color2 = _middleColor;
    color3 = _bigColor;
    
    for (auto gage : lifeGages) {
        cout << gage.smallCurveValue << endl;
    }
    
    font.load("verdana.ttf", 60);
}


void LifeGagesPlateComponent::updateLifeGageVslues(int index, float small_value, float middle_value) {
    lifeGages[index].update(small_value, middle_value);
//    color3 = ofColor(255, 255, 10, 200);
}


void LifeGagesPlateComponent::draw(float x, float y, float z) {
    smallCurves.clear();
    middleCurves.clear();
    bigCurves.clear();
    badCurves.clear();
    backLines.clear();
    highlightenLines.clear();
    badHighlightenLines.clear();
    
    smallCurves.setStrokeColor(color1);
    smallCurves.setStrokeWidth(5);
    smallCurves.setFilled(false);
    smallCurves.setCircleResolution(60);
    
    middleCurves.setStrokeColor(color2);
    middleCurves.setStrokeWidth(5);
    middleCurves.setFilled(false);
    middleCurves.setCircleResolution(200);
    
    bigCurves.setStrokeColor(color3);
    bigCurves.setStrokeWidth(4);
    bigCurves.setFilled(false);
    bigCurves.setCircleResolution(200);
    
    badCurves.setStrokeColor(ofColor(255, 0, 255, 200));
    badCurves.setStrokeWidth(4);
    badCurves.setFilled(false);
    badCurves.setCircleResolution(200);
    
    backLines.setStrokeColor(ofColor(255, 50));
    backLines.setStrokeWidth(0.1);
    backLines.setFilled(false);
    
    highlightenLines.setStrokeColor(ofColor(0, 255, 0, 255 * abs(sin(ofGetElapsedTimef()*M_PI/2))));
    highlightenLines.setStrokeWidth(1.1);
    highlightenLines.setFilled(false);
    
    badHighlightenLines.setStrokeColor(ofColor(255, 0, 255, 255 * abs(sin(ofGetElapsedTimef()*M_PI/2))));
    badHighlightenLines.setStrokeWidth(1.1);
    badHighlightenLines.setFilled(false);
    
    
    ofPushMatrix();
    ofTranslate(x, y, z);
    
    ofPushStyle();
    ofSetColor(255, 30);
    ofDrawRectangle(-500, -500, 1000 + 3500, 1000 + 3500);
    ofPopStyle();
    
    int col = 0;
    int row = 0;
    
    for (int i = 0; i < POINT_NUM; i++) {
        backLines.moveTo(points[i]);
        highlightenLines.moveTo(points[i]);
        badHighlightenLines.moveTo(points[i]);
        if (col != 7) {
            backLines.lineTo(points[(col+1) + row*8]);
            if (lifeGages[i].isAnimated && lifeGages[(col+1) + row*8].isAnimated) {
                if (lifeGages[i].isUp && lifeGages[(col+1) + row*8].isUp) {
                    highlightenLines.lineTo(points[(col+1) + row*8]);
                } else if (!lifeGages[i].isUp && !lifeGages[(col+1) + row*8].isUp) {
                    badHighlightenLines.lineTo(points[(col+1) + row*8]);
                } else {
                }
            }
        }
        backLines.moveTo(points[i]);
        highlightenLines.moveTo(points[i]);
        badHighlightenLines.moveTo(points[i]);
        if (row != 7) {
            backLines.lineTo(points[col + (row+1)*8]);
            if (lifeGages[i].isAnimated && lifeGages[col + (row+1)*8].isAnimated) {
                if (lifeGages[i].isUp && lifeGages[(col+1) + row*8].isUp) {
                    highlightenLines.lineTo(points[col + (row+1)*8]);
                } else if (!lifeGages[i].isUp && !lifeGages[(col+1) + row*8].isUp) {
                    badHighlightenLines.lineTo(points[col + (row+1)*8]);
                } else {
                    highlightenLines.lineTo(points[col + (row+1)*8]);
                }
            }
        }
        col++;
        if (col % 8 == 0) {
            row++;
            col = 0;
        }
    }
    backLines.close();
    highlightenLines.close();
    badHighlightenLines.close();
    
    for (int i = 0; i < POINT_NUM; i++) {
        ofPushMatrix();
        ofTranslate(0, 0, -900);
        font.drawString(ofToString(lifeGages[i].middleCurveValue), points[i].x, points[i].y);
        ofPopMatrix();
        lifeGages[i].drawSmallCurve(points[i].x, points[i].y, &smallCurves);
        lifeGages[i].drawMiddleCurve(points[i].x, points[i].y, &middleCurves);
        lifeGages[i].drawBigCurve(points[i].x, points[i].y, &bigCurves);
        lifeGages[i].drawBadCurve(points[i].x, points[i].y, &badCurves);
        smallCurves.close();
        middleCurves.close();
        bigCurves.close();
        badCurves.close();
    }
    
//    smallCurves.close();
//    middleCurves.close();
//    kbigCurves.close();
    backLines.draw();
    highlightenLines.draw();
    badHighlightenLines.draw();
//    smallCurves.draw();
    middleCurves.draw();
    bigCurves.draw();
    badCurves.draw();
    
    ofPopMatrix();
}


void LifeGagesPlateComponent::lifeGageAnimStart(int index) {
    lifeGages[index].isAnimated = true;
}
