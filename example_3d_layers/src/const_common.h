//
//  const_common.h
//  example_3d_layers
//
//  Created by KajiharaYuma on 2017/02/03.
//
//

#pragma once

#define REC_SOCK "tcp://127.0.0.1:9999"
#define DENSITY_SOCK "tcp://127.0.0.1:9996"
#define SEND_SOCK_1 "tcp://127.0.0.1:9991"
#define SEND_SOCK_2 "tcp://127.0.0.1:9992"
#define SEND_SOCK_3 "tcp://127.0.0.1:9993"
#define SEND_SOCK_4 "tcp://127.0.0.1:9994"
#define SEND_SOCK_5 "tcp://127.0.0.1:9995"

#define URA_SOCK "tcp://127.0.0.1:9001"

#define SW 2500
#define SH 1300

const int LAYER1[3] = {300, 62, 64};
const int LAYER2[3] = {148, 29, 64};
const int LAYER3[3] = {72, 13, 64};
const int LAYER4[3] = {34, 5, 64};
const int LAYER5[3] = {15, 1, 64};

const string JSON_FILE_NAME[5] = {
    "conv1.json",
    "conv2.json",
    "conv3.json",
    "conv4.json",
    "conv5.json"
};

enum VIEWMODE {
    _2D = -1,
    _3D = 1
};
