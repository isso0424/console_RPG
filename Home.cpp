#include "Home.hpp"
#include "picojson.h"
#include <fstream>
#include "Place.hpp"

using namespace std;

void Home::checkstatus(){
    fstream fs;
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
    std::vector<std::string> choice{"出発", "ショップ", "各種ステータス確認","職業コマンド","探検度確認", "セーブ", "ゲーム終了"};
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
        case 7: //ゲーム終了
            return;
            break;
        default:
            break;
        }
    }
}