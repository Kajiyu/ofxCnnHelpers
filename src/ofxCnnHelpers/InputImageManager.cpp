//
//  InputImageManager.cpp
//  example_3d_filters
//
//  Created by KajiharaYuma on 2017/02/07.
//
//

#include "InputImageManager.h"
#include "Poco/Base64Decoder.h"

OFX_CNN_HELPERS_BEGIN_NAMESPACE

void InputImageManager::start(string port, int w, int h) {
    if (image.load("input_image.jpg")) {
    } else {
        image.allocate(w, h, OF_IMAGE_COLOR);
    }
    if ( !isThreadRunning() )
    {
        zmqSubscriber.connect(port);
        startThread();
    }
}


void InputImageManager::stop() {
    if ( isThreadRunning() )
    {
        stopThread();
    }
}


void InputImageManager::threadedFunction() {
    while ( isThreadRunning() )
    {
        while ( zmqSubscriber.hasWaitingMessage(500) )
        {
            string bufferString;
            zmqSubscriber.getNextMessage(bufferString);
            stringstream ss;
            ss << bufferString;
            Poco::Base64Decoder b64in(ss);
            
            ofBuffer buffer;
            b64in >> buffer;
            if (lock()) {
//                image.load(buffer);
            }
            unlock();
            cout << "InputImageManager:::Get information from ZeroMQ" << endl;
            break;
        }
    }
}


void InputImageManager::save() {
    image.save("input_image.jpg");
}


void InputImageManager::draw(int x, int y, int z, int w, int h) {
    if (image.bAllocated()) {
    } else {
        ofPushMatrix();
        ofTranslate(x, y, z);
        image.draw(0, 0, 0, w, h);
        ofPopMatrix();
    }
}

OFX_CNN_HELPERS_END_NAMESPACE
