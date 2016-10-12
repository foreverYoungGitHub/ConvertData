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

    if(generate_positive())
    {
        cout<<"Success to write positive sample"<<endl;
    }
    else
    {
        cout<<"Fail to write positive sample"<<endl;
        return false;
    }
    if(generate_negative())
    {
        cout<<"Success to write negative sample"<<endl;
    }
    else
    {
        cout<<"Fail to write negative sample"<<endl;
        return false;
    }

    return true;
}

bool ConvertData::generate_positive()
{
    state_ = 1;
    return generate_sample();
}

bool ConvertData::generate_negative()
{
    state_ = 0;
    return generate_sample();
}

bool ConvertData::generate_sample()
{
    if(state_ != 0)
    {
        if (!txt_init())
        {
            cout << "Cannot initialize txt file" << endl;
            return false;
        }
    }

    if(!file_list_read())
    {
        cout<<"Cannot read file list"<<endl;
        return false;
    }

    if(!create_folder())
    {
        cout<<"Cannot create folder"<<endl;
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
bool ConvertData::create_folder()
{
    string cur_img_path = params_[2] + to_string(state_) + "/";
    return create_folder(cur_img_path);
}

bool ConvertData::create_folder(string dir_path)
{
    boost::filesystem::path dir(dir_path);
    if(boost::filesystem::is_directory(dir_path))
    {
        cout<<"Folder : "<< dir_path << " is existed" << endl;
        return true;
    }
    else
    {
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
}

bool ConvertData::sample_write(int i)
{
    //create the folder for file list
    string cur_img_path = params_[2] + to_string(state_) + "/" + file_list_[i];
    if(!create_folder(cur_img_path))
        return false;

    for(int j = 0; j < img_path_.size(); j++)
    {
        //read img
        cur_img_path = params_[1] + file_list_[i] + img_path_[j];
        if(img_read(cur_img_path))
        {
            cout << "Cannot open " << cur_img_path << endl;
            continue;
        }

        //create the folder for img
        string img_path = img_path_convert(img_path_[j]) + "/";
        cur_img_path = params_[2] + to_string(state_) + "/" + file_list_[i] + img_path;
        if(!create_folder(cur_img_path))
            return false;


        vector<Rect> cur_rect;
        //write positive
        if(state_ == 1)
        {
            cur_rect = rect_[j];
        }
        //write negative
        if(state_ == 0)
        {
            cur_rect = get_negative(cur_img_, rect_[j], threshold_);
        }

        //write img
        for(int k = 0; k < cur_rect.size(); k++)
        {
            Mat sample = crop(cur_img_, cur_rect[k]);
            if(k % 2 == 0)
            {
                txt_switch_ = 1;
            }
            if(img_write(cur_img_path + to_string(k) + ".jpg", sample))
                continue;
        }
    }

    return true;
}

vector<Rect> ConvertData::get_negative(Mat img, vector<Rect> rect, float threshold)
{
    //approximate the dimension of rect
    int dimension = rect[0].width;
    for(int i=0; i<rect.size(); i++)
    {
        if(dimension < rect[i].width)
            dimension = rect[i].width;
    }


    vector<Rect> negative_rect;
    //
    if(dimension == 0)
    {
        return negative_rect;
    }

    //generate the negative rect

    for(int i = 0, count = 30; i < img.cols - dimension && count >= 0; i += dimension)
    {
        for(int j = 0; j < img.rows - dimension && count >= 0; j += dimension)
        {
            Rect cur_rect(i, j, dimension, dimension);
            float overlap = 0;
            for(int k = 0; k < rect.size(); k++) {
                overlap += IoM(rect[k], cur_rect);
            }
            if (overlap <= threshold)
            {
                negative_rect.push_back(cur_rect);
                count--;
            }
        }
    }
    return negative_rect;
}

bool ConvertData::txt_init()
{
    txtfile_train_.open(params_[2] + "train.txt");
    txtfile_val_.open(params_[2] + "val.txt");
    if(txtfile_val_.is_open()&&txtfile_train_.is_open())
        return true;
    else
        return false;
}

bool ConvertData::img_read(string path)
{
    cur_img_ = imread(path);
    if(cur_img_.rows)
        return false;
    else
        return true;
}

bool ConvertData::img_write(string path, Mat img)
{
    if(imwrite(path, img))
    {
        if(txt_switch_ == 1)
        {
            txtfile_val_ << path << ' ' << state_ << endl;
            cout << "Success to write to val : " << path << endl;
            txt_switch_ = 0;
            return true;
        }
        txtfile_train_ << path << ' ' << state_ << endl;
        cout << "Success to write to train :" << path << endl;
        return true;
    }
    else
    {
        cout << "Fail to write " << path << endl;
        return false;
    }
}

Mat ConvertData::crop(Mat img, Rect rect)
{
    if(rect.x <= 0) rect.x = 0;
    if(rect.y <= 0) rect.y = 0;
    if(img.cols < (rect.x + rect.width)) rect.width = img.cols-rect.x;
    if(img.rows < (rect.y + rect.height)) rect.height = img.rows - rect.y;
    if(rect.width<0)
    {
        rect.x=0;
        rect.width = 0;
    }
    if(rect.height<0)
    {
        rect.y=0;
        rect.height = 0;
    }
    return img(rect);
}

string ConvertData::img_path_convert(string path)
{
    char * cstr = new char[path.length()+1];
    strcpy(cstr, path.c_str());
    char * p = strtok(cstr, ".");
    return p;
}

float ConvertData::IoM(Rect rect_1, Rect rect_2)
{
    int x11 = rect_1.x;
    int y11 = rect_1.y;
    int x12 = rect_1.width+x11;
    int y12 = rect_1.height+y11;
    int x21 = rect_2.x;
    int y21 = rect_2.y;
    int x22 = rect_2.width+x21;
    int y22 = rect_2.height+y22;
    int x_overlap = std::max(0, (std::min(x12, x22) - std::max(x11, x21)));
    int y_overlap = max(0, min(y12, y22) - max(y11, y21));
    int intersection = x_overlap * y_overlap;
    int rect_1_area = (y12 - y11) * (x12 -x11);
    int rect_2_area = (y22 - y21) * (x22 - x21);
    int min_area = min(rect_1_area, rect_2_area);
    float result = intersection * 1.0 /min_area;
    return result;
}