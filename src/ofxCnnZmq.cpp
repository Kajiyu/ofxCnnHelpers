//
//  ofxCnnZmq.cpp
//  cnnHelpersTest1
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#include "ofxCnnZmq.hpp"

void ofxCnnZmq::start(string port) {
    if (!isThreadRunning()) {
        requestClient.connect(port);
        startThread();
    }
}



void ofxCnnZmq::stop() {
    if (isThreadRunning()) {
        stopThread();
    }
}


void ofxCnnZmq::threadedFunction() {
    while (isThreadRunning()){
        if (int(ofGetElapsedTimef()) % 5 == 0) {
            if(lock()) {
                bool succeed = requestClient.send("1");
                if (succeed) {
                    ofBuffer buffer;
                    while (requestClient.hasWaitingMessage(10000)) {
                        requestClient.getNextMessage(buffer);
                        json.openFromBuffer(buffer);
                        cout << "get!!!!!"<< endl;
                        json.save("cnnDatas/density.json");
                        break;
                    }
                } else {
                    ofLogWarning("threadedFunction()") << "Failed to send data to ura_socket.";
                }
                unlock();
            } else {
                ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
            }
        }
    }
}
