#include "enemy.h"

Enemy::Enemy(const std::string& type) : enemy_type(type) {
    if (type == "wolf") {
        HP = wolf_hp;
        baseDMG = wolf_dmg;
    }

    if (type == "dog") {
        HP = dog_hp;
        baseDMG = dog_dmg;
    }

    if (type == "rat") {
        HP = rat_hp;
        baseDMG = rat_dmg;
    }
}

void Enemy::enemy_found() const {
    std::cout <<'\n'<< enemy_type << " found, " << get_hp() << " hp\n";
}

void Enemy::update_hp() {
    if (enemy_type == "wolf") {
        set_hp(wolf_hp);
    } else if (enemy_type == "dog") {
        set_hp(dog_hp);
    } else {
        set_hp(rat_hp);
    }
}

int Enemy::get_baseDMG() const {
    return baseDMG;
}

int Enemy::get_hp() const {
    return HP;
}

int Enemy::get_weaponDMG() const {
    return weaponDMG;
}

void Enemy::set_hp(int hp) {
    HP = hp;
}
