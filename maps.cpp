#include <iostream>
#include "picojson.h"
#include "maps.hpp"
#include <fstream>

using namespace std;
using namespace picojson;

void Maps::in_field(vector<string> monstars, int id_a, picojson::array map_list){
    fs.open("resorse/progress.json");
    fs >> val;
    fs.close();
    cout << "ここで出現するモンスターは" << endl;
    for (string mon : monstars){
        cout << mon << endl;
    }
    cout << "です" << endl;
    int id;

    for (value e : map_list){
        id = e.get<picojson::object>()["id"].get<double>();
        if (id == id_a){
            mapo = e;
            break;
        }
    }
    string id_s = to_string(id_a);
    int progress = val.get<object>()[id_s].get<object>()["progress"].get<double>();
    while(true){
        cout << "##############################################" << endl;
        cout << "1/進む  2/帰る(進行度が10%減ります" << endl;
        cout << "##############################################" << endl;
        cin >> action;
        if (0 < action < 3){
            switch (action)
            {
            case 1:
                
                break;
            case 2:
                break;
            default:
                break;
            }
            break;
        }
    }
}

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
    cout << mapo.get<object>()["name"].get<string>() << "のデータを読み込んでいます" << endl;
    monstar_list = mapo.get<object>()["monstars"].get<picojson::array>();
    for (auto e: monstar_list){
        monstars.push_back(e.get<string>());
    }
    in_field(monstars, id, map_list);
}