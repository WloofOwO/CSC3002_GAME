#ifndef Role_H
#define Role_H

class Role {
public:
    Role() {}
    ~Role() {}
    int GetEnerge() { return energy; }
    int GetMode() {return mode;} //用于随机化事件收益, 可参考slotfight
    int GetIQ() { return IQ; }
    int GetEQ() { return EQ; }
    int GetCharm() {return charm;}
    int GetMoney() { return money; }
    int GetExp() { return exp; }   //EXP_IMPROVEMENT
    int GetMiss() { return miss; } //对方魅力值
    int GetLike() { return like; } //
    int GetDay() { return day;}
    int GetEat() { return eat;}
    int GetGrade() { return grade;}

    void SetEnergy(int energy)	{ this->energy = energy; }
    void GetMode(int mode) {this->mode = mode; }
    void SetIQ(int IQ) { this->IQ = IQ; }
    void SetEQ(int EQ) { this->EQ = EQ; }
    void SetCharm(int charm) { this->charm = charm; }
    void SetMoney(int money) { this->money = money; }
    void SetExp(int exp) { this->exp = exp; }
    void SetMiss(int miss) { this->miss = miss; }
    void SetLike(int like) { this->like = like; }
    void SetDay(int day) {this->day = day; }
    void SetEat(int eat){this->eat = eat;}
    void SetGrade(int grade){this->grade = grade;}

private:
    int energy;
    int mode;
    int IQ;
    int EQ;
    int charm;
    int money;
    int exp;
    int miss;
    int like;
    int day;
    int eat;
    int grade;
};

#endif // Role_H
