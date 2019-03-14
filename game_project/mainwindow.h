#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "view.h"
#include "cheat.h"
#include "phone.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMenuBar>
#include <QString>
#include <QSound>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Welcome();
    void Clear();
    void CreateActions();
    void CreateMenus();
    void CreateInform();
    void CreateDate(int num);

    void AddMapItem(int x, int y, int num);
    void AddPictureItem(int x, int y, QString str);
    void AddPlayerItem(int x, int y, int toward, int sex);
    void AddTextItem(int x, int y, QString str, int size, QColor color);
    QString GetExpectedImpv(int num);

public slots:
    void slotDrawScene();
    void slotNewGame();
    void slotSaveGame();
    void slotLoadGame();
    void slotMovePlayerItem(int x, int y);
    void slotShop();
    void slotPhone(); // create phone menus, like Shop menus
    //void slotBook();
    void slotDate(int num);
    void slotEvent(QString str);

private:
    View *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *playerItem;
    QAction *clear;
    QAction *newGame;
    QAction *loadGame;
    QAction *saveGame;
    QAction *exitGame;
    QAction *cheatEnergy;
    QAction *cheatIQ;
    QAction *cheatEQ;
    QAction *cheatMode;
    QAction *cheatMoney;
    QAction *cheatGrade;
    QAction *cheatItem1;
    QAction *cheatItem2;
    QAction *cheatItem3;
    QAction *cheatItem4;
    QAction *cheatItem5;
    QAction *cheatItem6;
    QAction *cheatLike;
    QAction *cheatGodMode;
    Cheat *cheats;
    QAction *ToGo; //外卖
    QAction *Chat;
    QAction *Game;

};

#endif // MAINWINDOW_H
