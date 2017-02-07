//
//  FilterImageManager.cpp
//  example_2d_images
//
//  Created by KajiharaYuma on 2017/02/06.
//
//

#include "FilterImageManager.h"

OFX_CNN_HELPERS_BEGIN_NAMESPACE

void FilterImageManager::setup(string filename){
    layers.clear();
    
    ofFile file(filename.empty() ? "filter_outputs.json" : filename);
    if ( file.exists() )
    {
        ofxCereal::jsonin jin(file);
        jin >> layers;
    }
    
    
    /// allocate textures
    if (pixelsVectors.size() > 0) pixelsVectors.clear();
    for (int i = 0; i < layers.size(); i++) {
        vector<ofPixels> pixelsVector;
        for (int j = 0; j < layers[i].numImages; j++) {
            ofPixels tmpPixels;
            tmpPixels.allocate(layers[i].widthImage, layers[i].heightImage, OF_PIXELS_RGB);
            for (int y = 0; y < layers[i].heightImage; y++){
                for (int x = 0; x < layers[i].widthImage; x++){
                    tmpPixels.setColor(x,y,ofColor(0,0,0));
                }
            }
            pixelsVector.push_back(tmpPixels);
        }
        pixelsVectors.push_back(pixelsVector);
    }
}


void FilterImageManager::start(string port){
    if ( !isThreadRunning() )
    {
        zmqSubscriber.connect(port);
        startThread();
    }
}


void FilterImageManager::stop(){
    if ( isThreadRunning() )
    {
        stopThread();
    }
}


void FilterImageManager::threadedFunction(){
    auto getActivationLayersFromBuffer = [](vector<FilterOutputLayer> * layers, ofBuffer buffer, FilterImageManager * tmp)
    {
        ofxJSON json;
        json.openFromBuffer(buffer);
        
        layers->clear();
        
        for (int i = 0; i < json["layerNum"].asInt(); i++)
        {
            FilterOutputLayer l;
            l.name = json["layers"][i]["layerName"].toStyledString();
            l.numImages = json["layers"][i]["numImages"].asInt();
            l.widthImage = json["layers"][i]["widthImage"].asInt();
            l.heightImage = json["layers"][i]["heightImage"].asInt();
            l.widthFilter = json["layers"][i]["widthFilter"].asInt();
            l.heightFilter = json["layers"][i]["heightFilter"].asInt();
            for (int j = 0; j < l.numImages; j++)
            {
                for (int y = 0; y < l.heightImage; y++){
                    for (int x = 0; x < l.widthImage; x++){
                        int pixValue = json["layers"][i]["images"][j][y][x].asInt();
                        //cout << "debug::"<<i+1<<"layer "<<j<<"枚目の "<<x+1<<":"<<y+1<<endl;
                        tmp->pixelsVectors[i][j].setColor(x,y,ofColor(pixValue, pixValue, pixValue));
                    }
                }
//                l.values.push_back(json["layers"][i]["values"][j].asFloat());
            }
            layers->push_back(l);
        }
    };
    
    while ( isThreadRunning() )
    {
        while ( zmqSubscriber.hasWaitingMessage(500) )
        {
            ofBuffer private_buffer;
            zmqSubscriber.getNextMessage(private_buffer);
            getActivationLayersFromBuffer(&layers_buffer, private_buffer, this);
            if (lock()) {
                swap(layers_buffer, layers);
            }
            unlock();
            layers_buffer.clear();
            cout << "FilterImageManager:::Get information from ZeroMQ" << endl;
            break;
        }
    }
    
}


void FilterImageManager::save(){
    ofFile file("filter_outputs.json.json", ofFile::WriteOnly);
    cereal::jsonout jo(file);
    jo << layers;
}


void FilterImageManager::debugSave(){
    static unsigned int save_count = 0;
    string filename = "filter_outputs_" + ofToString(save_count) + ".json";
    ofFile file(filename, ofFile::WriteOnly);
    cereal::jsonout jo(file);
    jo << layers;
    save_count++;
}


int FilterImageManager::getLayersNum(){
    return layers.size();
}


vector<FilterOutputLayer> FilterImageManager::get() {
    return layers;
}


vector<vector<ofPixels>> FilterImageManager::getAllPixels() {
    return pixelsVectors;
}

vector<ofPixels> FilterImageManager::getPixelsAtIndexLayer(int index) {
    return pixelsVectors[index-1];
}


FilterOutputLayer FilterImageManager::getLayerAtIndex(int index) {
    return layers[index-1];
}

OFX_CNN_HELPERS_END_NAMESPACE
