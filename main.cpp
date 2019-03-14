//#include "mainwindow.cpp"
#include "database.cpp"
#include "view.cpp"
#include "player.cpp"
#include "cheat.cpp"
#include "role.h"
#include "shop_item.h"
#include "tool.h"
#include "character.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>

// Declare global varible
DataBase db;
Player player;
Character character[4];
Tools tools;
ShopItem shopitem;
int map[14][14][10];
int mode = 1;

// Main function
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Add BGM
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/welcome.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *bgm = new QMediaPlayer();
    bgm->setPlaylist(playlist);
    bgm->play();
    void AddMapItem(int x, int y, int num);
    void AddPictureItem(int x, int y, QString str);
    void AddPlayerItem(int x, int y, int toward, int sex);
    void AddTextItem(int x, int y, QString str, int size, QColor color);;

    // Connect database
    db.Connect(a.applicationDirPath()  + "/db.sqlite");

    // Main window
    MainWindow w;
    w.show();
    return a.exec();
}
