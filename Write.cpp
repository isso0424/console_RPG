#include <string>
#include "picojson.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Write.hpp"
#include <unordered_map>
#include <windows.h>

using namespace std;
using namespace picojson;

void Write::over_write_progress(double progress, int map_id){
    fs.open("resorse/progress.json");
    fs >> val;
    fs.close();
    DeleteFileA("resorse/progress.json");
    picojson::array progresses = val.get<object>()["progress"].get<picojson::array>();
    picojson::array progress_list;
    int count = 0;
    for (auto e: progresses){
        if (map_id == count){
            progress_list.push_back(picojson::value(progress));
        }
        else {
            progress_list.push_back(value(e.get<double>()));
        }
    }
    ofstream ofs("resorse/progress.json");
    picojson::object root;
    root.insert(make_pair("progress", progress_list));
    ofs << value(root).serialize(true) << endl;
}

tuple<unordered_map<string, string>, vector<string>> Write::load_string(){
    fs.open("resorse/chara.json");
    fs >> val;
    fs.close();
    picojson::object obj = val.get<object>();
    pro_string["name"] = obj["name"].get<string>();
    pro_string["job"] = obj["job"].get<string>();
    pro_string["sexual"] = obj["sexual"].get<string>();
    pro_string["ability_set"] = obj["ability_set"].get<string>();
    picojson::array abilitys = obj["abilitys"].get<picojson::array>();
    for (picojson::value e : abilitys){
        string abi = e.get<object>()["name"].get<string>();
        abi_name.push_back(e.get<object>()["name"].get<string>());
        pro_string[abi + "_kind"] = e.get<object>()["kind"].get<string>();
        picojson::object obj2 = e.get<object>()["effect"].get<object>();
        pro_string[abi + "_eff_name"] = obj2["name"].get<string>();
    }
    return forward_as_tuple(pro_string, abi_name);
}


unordered_map<string, double> Write::load_float(){
    fs.open("resorse/chara.json");
    fs >> val;
    fs.close();
    picojson::object obj = val.get<object>();
    pro_float["Lv"] = obj["Lv"].get<double>();
    pro_float["cool_time"] = obj["cool_time"].get<double>();
    pro_float["money"] = obj["money"].get<double>();
    picojson::object status = obj["status"].get<object>();
    pro_float["atk"] = status["atk"].get<double>();
    pro_float["def"] = status["def"].get<double>();
    pro_float["hp"] = status["hp"].get<double>();
    pro_float["int"] = status["int"].get<double>();
    pro_float["mp"] = status["mp"].get<double>();
    pro_float["pow"] = status["pow"].get<double>();
    picojson::array abilitys = obj["abilitys"].get<picojson::array>();
    for (auto e: abilitys){
        string key = e.get<object>()["effect"].get<object>()["name"].get<string>();
        pro_float[key + "_Lv"] = e.get<object>()["Lv"].get<double>();
        pro_float[key + "_eff_size"] = e.get<object>()["effect"].get<object>()["effect_size"].get<double>();
    }
    return pro_float;
}

