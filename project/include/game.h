#pragma once

#include <string>
#include <map>
#include <iostream>

#include "player.h"

class Game {
 public:
    Game() = default;
    explicit Game(const std::string &fname, bool second_stage);
    ~Game() = default;
    void run();

 private:
    bool e_live;
    void status_clothes(const std::map<std::string, Clothes>& cl_obj) const;
    void init_clothes(std::map<std::string, Clothes>& cl_obj);
    void print_first_stage() const;
    void print_second_stage() const;
    move&supported_actions(size_t type, move &move, const std::map<std::string,
            Clothes> &cl_obj, bool&e_live) const;
    void check_command(Enemy &enemy, const std::string &comm, size_t &type, move &move,
                          std::map<std::string, Clothes> &cl_obj);

    Map map;
    Player player;
    bool second_stage;
};
