#include "Home.hpp"
#include "picojson.h"
#include <fstream>
#include "Place.hpp"
#include <ostream>
#include <windows.h>
#include "Create.hpp"
#include "Write.hpp"
#include "maps.hpp"
using namespace std;

void Home::select_map(){
    fs.open("resorse/map.json");
    fs >> val;
    fs.close();
    picojson::array maps = val.get<object>()["maps"].get<picojson::array>();
    int max, count;
    count = 0;
    vector<string> map_list;
    for (auto map : maps){
        std::cout << map.get<object>()["id"].get<double>() << "/" << map.get<object>()["name"] << endl
             << "����Lv : " << map.get<object>()["Lv"].get<double>() << endl;
        max = map.get<object>()["Lv"].get<double>();
        map_list.push_back(map.get<object>()["name"].get<string>());
        count++;
    }
    std::cout << count << endl;
    std::cout << map_list[0] << endl;
    int map_id;
    while(true){
        std::cout << "��]����map��id����͂��Ă�������" << endl
         << ">>>";
        cin >> map_id;
        std::cout << map_id << endl;
        if (map_id < count){
            if (map_id < 0){
                continue;
            }
            string map_kind =  map_list[map_id];
            std::cout << map_kind << "�ֈړ����܂�" << endl;
            Maps ma;
            ma.move_field(map_id);
            break;
        }
    }
}

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
        std::cout << command["name"].get<string>() << "���g�p���܂�" << endl;
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
        std::cout << "�N�[���^�C�����ł�" << endl;
    }
}

void Home::checkstatus(){
    fs.open("resorse/chara.json");
    picojson::value val;
    fs >> val;
    fs.close();
    std::cout << "�e��X�e�[�^�X" << endl << "###################################################" << endl;
    std::cout << "���O : " << val.get<picojson::object>()["name"].get<string>() << endl;
    std::cout << "������ : " << val.get<picojson::object>()["money"].get<double>() << endl;
    std::cout << "�E�� : " << val.get<picojson::object>()["job"].get<string>() << endl;
    picojson::object status = val.get<picojson::object>()["status"].get<picojson::object>();
    std::cout << "HP : " << status["hp"].get<double>() << endl;
    std::cout << "MP : " << status["mp"].get<double>() << endl;
    std::cout << "�U���� : " << status["atk"].get<double>() << endl;
    std::cout << "�h��� : " << status["def"].get<double>() << endl;
    std::cout << "�m�� : " << status["int"].get<double>() << endl;
    std::cout << "���_�� : " << status["pow"].get<double>() << endl;
    std::cout << "#### �A�r���e�B���X�g ####" << endl;
    picojson::array abilitys = val.get<picojson::object>()["abilitys"].get<picojson::array>();
    for (picojson::value e : abilitys){
        std::cout << "�A�r���e�B��" << e.get<picojson::object>()["name"].get<string>() << endl;
        std::cout << "���" << e.get<picojson::object>()["kind"].get<string>() << endl;
        std::cout << "����" << e.get<picojson::object>()["effect"].get<picojson::object>()["name"].get<string>() << endl;
    }
    std::cout << "###################################################" << endl;
}

int Home::menu(){
    count = 1;
    std::vector<std::string> choice{"�o��", "�V���b�v", "�e��X�e�[�^�X�m�F","�E�ƃR�}���h","�T���x�m�F", "�Q�[���I��"};
    std::cout << "�߂ɂイ" << endl <<"###################################################" << endl;
    for (std::string cho : choice){
        std::cout << count << "/" << cho << " ";
        count++;
        if (count % 3 == 0){
            std::cout << endl;
        }
    }
    std::cout << endl << "###################################################" << endl;
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
        std::cout << endl <<"���ݒn : home" << endl;
        int action = menu();
        switch (action)
        {
        case 1: //�o��
            select_map();
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