void Write::over_write(vector<string> c_strings = {}, vector<double> c_float = {}, vector<bool> bools = {}){
    // {abi, cool, Lv, money, status, atk, def, hp, int, mp, pow}
    fs.open("resorse/chara.json");
    fs >> val;
    fs.close();
    picojson::object obj = val.get<object>();
    picojson::array abi_list;
    picojson::object status;
    tie(pro_string, abi_name) = load_string();
    pro_float = load_float();
    auto itr = c_strings.begin();
    auto itr2 = c_float.begin();
    auto itr3 = bools.begin();
    DeleteFileA("resorse/chara.json");
    user.insert(make_pair("name", value(pro_string["name"])));
    user.insert(make_pair("job", value(pro_string["job"])));
    user.insert(make_pair("sexual", value(pro_string["sexual"])));
    user.insert(make_pair("ability_set", value(pro_string["ability_set"])));
    if (*itr3){//string{name, kind, eff_name} float{Lv, size}
        picojson::object abilitys {};
        picojson::object effect {};
        abilitys.insert(make_pair("name", value(*itr)));
        itr++;
        abilitys.insert(make_pair("kind", value(*itr)));
        itr++;
        abilitys.insert(make_pair("Lv", value(*itr2)));
        itr ++;
        effect.insert(make_pair("name", value(*itr)));
        itr++;
        effect.insert(make_pair("effect_size",value{*itr2}));
        itr2++;
        abilitys.insert(make_pair("effect", effect));
        abi_list.push_back(value(abilitys));
    }
    itr3++;
    for (auto na : abi_name){
        picojson::object abilitys {};
        picojson::object effect {};
        abilitys.insert(make_pair("name", value(na)));
        abilitys.insert(make_pair("kind", value(pro_string[na+"_kind"])));
        abilitys.insert(make_pair("Lv", value(pro_float[na + "_Lv"])));
        effect.insert(make_pair("name", value(pro_string[na + "_eff_name"])));
        effect.insert(make_pair("effect_size",value{pro_float[na + "_eff_size"]}));
        abilitys.insert(make_pair("effect", effect));
        abi_list.push_back(value(abilitys));
    }
    user.insert(make_pair("abilitys", abi_list));
    if (*itr3) {//float{cool}
        user.insert(make_pair("cool_time", value(*itr2)));
        itr2++;
    } else {
        user.insert(make_pair("cool_time", value(pro_float["cool_time"])));
    }
    itr3++;
    if (*itr3) {//float{Lv}
        user.insert(make_pair("Lv", value(*itr2)));
        itr2++;
    } else {
        user.insert(make_pair("Lv", value(pro_float["Lv"])));
    }
    itr3++;
    if (*itr3){//float{money}
        user.insert(make_pair("money", value(*itr2)));
        itr2++;
    } else {
        user.insert(make_pair("money", value(pro_float["money"])));
    }
    itr3++;
    if (*itr3){
        itr3++;
        if (*itr3){
        status.insert(make_pair("atk", value(*itr2)));
        itr2++;
        }else{
                status.insert(make_pair("atk", value(pro_float["atk"])));
        }
        itr3++;
        if (*itr3){
        status.insert(make_pair("def", value(*itr2)));
        itr2++;
        }
        else{
            status.insert(make_pair("def", value(pro_float["def"])));
        }itr3++;
        if (*itr3){
            status.insert(make_pair("hp", value(*itr2)));
        itr2++;
        }
        else{
        status.insert(make_pair("hp", value(pro_float["hp"])));
        }itr3++;
        if(*itr3){
            status.insert(make_pair("int", value(*itr2)));
        itr2++;
        }
        else{
            status.insert(make_pair("int", value(pro_float["int"])));
        }itr3++;
        if(*itr3){
            status.insert(make_pair("mp", value(*itr2)));
        itr2++;
        }
        else{
            status.insert(make_pair("mp", value(pro_float["mp"])));
        }itr3++;
        if(*itr3){
            status.insert(make_pair("pow", value(*itr2)));
        itr2++;
        }
        else{
            status.insert(make_pair("pow", value(pro_float["pow"])));
        }itr3++;
        user.insert(make_pair("status", value(status)));
    } else {
        status.insert(make_pair("atk", value(pro_float["atk"])));
        status.insert(make_pair("def", value(pro_float["def"])));
        status.insert(make_pair("hp", value(pro_float["hp"])));
        status.insert(make_pair("int", value(pro_float["int"])));
        status.insert(make_pair("mp", value(pro_float["mp"])));
        status.insert(make_pair("pow", value(pro_float["pow"])));
        user.insert(make_pair("status", value(status)));
        int a = 0;
        while (a != 7){
            *itr3++;
            a++;
        }
    }
    picojson::array item_list = obj["item_list"].get<picojson::array>();
    if (*itr3){
        item_list.push_back(value(*itr));
        cout << *itr;
    }
    user.insert(make_pair("item_list", item_list));
    ofstream("resorse/chara.json");
    ofstream ofs("resorse/chara.json");
    ofs << value(user).serialize(true);
}