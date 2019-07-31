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
    void over_write(vector<string> c_strings, vector<double> c_float, vector<bool> bools);// bool c_abi, bool c_cool, bool c_Lv, bool c_money, bool c_status, bool c_atk, bool c_def, bool c_hp, bool c_int, bool c_mp, bool c_pow
private:
    ifstream fs;
    picojson::value val,val2;
    std::vector<picojson::object> arr;
    unordered_map<string, double> pro_float;
    unordered_map<string, string> pro_string;
    vector<string> abi_name;
    tuple<unordered_map<string, string>, vector<string>> load_string();
    unordered_map<string, double> load_float();
    picojson::object user;
    picojson::object abilitys;
    picojson::object status;
    picojson::object effect;
};

#endif