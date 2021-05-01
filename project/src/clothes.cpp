#include "clothes.h"

Clothes::Clothes(int WGT, int AMR) : WGT(WGT), ARM(AMR) { }

bool Clothes::get_clothes() const {
    return found_clothes;
}

bool Clothes::get_put_on_player() const {
    return put_on_player;
}

void Clothes::set_put_on_player(bool val) {
    put_on_player = val;
}

void Clothes::set_clothes(bool val) {
    found_clothes = val;
}

int Clothes::get_WGT() const {
    return WGT;
}

int Clothes::get_ARM() const {
    return ARM;
}

void Clothes::status_clothes(const std::map<std::string, Clothes>& cl_obj) const {
    for (const auto& [cl_type, cl_status] : cl_obj) {
        if (cl_status.found_clothes && !cl_status.put_on_player) {
            std::cout << "\n * pick " << cl_type;
        }
    }

    for (const auto& [cl_type, cl_status] : cl_obj) {
        if (cl_status.put_on_player) {
            std::cout << "\n * throw " << cl_type;
        }
    }
}
