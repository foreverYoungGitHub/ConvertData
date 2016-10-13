//
// Created by xileli on 10/13/16.
//

#include "DeletePath.h"

DeletePath::DeletePath()
{
}

DeletePath::DeletePath(vector<string> params)
{
    params_ = params;
}

DeletePath::~DeletePath()
{

}

bool DeletePath::run()
{
    if(erase_begining())
    {
        cout << "Succeed to change txt." << endl;
        return true;
    }
    else
    {
        cout << "Failed to change txt." << endl;
        return false;
    }
}

bool DeletePath::erase_begining()
{
    //find the length of the delete context
    int length = params_[0].length();

    for(int i = 1; i < params_.size(); i++)
    {
        ifstream ifile(params_[i]);
        ofstream ofile(params_[i] + '_');

        while(!ifile.eof())
        {
            string line;
            getline(ifile, line);
            if(line == "")
                continue;
            line.erase(line.begin(), line.begin() + length);
            ofile << line << endl;
            cout << "Succeed to change the path." << endl;
        }

        ifile.close();
        ofile.close();
    }

    return true;
}