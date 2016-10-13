//
// Created by xileli on 10/13/16.
//

#ifndef CONVERTDATA_DELETEPATH_H
#define CONVERTDATA_DELETEPATH_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class DeletePath {

public:
    DeletePath();
    DeletePath(vector<string> params);
    ~DeletePath();

    bool run();

    bool erase_begining();

    int num_; // the num for the input files
    vector<string> params_; // the first one is for the context to delete
};


#endif //CONVERTDATA_DELETEPATH_H
