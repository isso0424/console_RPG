#include <iostream>
#include "picojson.h"
#include "Create.hpp"
#include "Write.hpp"

using namespace std;
using namespace picojson;

void Create::chara(){
    cout << "�L�����N�^�[������͂��Ă�������" << endl << ">>>";
    cin >> name ;
    cout << "���ʂ���͂��Ă������� : man / woman" << endl << ">>>";
    while (true){
        cin >> sexual;
        if (sexual == "man" or sexual == "woman"){
            break;
        }
        cout << "man / woman �œ��͂��Ă�������" << endl << ">>>";
    }
    fs.open("resorse/job.json", ios::binary);
    fs >> val;
    fs.close();
    jobs = val.get<picojson::object>()["jobs_list"].get<picojson::array>();
    for (const auto& e: jobs){
        arr.push_back(e.get<std::string>());
    }
    cout << "�E�Ƃ�I�����Ă�������" << endl;
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
        cout << "���͂��ꂽ�l���s���ł�" << endl << ">>>"; 
    }
    Write write;
    write.chara(name, job, sexual);
}