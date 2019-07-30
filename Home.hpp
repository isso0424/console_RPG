#ifndef _HOME_HPP_
#define _HOME_HPP_

#include "picojson.h"
#include <fstream>

class Home{
public:
    void home();
private:
    int menu();
    int count;
    int chose;
    void checkstatus();
    void job_command();
    std::fstream fs;
    picojson::value val;
};

#endif