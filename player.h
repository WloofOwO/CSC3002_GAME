#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"
#include <QString>

class Player : public Role {
public:
    Player() {}
    ~Player() {}
    int GetGrade() { return grade; }
    int GetPosx() { return posx; }
    int GetPosy() { return posy; }
    int GetPlace() {return place; }
    int GetToward() {return toward; }
    int GetSex() {return sex; }
    int GetNeed() {return need; }

    void SetGrade(int grade) { this->grade = grade; }
    void SetPosx(int posx) { this->posx = posx; }
    void SetPosy(int posy) { this->posy = posy; }
    void SetPlace(int place) { this->place = place; }
    void SetToward(int toward) { this->toward = toward; }
    void SetSex(int sex) { this->sex = sex; }
    void SetNeed(int need) { this->need = need; }
    void ChooseSex(int sex);
    void GradeUp();

private:
    int grade;
    int posx;
    int posy;
    int place;
    int toward;
    int sex;
    int need;
};

#endif // PLAYER_H
