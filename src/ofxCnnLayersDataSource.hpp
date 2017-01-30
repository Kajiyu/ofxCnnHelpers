//
//  ofxCnnLayersDataSource.hpp
//  ofxCnnHelpers
//
//  Created by KajiharaYuma on 2017/01/30.
//
//

#pragma once
#include "ofMain.h"
#include "ofxJSON.h"

/*
 * ofxCnnLayersDataSource
 * MARK:::: DON'T FORGET to create the "cnnDatas" directory at "YOUR_APP_PATH/bin/data/".
 * input : json files
           - CNN_DENSITY : "YOUR_APP_PATH/bin/data/cnnDatas/density.json"
           - CNN_FILTER : "YOUR_APP_PATH/bin/data/cnnDatas/filter.json"
           - CNN_OUTPUT : "YOUR_APP_PATH/bin/data/cnnDatas/output.json"
 * usage : managing datas conv_output, fc_output and etc... of cnn.
 */


/*
 *
 * layersState ::
 * [
 *  [Image's Width, Image's Height, Filter's Number],
 *  ...,
 * ]
 *
 */

class ofxCnnLayersDataSource {
public:
    enum CnnDataMode {
        CNN_DENSITY,
        CNN_FILTER,
        CNN_OUTPUT
    };
    void setup(int _layer_num, vector<vector<int>> &layers, CnnDataMode _mode);
    void changeMode(CnnDataMode _mode);
    void changeUsingLayerIndex(int index);
    void update();
    void getDensityDatas(vector<vector<float>> * _densities);
    void getFilterDatas(vector<vector<vector<vector<float>>>> * _filters);
    void getOutputDatas(vector<vector<vector<vector<float>>>> * _outputs);
    
protected:
    bool isSetuped = false;
    CnnDataMode mode;
    int layer_num;
    int usingLayerIndex = 1;
    vector<vector<int>> layersState;
    vector<vector<float>> densities;
    vector<vector<vector<vector<float>>>> filters;
    vector<vector<vector<vector<float>>>> outputs;
};
