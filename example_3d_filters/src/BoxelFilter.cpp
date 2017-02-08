//
//  BoxelFilter.cpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#include "BoxelFilter.hpp"


void BoxelFilter::setup(ofxCnnHelpers::FilterOutputLayer &_layer, int _filter_id) {
    width = _layer.widthImage;
    height = _layer.heightImage;
    filter_id = _filter_id;
    layer_name = _layer.name;
    
    
//    for (int i = 0; i < height; i++) {
//        vector<ofBoxPrimitive> tmp_boxes_part;
//        for (int j = 0; j < width; j++) {
//            ofBoxPrimitive box;
//            box.set(20, 20, 20);
//            box.setPosition(i*30, j*(-30), 0);
//            tmp_boxes_part.push_back(box);
//        }
//        boxes.push_back(tmp_boxes_part);
//    }
    
    ofBoxPrimitive tmpBox;
    tmpBox.set(20, 20, 20);
    vboMesh = tmpBox.getMesh();
    shader.load("shaders/shader");
}




void BoxelFilter::update(ofPixels &_pixels) {
//    pixels = _pixels;
    if (texture.bAllocated()) {
        texture.loadData(_pixels);
    } else {
        texture.allocate(_pixels);
    }
}


void BoxelFilter::draw(float x, float y, float z) {
//    for (int i = 0; i < boxes.size(); i++) {
//        for (int j = 0; j < boxes[i].size(); j++) {
//            ofxYCrCb color = ofxYCrCb(125, 127, pixels.getColor(j, i).r);
//            ofSetColor(color.toRgb());
//            boxes[i][j].draw();
//        }
//    }
    
    glPushMatrix();
    glTranslated(x, y, z);
    ofRotate(90, 0, 0, -1);
    shader.begin();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    shader.setUniformTexture("tex", texture, 0);
    shader.setUniform1f("time", (ofGetElapsedTimeMillis() % 30000) / 30000.0f);
    shader.setUniform1f("width", float(width));
    shader.setUniform1f("height", float(height));
    vboMesh.drawInstanced(OF_MESH_FILL, float(width*height));
    
    glDisable(GL_CULL_FACE);
    shader.end();
    glPopMatrix();
}

