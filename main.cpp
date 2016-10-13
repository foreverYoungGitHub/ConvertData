#include <iostream>
#include "ConvertData.h"
#include "DeletePath.h"

int main() {
//    vector<string> params = {
//            "/home/xileli/Documents/dateset/AFW/v1/",
//            "/home/xileli/Documents/dateset/AFW/WIDER_train/images/",
//            "/home/xileli/Documents/dateset/AFW/converData/"
//    };
//
//    ConvertData convertdata(params);
//    convertdata.run();

    vector<string> params = {
            "/home/xileli/Documents/dateset/AFW/converData/",
            "/home/xileli/Documents/dateset/AFW/converData/train.txt",
            "/home/xileli/Documents/dateset/AFW/converData/val.txt"
    };

    DeletePath delete_path(params);
    delete_path.run();

    return 0;
}