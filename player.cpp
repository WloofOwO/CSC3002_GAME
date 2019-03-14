#include "player.h"
#include <QtMath>

void Player::ChooseSex(int sex) {
    if (sex == 1) {
        SetEnergy(50);
        SetIQ(100);
        SetEQ(100);
        SetCharm(100);
        SetMoney(100);
        SetLike(0);
    } else {
        SetEnergy(50);
        SetIQ(100);
        SetEQ(100);
        SetCharm(100);
        SetMoney(100);
        SetLike(0);
    }

    this->grade = 0;
    this->posx = 6;
    this->posy = 12;
    this->place = 0;
    this->toward = 3;
    this->sex = sex;
    this->need = 5;  //what's need???
}

void Player::GradeUp() {
    grade += 1;

    //need = qFloor(need*1.5) + 1;
}
