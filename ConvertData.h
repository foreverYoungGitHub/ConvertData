//
// Created by xileli on 10/5/16.
//

#ifndef CONVERTDATA_CONVERTDATA_H
#define CONVERTDATA_CONVERTDATA_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace cv;

class ConvertData {

public:
	//Constructor function
	ConvertData();
	ConvertData(std::vector<string> params);

	//Deconstructor function
    ~ConvertData();

    //the interface function
    bool run();

    //the ture function generate sample
    bool generate_sample();

    //generate the positive sample
    bool generate_positive();

    //generate the negative sample
    bool generate_negative();

    //read the img path, face number, face rectangle and img
    bool file_list_read();
    bool file_list_read(string path);
    bool img_path_read(int i);
    bool img_path_read(string path);
    bool num_read(int i);
    bool num_read(string path);
    bool rect_read(int i);
    bool rect_read(string path);
//    bool img_read(int i);
    bool img_read(string path);

    //convert one element(path, num, rect, params) to the needed format
    string img_path_convert(string path);
    int num_convert(string num);
    Rect rect_convert(string rect);

    //write the positive sample or the negative sample
    bool sample_write(int i);
    Mat crop(Mat img, Rect rect);
//    bool positive_write(int i);
//    bool negative_write(int i);
    vector<Rect> get_negative(Mat img, vector<Rect> rect, float threshold_);
    bool img_write(string path, Mat img);
    bool txt_init();

    //Create one relative folder for the image
    bool create_folder();
    bool create_folder(string dir_path);

    //IoM alg
    float IoM(Rect rect_1, Rect rect_2);

    //variable
public:
    vector<string> params_; // 0 means the path for the txt file. 1 means the path for the img file. 2 means the path for the write files and txt folder
    vector<string> file_list_;
    vector<int> num_;
    vector<vector<Rect>> rect_;
    vector<string> img_path_;
//    string cur_img_path_;
    //vector<Mat> img_;
    ofstream txtfile_train_, txtfile_val_;
    int state_, txt_switch_;
    Mat cur_img_;
    float threshold_ = 0.1;












};


#endif //CONVERTDATA_CONVERTDATA_H
