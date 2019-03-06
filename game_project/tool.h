#ifndef TOOL_H
#define TOOL_H

class Tools {
public:
    Tools() {}
    ~Tools() {}
    int GetItem4() { return item4; }
    int GetItem5() { return item5; }
    int GetItem6() { return item6; }
    void SetItem4(int item4)	{ this->item4 = item4; }
    void SetItem5(int item5) { this->item5 = item5; }
    void SetItem6(int item6) { this->item6 = item6; }

private:
    int item4;
    int item5;
    int item6;
};

#endif // TOOL_H
