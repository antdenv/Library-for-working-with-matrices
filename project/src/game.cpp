#include "game.h"

Game::Game(const std::string &fname, bool second_stage)
        : e_live(false), map(fname), player(), second_stage(second_stage) { }

void Game::check_command(Enemy &enemy, const std::string &comm, size_t &type, move &move,
                            std::map<std::string, Clothes> &cl_obj) {
    if (comm == "move left" || comm == "move right" ||
        comm == "move up" || comm == "move down") {
        map.delete_object();

        for (auto& [cl_type, cl_status] : cl_obj) {
            cl_obj[cl_type] = cl_status;
            cl_status.set_clothes(false);
        }

        player.move_and_check(move, comm, type, enemy, cl_obj, map);
        return;
    }

    if (comm == "kick enemy" && e_live) {
        player.kick_enemy(enemy, type, e_live);
        return;
    }

    if (comm.compare(0, 4, "pick") == 0) {
        player.take_clothes(comm, cl_obj, type);
        return;
    }

    if (comm.compare(0, 5, "throw") == 0) {
        player.throw_clothes(comm, cl_obj);
    }
}

move&Game::supported_actions(size_t type, move &move, const std::map<std::string,
        Clothes> &cl_obj, bool &e_live) const {
    std::cout << "Supported actions:";

    if (type >= wolf_found && type <= rat_found) {
        e_live = true;
        std::cout << "\n * kick enemy";
    } else {
        map.check_status(move);
        if (type > rat_found) {
            status_clothes(cl_obj);
        }
    }
    return move;
}


void Game::init_clothes(std::map<std::string, Clothes>& cl_obj) {
    cl_obj["armor"] = {armor_wgt, armor_arm};
    cl_obj["helmet"] = {helmet_wgt, helmet_arm};
    cl_obj["shield"] = {shield_wgt, shield_arm};
    cl_obj["pants"] = {pants_wgt, pants_arm};
    cl_obj["T-Shirt"] = {T_Shirt_wgt, T_Shirt_arm};
}

void Game::run() {
    Enemy enemy;
    size_t type = 0;
    move move;
    std::string comm;

    std::map<std::string, Clothes> cl_obj;
    init_clothes(cl_obj);

    while (player.get_hp() > 0) {
        move = supported_actions(type, move, cl_obj, e_live);

        if (second_stage) {
            print_second_stage();
        } else {
            print_first_stage();
        }

        if (!getline(std::cin, comm)) {
            return;
        }

        check_command(enemy, comm, type, move, cl_obj);
    }

    std::cout << "\nplayer died\n";
}

void Game::print_first_stage() const {
    std::cout <<'\n'<< map.get_x() << " x " << map.get_y() << ", hp: " << player.get_hp() <<
              " > ";
}

void Game::print_second_stage() const {
    std::cout <<'\n'<< map.get_x() << " x " << map.get_y() << ", hp: " << player.get_hp() <<
              ", armor: " << player.get_ARM() << " > ";
}

void Game::status_clothes(const std::map<std::string, Clothes>& cl_obj) const {
    for (const auto& [cl_type, cl_status] : cl_obj) {
        if (cl_status.get_clothes() && !cl_status.get_put_on_player()) {
            std::cout << "\n * pick " << cl_type;
        }
    }

    for (const auto& [cl_type, cl_status] : cl_obj) {
        if (cl_status.get_put_on_player()) {
            std::cout << "\n * throw " << cl_type;
        }
    }
}



