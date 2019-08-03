#include <iostream>
#include "picojson.h"
#include "maps.hpp"
#include <fstream>
#include "Write.hpp"

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
    picojson::array pros = val.get<object>()["progress"].get<picojson::array>();
    std::vector<double> progresses;
    for (auto e : pros){
        progresses.push_back(e.get<double>());
    }
    int progress = progresses[id_a];
    vector<double> progresses2;
    while(true){
        
        cout << "##############################################" << endl;
        cout << "1/進む  2/帰る(進行度が10%減ります  現在の進行度 : " << progress << "%" << endl;
        cout << "##############################################" << endl;
        cin >> action;
        if (0 < action < 3){
            fs.open("resorse/progress.json");
            fs >> val2;
            fs.close();
            auto progresses = vector<double>{};
            auto progresses2 = vector<double>{};
            switch (action)
            {
            case 1:
                writer.over_write_progress(progress + 3, id_a);
                pros = val2.get<object>()["progress"].get<picojson::array>();
                for (auto e : pros){
                    progresses.push_back(e.get<double>());
                }
                progress = progresses[id_a];
                cout << "現在の進行度 : " << progress << "%" << endl;
                break;
            case 2:
                pros = val2.get<object>()["progress"].get<picojson::array>();
                for (auto e : pros){
                    progresses.push_back(e.get<double>());
                }
                progress = progresses[id_a];
                
                if (progress <= 10){
                writer.over_write_progress(0, id_a);
                }else{
                    writer.over_write_progress(progress - 10, id_a);
                }
                pros = val2.get<object>()["progress"].get<picojson::array>();
                for (auto e : pros){
                    progresses2.push_back(e.get<double>());
                }
                progress = progresses2[id_a];
                cout << "現在の進行度 : " << progress << "%" << endl;
                break;
            default:
                break;
            }
            if (action == 2){
                break;
            }
        }
        fs.open("resorse/progress.json");
        fs >> val3;
        fs.close();
        pros = val3.get<object>()["progress"].get<picojson::array>();
        auto progresses = vector<double>{};
        for (auto e : pros){
            progresses.push_back(e.get<double>());
        }
        progress = progresses[id_a];
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