#ifndef _WRITE_H_
#define _WRITE_H_
#include "picojson.h"
#include <string>
#include <fstream>
using namespace std;
class Write
{
public:
    void chara(string name, string job, string sexual);
private:
    ifstream fs;
    picojson::value val,val2;
    std::vector<picojson::object> arr;
};

#endif