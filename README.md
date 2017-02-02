# ofxCnnHelpers

This addon is composed of some util classes which make easy to deal with datas about ConvNet.

### Usage

#### ofxCnnDensitiesDataSource
This class is a data manager of densities of pixels in conv-filters, in each layer.<br/>
The below struct is a base information about a conv-layer
```
struct DensityLayer {
    string layerName;
    int filtersNum = 0;
    vector<float> density_values;
};
```
You can use like that.
```
ofxCnnDensitiesDataSource densityDataSource;
vector<DensityLayer> layers;

void ofApp::setup(){
  densityDataSource.setup("");
  densityDataSource.start("tcp://127.0.0.1:9001");
}

void ofApp::update(){
    densityDataSource.update();
    layers = densityDataSource.getDensityDatas();
}
```

### Dependent Addons
- ofxJSON
- ofxZmq
- ofxCereal
