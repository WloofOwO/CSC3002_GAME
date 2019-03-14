#include "cheat.h"
#include "player.h"
#include "role.h"
#include "tool.h"
#include "shop_item.h"
#include <QtMath>


extern Player player;
extern Tools tools;
extern ShopItem items;
extern int mode;

void Cheat::slotCheatEnergy() {             // Cheat: Hp+100
    player.SetEnergy(player.GetEnerge() + 100);
    emit change();
}

void Cheat::slotCheatIQ() {         // Cheat: Attack+3
    player.SetIQ(player.GetIQ() + 10);
    emit change();
}

void Cheat::slotCheatEQ() {         // Cheat: Defend+2
    player.SetEQ(player.GetEQ() + 2);
    emit change();
}

void Cheat::slotCheatMoney() {          // Cheat: Money+50
    player.SetMoney(player.GetMoney() + 100);
    emit change();
}

void Cheat::slotCheatGrade() {          // Cheat: Level+1, Hp+10, Attack+1, Defend+1
    player.GradeUp();
    emit change();
}

void Cheat::slotCheatLike() {          // Cheat: Money+50
    player.SetLike(player.GetLike() + 100);
    emit change();
}



void Cheat::slotCheatMode() {           // Cheat: God mode
    mode = -mode;
    emit change();
}

