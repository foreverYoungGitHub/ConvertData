//
// Created by xileli on 10/5/16.
//

#include "ConvertData.h"


void rect_read()
{
    for(int i=0; i<file_list_.size(); i++)
    {
        string rec_read_path = path + file_list_[i] + ".txt";
        vector<Rect> cur_rects;
        string line;
        Rect cur_rect;
        ifstream rec_read(rec_read_path);
        while(!rec_read.eof())
        {
            getline(rec_read, line);
            if(line == "")
                continue;
            cur_rect = convert_rect(line);
            cur_rects.push_back(cur_rect);
        }
        rect_.push_back(cur_rects);
    }
}

void num_read(string headpath)
{
    for(int i=0; i<file_list_.size(); i++)
    {
        string num_read_path = path + file_list_[i] + "_head_num.txt";
        vector<int> cur_nums;
        string line;
        int cur_num;
        ifstream num_read(num_read_path);
        while(!num_read.eof())
        {
            getline(num_read, line);
            if(line == "")
                continue;
            cur_num = convert_num(line);
            cur_nums.push_back(cur_num);

        }
        num_.push_back(cur_nums);
    }
}

void img_path_read(string headpath)
{
    for(int i=0; i<file_list_.size(); i++)
    {
        string img_read_path = headpath + file_list_[i] + "_img_path.txt";
        vector<string> cur_img_pathes;
        string line;
        ifstream img_path_read(img_read_path);
        while(!img_path_read.eof())
        {
            getline(img_path_read, line);
            if(line == "")
                continue;
            cur_img_pathes.push_back(line);
        }
        path_.push_back(cur_img_pathes);
    }
}


bool ConvertData::img_path_read(string headpath, int i)
{
    string img_read_path = headpath + file_list_[i] + "_img_path.txt";
    vector<string> cur_img_pathes;
    string line;
    ifstream img_path_read(img_read_path);
    while(!img_path_read.eof())
    {
        getline(img_path_read, line);
        if (line == "")
            continue;
        cur_img_pathes.push_back(line);
    }
    path_ = cur_img_pathes;
    return true;
}


//Create one relative folder for the image
bool ConvertData::create_folder(string dir_path)
{
    boost::filesystem::path dir(dir_path);
    if(boost::filesystem::create_directory(dir))
    {
        cout<<"Success To Create Folder : "<< dir_path << endl;
        return true;
    }
    else
    {
        cout<<"Fail to Create Folder : "<< dir_path << endl;
        return false;
    }
}

vector<Mat> img_Mat_read(string headpath_img, int i)
{

    vector<Mat> cur_imgs;
    Mat cur_img;
    for(int j=0; j<afw_face_path_[i].size(); j++)
    {
        string img_path = headpath_img + mid_file_list_[i] + afw_face_path_[i][j];
        cur_img = imread(img_path);
        cur_imgs.push_back(cur_img);
    }
    return cur_imgs;
}