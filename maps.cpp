#include <iostream>
#include "picojson.h"
#include "maps.hpp"
#include <fstream>
#include "Write.hpp"

using namespace std;
using namespace picojson;

int Maps::load_progress(int map_id){
    fs.open("resorse/progress.json");
    fs >> val;
    fs.close();
    pros = val.get<object>()["progress"].get<picojson::array>();
    for (auto e : pros){
        progresses.push_back(e.get<double>());
    }
    progress = progresses[map_id];
    return progress;
}

void Maps::in_field(vector<string> monstars, int id_a, picojson::array map_list){
    fs.open("resorse/progress.json");
    fs >> val;
    fs.close();
    cout << "ここで出現するモンスターは" << endl;
    for (string mon : monstars){
        cout << mon << endl;
    }
    cout << "です" << endl;
    progress = load_progress(id_a);
    while(true){
        
        cout << "##############################################" << endl;
        cout << "1/進む  2/帰る(進行度が10%減ります  現在の進行度 : " << progress << "%" << endl;
        cout << "##############################################" << endl;
        cin >> action;
        if (0 < action < 3){
            switch (action)
            {
            case 1:
                writer.over_write_progress(progress + 3, id_a);
                progress = load_progress(id_a);
                cout << "現在の進行度 : " << progress << "%" << endl;
                break;
            case 2:
                progress = load_progress(id_a);
                
                if (progress <= 10){
                writer.over_write_progress(0, id_a);
                }else{
                    writer.over_write_progress(progress - 10, id_a);
                }
                progress = load_progress(id_a);
                cout << "現在の進行度 : " << progress << "%" << endl;
                break;
            default:
                break;
            }
            if (action == 2){
                break;
            }
        }
        progress = load_progress(id_a);
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