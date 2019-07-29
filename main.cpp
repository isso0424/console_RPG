#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include "picojson.h"
#include "Create.hpp"
#include <windows.h>
#include <filesystem>
#include <sys/stat.h>
#include <typeinfo>
#include "Place.hpp"
#include "Home.hpp"
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
        cout << "�L�����N�^�[�t�@�C��������܂���\n�L�����N�^�[�t�@�C�����쐬���܂�";
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
        cout << "�L�����N�^�[�f�[�^������܂���\n�V�K�L�����N�^�[�𐧍삵�܂�"<<endl;
        Create obj;
        obj.chara();
    }
    fstream fs;
    fs.open("resorse/chara.json");
    fs >> val;
    fs.close();
    cout << "�悤����" << val.get<picojson::object>()["name"].get<string>() << "����" << endl;
    Home home;
    home.home();
    return 0;
}
