#ifndef _WRITE_H_
#define _WRITE_H_
#include "picojson.h"
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;
class Write
{
public:
    void chara(string name, string job, string sexual, string new_item, vector<string> now_list, vector<double> now_status, double money, double cool, bool over_write);
    void over_write_cool();
private:
    ifstream fs;
    picojson::value val,val2;
    std::vector<picojson::object> arr;
    map<string, double> pro_float;
    unordered_map<string, string> pro_string;

    unordered_map<string, string> load_string();
    map<string, double> load_float();
};

#endif