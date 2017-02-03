//
//  ActivationLayerManager.cpp
//
//  Created by KajiharaYuma on 2017/02/02.
//
//

#include "ActivationLayerManager.h"

OFX_CNN_HELPERS_BEGIN_NAMESPACE

void ActivationLayerManager::setup(string fileName)
{
    layers.clear();
    
    ofFile file(fileName.empty() ? "activation.json" : fileName);
    if ( file.exists() )
    {
        ofxCereal::jsonin jin(file);
        jin >> layers;
    }
}


vector<ActivationLayer> ActivationLayerManager::get()
{
    return layers;
}


void ActivationLayerManager::start(string port)
{
    if ( !isThreadRunning() )
    {
        zmqSubscriber.connect(port);
        startThread();
    }
}


void ActivationLayerManager::stop()
{
    if ( isThreadRunning() )
    {
        stopThread();
    }
}


void ActivationLayerManager::threadedFunction()
{
    auto getActivationLayersFromBuffer = [](vector<ActivationLayer> * layers, ofBuffer buffer)
    {
        ofxJSON json;
        json.openFromBuffer(buffer);
        
        layers->clear();
        
        for (int i = 0; i < json["layerNum"].asInt(); i++)
        {
            ActivationLayer l;
            l.name = json["layers"][i]["layerName"].toStyledString();
            l.numFilters = json["layers"][i]["valuesNum"].asInt();
            for (int j = 0; j < l.numFilters; j++)
            {
                l.values.push_back(json["layers"][i]["values"][j].asFloat());
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
            getActivationLayersFromBuffer(&layers_buffer, private_buffer);
            if (lock()) {
                swap(layers_buffer, layers);
            }
            unlock();
            layers_buffer.clear();
            break;
        }
    }
}

void ActivationLayerManager::save()
{
    ofFile file("activation.json", ofFile::WriteOnly);
    cereal::jsonout jo(file);
    jo << layers;
}


void ActivationLayerManager::debugSave()
{
    static unsigned int save_count = 0;
    string filename = "activation_" + ofToString(save_count) + ".json";
    ofFile file(filename, ofFile::WriteOnly);
    cereal::jsonout jo(file);
    jo << layers;
    save_count++;
}


int ActivationLayerManager::getLayersNum() {
    return layers.size();
}

OFX_CNN_HELPERS_END_NAMESPACE
