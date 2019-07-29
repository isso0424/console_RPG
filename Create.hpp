#ifndef _CREATE_H_
#define _CREATE_H_
#include <string>
#include "Write.hpp"
#include "picojson.h"
#include <fstream>
#include <string>
using namespace std;
using namespace picojson;
class Create{
public:
    void chara();
private:
    string name;
    string sexual;
    string job;
    int job_num;
    int count;
    value val;
    ifstream fs;
    picojson::array jobs;
    vector<string> arr;
    string s;
};

#endif //_CREATE_H_
