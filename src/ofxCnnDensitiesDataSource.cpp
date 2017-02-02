//
//  ofxCnnDensitiesDataSource.cpp
//  example_3d_curves
//
//  Created by KajiharaYuma on 2017/02/02.
//
//

#include "ofxCnnDensitiesDataSource.hpp"


void ofxCnnDensitiesDataSource::setup(string filename) {
    if (densityLayers.size() > 0) {
        densityLayers.clear();
    }
    if (filename == "") {
        ofFile file("density.json");
        if (file.exists()) {
            ofxCereal::jsonin ji(file);
            ji >> densityLayers;
            isSetup = true;
        }
        jsonFileName = filename;
        
    } else {
        ofFile file(filename);
        if (file.exists()) {
            ofxCereal::jsonin ji(file);
            ji >> densityLayers;
            isSetup = true;
        }
        jsonFileName = filename;
    }
}


void ofxCnnDensitiesDataSource::update() {
//    for (int i = 0; i < densityLayers.size(); i++) {
//        cout << densityLayers[i].layerName << endl;
//    }
}


vector<DensityLayer> ofxCnnDensitiesDataSource::getDensityDatas() {
    return densityLayers;
}


void ofxCnnDensitiesDataSource::start(string port){
    if (!isThreadRunning()) {
        zmqSubscriber.connect(port);
        startThread();
    }
}


void ofxCnnDensitiesDataSource::stop(){
    if (isThreadRunning()) {
        stopThread();
    }
}


void ofxCnnDensitiesDataSource::threadedFunction(){
    while (isThreadRunning()){
        if(lock()) {
            while (zmqSubscriber.hasWaitingMessage(500)) {
                zmqSubscriber.getNextMessage(private_buffer);
                densitiesDomain.tmpJson.openFromBuffer(private_buffer);
                densitiesDomain.getAsDensityLayers(&densityLayers);
                zmq_get_count++;
                cout << "get ::: " << zmq_get_count << endl;
                break;
            }
            unlock();
        } else {
        }
    }
}


void ofxCnnDensitiesDataSource::save() {
    ofFile file("density.json", ofFile::WriteOnly);
    cereal::jsonout jo(file);
    jo << densityLayers;
}

void ofxCnnDensitiesDataSource::debugSave() {
    string filename = "density" + ofToString(save_count) + ".json";
    ofFile file(filename, ofFile::WriteOnly);
    cereal::jsonout jo(file);
    jo << densityLayers;
    save_count++;
}
