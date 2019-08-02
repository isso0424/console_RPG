#ifndef _MAPS_HPP_
#define _MAPS_HPP_

#include <fstream>
#include "picojson.h"

class Maps{
public:
    void move_field(int map_id);
private:
    int action;
    int map_id;
    std::fstream fs;
    picojson::value val;
    picojson::value mapo;
    picojson::array monstar_list;
    std::vector<std::string> monstars;
    void in_field(std::vector<std::string> monstars, int id, picojson::array map_list);
};

#endif