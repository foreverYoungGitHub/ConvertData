//
// Created by xileli on 10/5/16.
//

#ifndef CONVERTDATA_CONVERTDATA_H
#define CONVERTDATA_CONVERTDATA_H

#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace cv;

class ConvertData {
    vector<string> path_;


    bool img_path_read(string headpath, int i);

    //Create one relative folder for the image
    bool create_folder(string dir_path);

    //generate the positive sample
    bool generate_positive();
};


#endif //CONVERTDATA_CONVERTDATA_H
