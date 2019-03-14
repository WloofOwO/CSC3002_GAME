#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>

class DataBase {
public:
    DataBase();
    ~DataBase();
    void Connect(QString dbpath);
    void SaveMap(int num);
    void LoadMap(int num);
    void SaveTools(int num);
    void LoadTools(int num);
    void SaveIteam(int num); //boyfriend & girlfriend & research professor
    void LoadIteam(int num);
    void SavePlayer();
    void LoadPlayer();
    void LoadCharacter(); //professor & friend

private:
    QString place(int num);
    QSqlDatabase db;
};

#endif // DATABASE_H
