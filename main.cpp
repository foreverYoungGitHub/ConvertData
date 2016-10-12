#include <iostream>
#include "ConvertData.h"

int main() {
    vector<string> params = {
            "/home/xileli/Documents/dateset/AFW/v1/",
            "/home/xileli/Documents/dateset/AFW/WIDER_train/images/",
            "/home/xileli/Documents/dateset/AFW/converData/"
    };

    ConvertData convertdata(params);
    convertdata.run();

    return 0;
}