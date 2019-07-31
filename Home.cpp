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
        cout << command["name"].get<string>() << "���g�p���܂�" << endl;
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
        cout << "�N�[���^�C�����ł�" << endl;
    }
}

void Home::checkstatus(){
    fs.open("resorse/chara.json");
    picojson::value val;
    fs >> val;
    fs.close();
    cout << "�e��X�e�[�^�X" << endl << "###################################################" << endl;
    cout << "���O : " << val.get<picojson::object>()["name"].get<string>() << endl;
    cout << "������ : " << val.get<picojson::object>()["money"].get<double>() << endl;
    cout << "�E�� : " << val.get<picojson::object>()["job"].get<string>() << endl;
    picojson::object status = val.get<picojson::object>()["status"].get<picojson::object>();
    cout << "HP : " << status["hp"].get<double>() << endl;
    cout << "MP : " << status["mp"].get<double>() << endl;
    cout << "�U���� : " << status["atk"].get<double>() << endl;
    cout << "�h��� : " << status["def"].get<double>() << endl;
    cout << "�m�� : " << status["int"].get<double>() << endl;
    cout << "���_�� : " << status["pow"].get<double>() << endl;
    cout << "#### �A�r���e�B���X�g ####" << endl;
    
    picojson::array abilitys = val.get<picojson::object>()["abilitys"].get<picojson::array>();
    for (picojson::value e : abilitys){
        cout << "�A�r���e�B��" << e.get<picojson::object>()["name"].get<string>() << endl;
        cout << "���" << e.get<picojson::object>()["kind"].get<string>() << endl;
        cout << "����" << e.get<picojson::object>()["effect"].get<picojson::object>()["name"].get<string>() << endl;
    }
    cout << "###################################################" << endl;
}

int Home::menu(){
    count = 1;
    std::vector<std::string> choice{"�o��", "�V���b�v", "�e��X�e�[�^�X�m�F","�E�ƃR�}���h","�T���x�m�F", "�Q�[���I��"};
    cout << "�߂ɂイ" << endl <<"###################################################" << endl;
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
        cout << endl <<"���ݒn : home" << endl;
        int action = menu();
        switch (action)
        {
        case 1: //�o��
            break;
        case 2: //�V���b�v
            break;
        case 3:
            checkstatus();
            break;
        case 4:
            job_command();
            break;
        case 6: //�Q�[���I��
            return;
            break;
        default:
            break;
        }
    }
}
