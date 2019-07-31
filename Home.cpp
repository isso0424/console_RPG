#include "Home.hpp"
#include "picojson.h"
#include <fstream>
#include "Place.hpp"
#include <ostream>
#include <windows.h>
#include "Create.hpp"
#include "Write.hpp"
using namespace std;

void Home::job_command(){
    fs.open("resorse/chara.json");
    fs >> val;
    fs.close();
    string job = val.get<picojson::object>()["job"].get<string>();
    double cool = val.get<picojson::object>()["cool_time"].get<double>();
    fs.open("resorse/job.json");
    fs >> val;
    fs.close();
    picojson::object command = val.get<picojson::object>()["jobs"].get<picojson::object>()[job].get<picojson::object>()["job_command"].get<picojson::object>();
    if (cool == 0){
        cout << command["name"].get<string>() << "を使用します" << endl;
        string kind = command["type"].get<string>();
        if (kind == "make"){
            fs.open("resorse/chara.json");
            fs >> val;
            fs.close();
            Write write;
            double new_cool = 10;
            write.over_write({"vegetable"}, {10}, {false, true, false, false, false, false, false, false, false, false, false, true});
            picojson::array item_list = val.get<picojson::object>()["item_list"].get<picojson::array>();
            item_list.push_back(picojson::value(command["reward"].get<string>()));  
        }
    }
    else{
        cout << "クールタイム中です" << endl;
    }
}

void Home::checkstatus(){
    fs.open("resorse/chara.json");
    picojson::value val;
    fs >> val;
    fs.close();
    cout << "各種ステータス" << endl << "###################################################" << endl;
    cout << "名前 : " << val.get<picojson::object>()["name"].get<string>() << endl;
    cout << "所持金 : " << val.get<picojson::object>()["money"].get<double>() << endl;
    cout << "職業 : " << val.get<picojson::object>()["job"].get<string>() << endl;
    picojson::object status = val.get<picojson::object>()["status"].get<picojson::object>();
    cout << "HP : " << status["hp"].get<double>() << endl;
    cout << "MP : " << status["mp"].get<double>() << endl;
    cout << "攻撃力 : " << status["atk"].get<double>() << endl;
    cout << "防御力 : " << status["def"].get<double>() << endl;
    cout << "知性 : " << status["int"].get<double>() << endl;
    cout << "精神力 : " << status["pow"].get<double>() << endl;
    cout << "#### アビリティリスト ####" << endl;
    
    picojson::array abilitys = val.get<picojson::object>()["abilitys"].get<picojson::array>();
    for (picojson::value e : abilitys){
        cout << "アビリティ名" << e.get<picojson::object>()["name"].get<string>() << endl;
        cout << "種類" << e.get<picojson::object>()["kind"].get<string>() << endl;
        cout << "効果" << e.get<picojson::object>()["effect"].get<picojson::object>()["name"].get<string>() << endl;
    }
    cout << "###################################################" << endl;
}

int Home::menu(){
    count = 1;
    std::vector<std::string> choice{"出発", "ショップ", "各種ステータス確認","職業コマンド","探検度確認", "ゲーム終了"};
    cout << "めにゅう" << endl <<"###################################################" << endl;
    for (std::string cho : choice){
        cout << count << "/" << cho << " ";
        count++;
        if (count % 3 == 0){
            cout << endl;
        }
    }
    cout << endl << "###################################################" << endl;
    while(true){
        int chose;
        cin >> chose;
        if (0 < chose < count){
            return chose;
        }
    }
}

void Home::home(){
    while(true){
        cout << endl <<"現在地 : home" << endl;
        int action = menu();
        switch (action)
        {
        case 1: //出発
            break;
        case 2: //ショップ
            break;
        case 3:
            checkstatus();
            break;
        case 4:
            job_command();
            break;
        case 6: //ゲーム終了
            return;
            break;
        default:
            break;
        }
    }
}
