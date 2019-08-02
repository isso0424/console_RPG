#include <iostream>
#include "picojson.h"
#include "maps.hpp"
#include <fstream>

using namespace std;
using namespace picojson;

void Maps::move_field(int map_id){
    fs.open("resorse/map.json");
    fs >> val;
    fs.close();
    picojson::array map_list = val.get<picojson::object>()["maps"].get<picojson::array>();
    int id;
    for (value e : map_list){
        id = e.get<picojson::object>()["id"].get<double>();
        if (id == map_id){
            mapo = e;
            break;
        }
    }
    cout << mapo.get<object>()["name"].get<string>() << "の情報を読み込んでいます" << endl;
    monstar_list = mapo.get<object>()["monstars"].get<picojson::array>();
    for (auto e: monstar_list){
        monstars.push_back(e.get<string>());
    }
    
}