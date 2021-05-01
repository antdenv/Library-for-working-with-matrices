#include "player.h"

void Player::kick_enemy(Enemy& enemy, size_t& e_type, bool& e_live) {
    enemy.set_hp(enemy.get_hp() - DMG);

    if (enemy.get_hp() <= 0) {
        std::cout << "\nenemy killed\n";
        e_live = false;
        enemy.update_hp();
        e_type = 0;
        return;
    }

    HP = ARM >= (enemy.get_weaponDMG() + enemy.get_baseDMG()) ? HP - 1 :
            HP + ARM - (enemy.get_weaponDMG() + enemy.get_baseDMG());

    if (HP > 0) {
        std::cout << "\nenemy kicked. Enemy hp: " << enemy.get_hp() <<'\n';
    }
}

void Player::take_clothes(const std::string& comm, std::map<std::string, Clothes>& cl_obj, size_t&type) {
    for (auto& [cl_type, cl_status] : cl_obj) {
        if (cl_status.get_clothes() && comm.find(cl_type) > 0 &&
            !cl_status.get_put_on_player() && (WGT + cl_status.get_WGT()) <= 20) {
            std::cout << "\nclothes worn\n";

            cl_status.set_put_on_player(true);
            cl_status.set_clothes(false);

            WGT += cl_status.get_WGT();
            ARM += cl_status.get_ARM();

            type = 0;
            return;
        }
    }
}

void Player::throw_clothes(const std::string& comm, std::map<std::string, Clothes>& cl_obj) {
    for (auto& [cl_type, cl_status] : cl_obj) {
        if (cl_status.get_put_on_player() && comm.find(cl_type) != std::string::npos) {
            std::cout << "\nthe " << cl_type << " is thrown out\n";

            cl_status.set_put_on_player(false);

            ARM -= cl_status.get_ARM();
            WGT -= cl_status.get_WGT();

            return;
        }
    }
}

void Player::move_and_check(move &move, const std::string &comm, size_t &type, Enemy &enemy,
                            std::map<std::string, Clothes> &cl_obj, Map& map) {
    if (comm == "move left" && move.left) {
        map.set_x(map.get_x() - 1);
        print_moved(type, map);
    }

    if (comm == "move right" && move.right) {
        map.set_x(map.get_x() + 1);
        print_moved(type, map);
    }

    if (comm == "move down" && move.down) {
        map.set_y(map.get_y() - 1);
        print_moved(type, map);
    }

    if (comm == "move up" && move.up) {
        map.set_y(map.get_y() + 1);
        print_moved(type, map);
    }

    Enemy wolf("wolf");
    Enemy dog("dog");
    Enemy rat("rat");

    switch (type) {
        case wolf_found:
            enemy = wolf;
            enemy.enemy_found();
            return;

        case dog_found:
            enemy = dog;
            enemy.enemy_found();
            return;

        case rat_found:
            enemy = rat;
            enemy.enemy_found();
            return;

        case armor_found:
            std::cout << "\narmor found\n";
            cl_obj["armor"].set_clothes(true);
            return;

        case helmet_found:
            std::cout << "\nhelmet found\n";
            cl_obj["helmet"].set_clothes(true);
            return;

        case shield_found:
            std::cout << "\nshield found\n";
            cl_obj["shield"].set_clothes(true);
            return;

        case pants_found:
            std::cout << "\npants found\n";
            cl_obj["pants"].set_clothes(true);
            return;

        case T_Shirt_found:
            std::cout << "\nT-Shirt found\n";
            cl_obj["T-Shirt"].set_clothes(true);
            return;

        default:
            return;
    }
}

void Player::print_moved(size_t &type, const Map& map) const {
    type = map.find_object();

    if (type == 0) {
        std::cout << "\nmoved\n";
        return;
    }
}

int Player::get_ARM() const {
    return ARM;
}

int Player::get_hp() const {
    return HP;
}

void Player::set_hp(int hp) {
    HP = hp;
}
