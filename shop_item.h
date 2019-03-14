#ifndef SHOP_ITEM_H
#define SHOP_ITEM_H
//商店卖的消耗品，像key一样
class ShopItem {
public:
    ShopItem() {}
    ~ShopItem() {}
    int GetItem1() { return item1; }
    int GetItem2() { return item2; }
    int GetItem3() { return item3; }
    void SetItem1(int item1)	{ this->item1 = item1; }
    void SetItem2(int item2) { this->item2 = item2; }
    void SetItem3(int item3) { this->item3 = item3; }

private:
    int item1;
    int item2;
    int item3;
};

#endif // SHOP_ITEM_H
