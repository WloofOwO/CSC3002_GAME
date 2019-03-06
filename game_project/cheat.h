#ifndef CHEAT_H
#define CHEAT_H
#include <QObject>

class Cheat : public QObject {
    Q_OBJECT
public:
    Cheat() {}
    ~Cheat() {}
signals:
    void change();
public slots:
    void slotCheatEnergy();
    void slotCheatIQ();
    void slotCheatEQ();
    void slotCheatCharm();
    void slotCheatMoney();
    void slotCheatGrade(); //不同年级触发不同剧情事件
    void slotCheatLike();
    void slotCheatGirlFriend();
    void slotCheatBoyFriend();
    void slotCheatResearchProf();
    void slotCheatIteam1(); //商店里卖的物品
    void slotCheatIteam2();
    void slotCheatIteam3();
    void slotCheatMode();
};

#endif // CHEAT_H
