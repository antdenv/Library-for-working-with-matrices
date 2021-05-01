#pragma once

#include <string>
#include <map>
#include <iostream>

#include "map.h"

class Player {
 public:
    Player() = default;
    ~Player() = default;
    void kick_enemy(Enemy& enemy, size_t& e_type, bool& e_live);
    void take_clothes(const std::string& comm, std::map<std::string, Clothes>& cl_obj, size_t&type);
    void throw_clothes(const std::string& comm, std::map<std::string, Clothes>& cl_obj);
    void move_and_check(move& move, const std::string& comm, size_t&type, Enemy& enemy,
                        std::map<std::string, Clothes>& cl_obj, Map& map);
    void print_moved(size_t&type, const Map& map) const;
    int get_ARM() const;
    int get_hp() const;
    void set_hp(int hp);

 private:
    int WGT = 0;
    int ARM = 0;
    int HP = 100;
    int DMG = 1;
};
