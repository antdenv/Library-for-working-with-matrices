#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include "clothes.h"
#include "enemy.h"

enum obj_found {
    wolf_found = 1,
    dog_found,
    rat_found,
    armor_found,
    helmet_found,
    shield_found,
    pants_found,
    T_Shirt_found
};

struct field {
    size_t x;
    size_t y;
    size_t type;
};

struct position {
    size_t x = 0;
    size_t y = 0;
};

struct move {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};

class Map {
 public:
    Map() = default;
    explicit Map(const std::string& fname);
    ~Map() = default;
    void check_status(move& move) const;
    void delete_object();
    int find_object() const;
    size_t get_x() const;
    size_t get_y() const;
    void set_x(size_t x);
    void set_y(size_t y);

 private:
    std::vector<field> field_vector;
    size_t rows = 0;
    size_t cols = 0;
    position pos;
};

