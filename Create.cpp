#include <iostream>
#include "picojson.h"
#include "Create.hpp"
#include "Write.hpp"

using namespace std;
using namespace picojson;

void Create::chara(){
    cout << "キャラクター名を入力してください" << endl << ">>>";
    cin >> name ;
    cout << "性別を入力してください : man / woman" << endl << ">>>";
    while (true){
        cin >> sexual;
        if (sexual == "man" or sexual == "woman"){
            break;
        }
        cout << "man / woman で入力してください" << endl << ">>>";
    }
    fs.open("resorse/job.json", ios::binary);
    fs >> val;
    fs.close();
    jobs = val.get<picojson::object>()["jobs_list"].get<picojson::array>();
    for (const auto& e: jobs){
        arr.push_back(e.get<std::string>());
    }
    cout << "職業を選択してください" << endl;
    count = 1;
    for (string s:arr){
        cout << count << " / " << s << endl;
        count++;
    }
    cout << endl << ">>>";
    while (true){
        cin >> job_num;
        if (0 < job_num < count){
            job = arr[job_num - 1];
            break;
        }
        cout << "入力された値が不正です" << endl << ">>>"; 
    }
    picojson::object user;
    picojson::object root;
    picojson::object abilit;
    double money = 0;
    double cool = 10;
    double lv = 1;
    user.insert(make_pair("name", picojson::value(name)));
    user.insert(make_pair("job", picojson::value(job)));
    user.insert(make_pair("sexual", picojson::value(sexual)));
    user.insert(make_pair("money", picojson::value(money)));
    user.insert(make_pair("cool_time", picojson::value(cool)));
    user.insert(make_pair("Lv", value(lv)));
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
    fs >> val;
    fs.close();
    picojson::array abilitys = val.get<picojson::object>()
                                [ability].get<picojson::array>();
    vector<object> arr;
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