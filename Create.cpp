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
        cout << "man か woman で入力してください" << endl << ">>>";
    }
    fs.open("resorse/job.json", ios::binary);
    fs >> val;
    fs.close();
    jobs = val.get<picojson::object>["jobs_list"].get<picojson::array>();
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
    Write write;
    write.chara(name, job, sexual);
}