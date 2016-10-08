//
// Created by xileli on 10/5/16.
//

#include "ConvertData.h"


ConvertData::ConvertData()
{

}

ConvertData::ConvertData(std::vector<string> params)
{
    params_ = params;
}

ConvertData::~ConvertData()
{

}

bool ConvertData::run()
{

    if(generate_sample())
    {
        cout<<"Success Sample"<<endl;
        return true;
    }
    else
    {
        cout<<"Fail to Sample"<<endl;
        return false;
    }

}

//bool ConvertData::generate_positive()
//{
//    return generate_sample(1);
//}
//
//bool ConvertData::generate_negative()
//{
//    return generate_sample(0);
//}

bool ConvertData::generate_sample()
{
    if(!txt_init())
    {
        cout<<"Cannot initialize txt file"<<endl;
        return false;
    }

    if(!file_list_read())
    {
        cout<<"Cannot read file list"<<endl;
        return false;
    }

    for(int i=0; i<file_list_.size(); i++)
    {
        cout<< "Processing " << i << " Sample" << endl;

        if(!num_read(i))
        {
            cout<<"Cannot read num"<<endl;
            return false;
        }

        if(!rect_read(i))
        {
            cout<<"Cannot read rect"<<endl;
            return false;
        }

        if(!img_path_read(i))
        {
            cout<<"Cannot read img path"<<endl;
            return false;
        }

//        if(!img_read(i))
//        {
//            cout<<"Cannot read img "<< cur_img_path_ << endl;
//            return false;
//        }

//        if(!create_folder())
//        {
//            cout<<"Cannot read file list"<<endl;
//            return false;
//        }

        if(!sample_write(i))
        {
            cout<<"Fail to Write Sample"<<endl;
            return false;
        }

//        if(state == 1)
//        {
//            if (!positive_write(i)) {
//                cout << "Fail to Positive Sample" << endl;
//                return false;
//            } else {
//                cout << "Success Positive Sample" << endl;
//                return true;
//            }
//        }
//        else
//        {
//            if(!negative_write(i))
//            {
//                cout<<"Fail to Positive Sample"<<endl;
//                return false;
//            }
//            else
//            {
//                cout<<"Success Positive Sample"<<endl;
//                return true;
//            }
//        }
    }

    return true;
}


bool ConvertData::file_list_read()
{
    return file_list_read(params_[0] + "name_list.txt");
}

bool ConvertData::file_list_read(string path)
{
    ifstream in(path);
    while(!in.eof())
    {
        string line;
        getline(in, line);
        if(line == "")
            continue;
        file_list_.push_back(line);
    }

    if(file_list_.size() != 0)
        return true;
    else
        return false;
}

bool ConvertData::num_read(int i)
{
    return num_read(params_[0] + file_list_[i] + "_head_num.txt");
}

bool ConvertData::num_read(string path)
{
    num_.clear();
    ifstream num_file(path);
    while(!num_file.eof())
    {
        string line;
        getline(num_file, line);
        if(line == "")
            continue;
        int cur_num = num_convert(line);
        num_.push_back(cur_num);
    }

    if(num_.size() != 0)
        return true;
    else
        return false;
}

int ConvertData::num_convert(string num)
{
    return atoi(num.c_str());
}

bool ConvertData::rect_read(int i)
{
    return rect_read(params_[0] + file_list_[i] + ".txt");
}

bool ConvertData::rect_read(string path)
{
    rect_.clear();
    vector<Rect> rect;
    int count = 0;
    ifstream rect_file(path);
    while(!rect_file.eof())
    {
        string line;
        getline(rect_file, line);
        if(line == "")
            continue;
        Rect cur_rect = rect_convert(line);
        rect.push_back(cur_rect);
        if(rect.size() == num_[count])
        {
            rect_.push_back(rect);
            count++;
            rect.clear();
        }
    }

    if(rect_.size() != 0)
        return true;
    else
        return false;
}

Rect ConvertData::rect_convert(string rect)
{
    char * cstr = new char[rect.length()+1];
    strcpy(cstr, rect.c_str());
    char * p = strtok(cstr, ",");
    vector<float> rect_list;
    while(p != 0)
    {
        float pos = atof(p);
        rect_list.push_back(pos);
        p = strtok(NULL, ",");
    }
    return Rect(rect_list[0], rect_list[1], rect_list[2], rect_list[3]);
}

bool ConvertData::img_path_read(int i)
{
    return img_path_read(params_[0] + file_list_[i] + "_img_path.txt");
}

bool ConvertData::img_path_read(string path)
{
    img_path_.clear();
    ifstream img_path_file(path);
    while(!img_path_file.eof())
    {
        string line;
        getline(img_path_file, line);
        if(line == "")
            continue;
        img_path_.push_back(line);
    }

    if(img_path_.size() != 0)
        return true;
    else
        return false;
}

//bool ConvertData::img_read(int i)
//{
//    return img_read(params_[1] + file_list_[i]);
//}
//
//bool ConvertData::img_read(string path)
//{
//    img_.clear();
//    for(int i = 0; i < img_path_.size(); i++)
//    {
//        cur_img_path_ = path + img_path_[i];
//        Mat cur_img = imread(cur_img_path_);
//        if(cur_img.empty())
//            return false;
//        img_.push_back(cur_img);
//    }
//
//    if(img_.size() != 0)
//        return true;
//    else
//        return false;
//}


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

bool ConvertData::positive_write(int i)
{
    for(int j = 0; j < img_path_.size(); j++)
    {
        //read img
        string cur_img_path = params_[1] + file_list_[i] + img_path_[j];
        if(img_read(cur_img_path))
        {
            cout << "Cannot open " << cur_img_path << endl;
            continue;
        }

        if(state_ == 1)
        {
            //create the folder for file list
            cur_img_path = params_[2] + "1/" + file_list_[i];
            create_folder(cur_img_path);
        }
        if(state_ == 0)
        {
            //create the folder for file list
            cur_img_path = params_[2] + "0/" + file_list_[i];
            create_folder(cur_img_path);
        }

        //create the folder for img
        cur_img_path = params_[2] + file_list_[i] + img_path_[j];
        create_folder(cur_img_path);

        //create the folder for img
        cur_img_path = params_[2] + file_list_[i] + img_path_[j];
        create_folder(cur_img_path);

        //write positve
        for(int k = 0; k < num_[j]; k++)
        {
            positive_sample(cur_img_, rect_[j][k]);
            img_write();
        }
    }

}

bool ConvertData::negative_write(int i)
{

}

bool ConvertData::img_read(string path)
{
    cur_img_ = imread(path);
    if(cur_img_.empty())
        return false;
    else
        return true;
}

Mat ConvertData::positive_sample(Mat img, Rect rect)
{
    if(rect.x <= 0) rect.x = 0;
    if(rect.y <= 0) rect.y = 0;
    if(img.cols < (rect.x + rect.width)) rect.width = img.cols-rect.x;
    if(img.rows < (rect.y + rect.height)) rect.height = img.rows - rect.y;
    if(rect.width <= 0) rect.width = 0;
    if(rect.height <= 0) rect.height = 0;
    return img(rect);
}


bool ConvertData::txt_init()
{
    txtfile_.open(params_[0]);
    if(txtfile_.is_open())
        return true;
    else
        return false;
}