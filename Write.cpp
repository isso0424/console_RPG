#include <string>
#include "picojson.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Write.hpp"
#include <unordered_map>

using namespace std;
using namespace picojson;

void Write::chara(string name, string job, string sexual, string new_item, 
vector<string> now_list = {}, vector<double> now_status = {}, double money = 0, 
double cool = 10, bool over_write = false)
{
    picojson::object user;
    picojson::object root;
    picojson::object abilit;
    user.insert(make_pair("name", picojson::value(name)));
    user.insert(make_pair("job", picojson::value(job)));
    user.insert(make_pair("sexual", picojson::value(sexual)));
    user.insert(make_pair("place", picojson::value("home")));
    user.insert(make_pair("money", picojson::value(money)));
    user.insert(make_pair("cool_time", picojson::value(cool)));
    fs.open("resorse/job.json");
    fs >> val;
    fs.close();
    picojson::object status = val.get<picojson::object>()
                                ["jobs"].get<picojson::object>()
                                [job].get<picojson::object>()
                                ["initial_value"].get<picojson::object>();
    string ability = val.get<picojson::object>()
                                ["jobs"].get<picojson::object>()
                                [job].get<picojson::object>()
                                ["ability"].get<std::string>();
    picojson::array items;
    user.insert(make_pair("item_list", items));
    user.insert(make_pair("status", status));
    user.insert(make_pair("ability_set", ability));
    fs.open("resorse/ability.json");
    fs >> val2;
    fs.close();
    picojson::array abilitys = val2.get<picojson::object>()
                                [ability].get<picojson::array>();
    for (const auto& e : abilitys){
        arr.push_back(e.get<picojson::object>());
    }
    picojson::array ar;
    for (object e : arr){
        int a = e["Lv"].get<double>();
        if (a == 1){
            abilit.insert(make_pair(e["name"].get<string>(), e));
            ar.push_back(value(e));
        }
    }
    user.insert(make_pair("abilitys", ar));
    ofstream ofs("resorse/chara.json");
    ofs << picojson::value(user).serialize(true);
}

unordered_map<string, string> Write::load_string(){
    fs.open("resorse/chara.json");
    fs >> val;
    fs.close();
    object obj = val.get<object>();
    pro_string["name"] = obj["name"].get<string>();
    pro_string["job"] = obj["job"].get<string>();
    pro_string["sexual"] = obj["sexual"].get<string>();
    pro_string["ability_set"] = obj["ability_set"].get<string>();
    picojson::array abilitys = obj["abilitys"].get<picojson::array>();
    for (picojson::value e : abilitys){
        pro_string["abi_name"] = e.get<object>()["name"].get<string>();
        pro_string["kind"] = e.get<object>()["kind"].get<string>();
        picojson::object obj2 = e.get<object>()["effect"].get<object>();
        pro_string["eff_name"] = obj2["name"].get<string>();
        pro_string["eff_size"] = obj2["effect_size"].get<double>();
    }
    return pro_string;
}