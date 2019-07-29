#include <string>
#include "picojson.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Write.hpp"

using namespace std;
using namespace picojson;

void Write::chara(string name, string job, string sexual){
    picojson::object user;
    picojson::object root;
    picojson::object abilit;
    user.insert(make_pair("name", picojson::value(name)));
    user.insert(make_pair("job", picojson::value(job)));
    user.insert(make_pair("sexual", picojson::value(sexual)));
    user.insert(make_pair("place", picojson::value("home")));
    double b = 0;
    user.insert(make_pair("money", picojson::value(b)));
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