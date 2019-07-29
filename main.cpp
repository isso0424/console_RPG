#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "picojson.h"
#include "Create.hpp"
#include <windows.h>
#include <filesystem>
#include <sys/stat.h>
#ifndef UNICODE
    typedef std::string String;
#else
    typedef std::wstring String;
#endif

using namespace std;
using namespace picojson;

bool checkFileExistence(const std::string& str){
    std::ifstream ifs(str);
    return ifs.is_open();
}

int main(){
    std::string path = "resorse\\chara.json";
    char dir[255];
    GetCurrentDirectory(255, dir);
    cout << dir << endl;
    if (! checkFileExistence(path)){
        cout << "キャラクターファイルがありません\nキャラクターファイルを作成します";
        ofstream("resorse\\chara.json");
        cout << "create";
    }
    picojson::value val;
    string dirs = dir;
    string chara_dir = dirs + "\\resorse\\chara.json";
    struct stat s;
    int ret;
    ret = stat("resorse/chara.json", &s);
    /*
    std::ifstream fs;
    fs.open("resorse/chara.json");
    assert(fs);
    fs >> val;
    fs.close();
    cout << val << endl;
    */
    
    if (s.st_size == 0){
        cout << "キャラクターデータがありません\n新規キャラクターを制作します"<<endl;
        Create obj;
        obj.chara();
    }
    cout << "どのキャラを使いますか" << endl;
    ifstream fs;
    fs.open("resorse/chara.json", ios::binary);
    picojson::value val2;
    fs >> val2;
    fs.close();
    picojson::object charas = val2.get<picojson::object>();
    int count = 1;
    std::vector<string> chara_list;
    for (const auto& e : charas){
        cout << charas["name"].get<string>();
        count++;
        chara_list.push_back(charas["name"].get<string>());
    }
    string chara_name;
    vector<string>::iterator siter = find(
        chara_list.begin(),chara_list.end(),chara_name
    );
    while (true){
        cout << "\n>>>";
        cin >> chara_name;
        if (siter != chara_list.end()){
            break;
        }
    }
    return 0;
}
