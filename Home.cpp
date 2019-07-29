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
    std::vector<std::string> choice{"�o��", "�V���b�v", "�e��X�e�[�^�X�m�F","�E�ƃR�}���h","�T���x�m�F", "�Z�[�u", "�Q�[���I��"};
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
        case 7: //�Q�[���I��
            return;
            break;
        default:
            break;
        }
    }
}