#pragma once

#include <string>
#include <iostream>

enum enemy_hp {
    wolf_hp = 6,
    dog_hp = 3,
    rat_hp = 2
};

enum enemy_dmg {
    wolf_dmg = 10,
    dog_dmg = 5,
    rat_dmg = 3
};

class Enemy {
 public:
    Enemy() = default;
    explicit Enemy(const std::string& type);
    ~Enemy() = default;
    void update_hp();
    void enemy_found() const;
    int get_baseDMG() const;
    int get_hp() const;
    int get_weaponDMG() const;
    void set_hp(int hp);

 protected:
    std::string enemy_type;
    int baseDMG = 0;
    int HP = 0;
    int weaponDMG = 1;
};

