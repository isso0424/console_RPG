#ifndef _MAPS_HPP_
#define _MAPS_HPP_

#include <fstream>
#include "picojson.h"
#include "Write.hpp"

class Maps{
public:
    void move_field(int map_id);
    int load_progress(int map_id);

private:
    int action, map_id, progress;
    std::fstream fs;
    picojson::value val, val2, val3;
    picojson::value mapo;
    picojson::array monstar_list, pros;
    std::vector<std::string> monstars;
    void in_field(std::vector<std::string> monstars, int id, picojson::array map_list);
    Write writer;
    std::vector<double> progresses;
};

#endif