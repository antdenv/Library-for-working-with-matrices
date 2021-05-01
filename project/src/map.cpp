#include "map.h"

Map::Map(const std::string& fname) {
    std::ifstream file(fname);

    if (!file) {
        std::cout << "file opening error\n";
        exit(1);
    }

    file >> rows >> cols;

    std::string obj;
    size_t x;
    size_t y;
    size_t type;

    while (!file.eof()) {
        x = 0;
        y = 0;
        file >> x >> y;
        if (x == 0 && y == 0) {
            break;
        }

        type = 0;
        file >> obj;

        if (obj == "wolf") {
            type = wolf_found;
        } else if (obj == "dog") {
            type = dog_found;
        } else if (obj == "rat") {
            type = rat_found;
        } else if (obj == "armor") {
            type = armor_found;
        } else if (obj == "helmet") {
            type = helmet_found;
        } else if (obj == "shield") {
            type = shield_found;
        } else if (obj == "pants") {
            type = pants_found;
        } else if (obj == "T-Shirt") {
            type = T_Shirt_found;
        }

        field_vector.push_back({x, y, type});
    }
    file.close();
}

void Map::check_status(move& move) const {
    if (pos.x > 0) {
        move.left = true;
        std::cout << "\n * move left";
    } else {
        move.left = false;
    }

    if (pos.x + 1 < rows) {
        move.right = true;
        std::cout << "\n * move right";
    } else {
        move.right = false;
    }

    if (pos.y > 0) {
        move.down = true;
        std::cout << "\n * move down";
    } else {
        move.down = false;
    }

    if (pos.y + 1 < cols) {
        move.up = true;
        std::cout << "\n * move up";
    } else {
        move.up = false;
    }

    if (!(move.down || move.up || move.right || move.left)) {
        std::cout << "\n";
    }
}

void Map::delete_object() {
    for (size_t i = 0; i < field_vector.size(); i++) {
        if (pos.x == field_vector[i].x && pos.y == field_vector[i].y) {
            field_vector.erase(field_vector.begin() + i);
        }
    }
}

int Map::find_object() const {
    if (pos.x > rows || pos.y > cols) {
        return 0;
    }

    for (size_t i = 0; i < field_vector.size(); i++) {
        if (field_vector[i].x == pos.x && field_vector[i].y == pos.y) {
            return field_vector[i].type;
        }
    }

    return 0;
}

size_t Map::get_x() const {
    return pos.x;
}

size_t Map::get_y() const {
    return pos.y;
}

void Map::set_x(size_t x) {
    pos.x = x;
}

void Map::set_y(size_t y) {
    pos.y = y;
}
