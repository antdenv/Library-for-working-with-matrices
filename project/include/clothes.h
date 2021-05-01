#pragma once

#include <iostream>
#include <string>
#include <map>

enum cl_wgt {
    armor_wgt = 3,
    helmet_wgt = 2,
    shield_wgt = 7,
    pants_wgt = 1,
    T_Shirt_wgt = 1
};

enum cl_arm {
    armor_arm = 3,
    helmet_arm = 3,
    shield_arm = 5,
    pants_arm = 1,
    T_Shirt_arm = 1
};

class Clothes {
 public:
    Clothes() = default;
    Clothes(int WGT, int ARM);
    ~Clothes() = default;

    void set_clothes(bool val);
    void set_put_on_player(bool val);

    bool get_clothes() const;
    bool get_put_on_player() const;

    int get_WGT() const;
    int get_ARM() const;

    void status_clothes(const std::map<std::string, Clothes>& cl_obj) const;

 private:
    bool put_on_player = false;
    bool found_clothes = false;
    int WGT;
    int ARM;
};
