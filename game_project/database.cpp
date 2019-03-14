#include "database.h"
#include "player.h"
#include "tool.h"
#include "shop_item.h"
#include "character.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

//    https://blog.csdn.net/Zzhouzhou237/article/details/79459320
extern Player player;
extern Character character[4];
extern Tools tools;
extern ShopItem shopitem;
extern int map[14][14][10];

const int kMapLen = 14;
const int kMaxFloor = 10;
const int kDecimal=10;

DataBase::DataBase() {         // Create to SQLITE database
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DataBase::~DataBase() {         // Close database
    db.close();
}

void DataBase::Connect(QString dbpath) {         // Connect to SQLITE database
    db.setDatabaseName(dbpath);
    if (!db.open()) {
        QMessageBox msgBox; // https://doc.qt.io/archives/qt-4.8/qmessagebox.html
        msgBox.setIcon(QMessageBox::Critical);//add Icon
        msgBox.setText(db.lastError().text());// setText(const QString & text)
        msgBox.setStandardButtons(QMessageBox::Ok);//setStandardButtons(StandardButtons buttons)
        msgBox.exec();
    }

    QFile file(":/database/data.sql");         // Read and load sql data file
    if(!file.exists()){
        qDebug() << "Database init file not exist, expected: " << file.fileName();
    }
    QSqlQuery query(db);  // qt class : https://doc.qt.io/qt-5/qsqlquery.html
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //https://blog.csdn.net/huyisu/article/details/29819321 "QT file operation"
        QStringList scriptQueries = QTextStream(&file).readAll().split(';'); // script file by ";"
        foreach (QString queryTxt, scriptQueries) {
            if (queryTxt.trimmed().isEmpty()) {
                continue;
            } //skip the empty text
            if (!query.exec(queryTxt))
                //程序进入消息循环，等待可能输入进行响应。
                //这里main()把控制权转交给Qt，Qt完成事件处理工作，当应用程序退出的时候exec()的值就会返回。
                //在exec()中，Qt接受并处理用户和系统的事件并且把它们传递给适当的窗口部件。
            {
                qFatal("One of the query failed to execute. Error detail: %s", query.lastError().text().toStdString().c_str());
            }//debug
            query.finish();
        }
    }
    file.close();
    qDebug( "Database connected." );
}

void DataBase::LoadMap(int num) {         // Load map data, num = 0 for new, others for old
    QSqlQuery query(db);
    QString str = "SELECT layer0, layer1, layer2, layer3, layer4, layer5, layer6, layer7, layer8, layer9 FROM map WHERE id = " + QString::number(num+1, kDecimal);
    query.exec(str);
    query.next();
    for (int i = 0; i < kMaxFloor; i++) {
        QString floors = query.value(i).toString();
        floors = floors.simplified();//去空格
        int tmp = 0;
        while (floors.length() > 4) {
            map[tmp%kMapLen][tmp/kMapLen][i] = floors.left(3).toInt();
            floors.remove(0,4); //删除已读取
            tmp++;
        }
        map[kMapLen-1][kMapLen-1][i] = floors.toInt();
    }
    query.clear();
}

void DataBase::LoadPlayer() {         // Load player data
    QSqlQuery query(db);  // query length change!!!
    query.exec("SELECT hp, attack, defend, money, exp, miss, crit, level, posx, posy, floor, toward, sex, need FROM player WHERE id = 1");
    query.next();
    player.SetEnergy(query.value(0).toInt());
    player.SetIQ(query.value(1).toInt());
    player.SetEQ(query.value(2).toInt());
    player.SetMoney(query.value(3).toInt());
    player.SetExp(query.value(4).toInt());
    player.SetMiss(query.value(5).toInt());
    player.SetLike(query.value(6).toInt());
    player.SetGrade(query.value(7).toInt());
    player.SetPosx(query.value(8).toInt());
    player.SetPosy(query.value(9).toInt());
    player.SetPlace(query.value(10).toInt());
    player.SetToward(query.value(11).toInt());
    player.SetSex(query.value(12).toInt());
    player.SetNeed(query.value(13).toInt());
    player.SetDay(query.value(14).toInt());
    query.clear();
}

void DataBase::LoadCharacter() {         // Load monsters data
    QSqlQuery query(db);
    query.exec("SELECT hp, attack, defend, money, exp, miss, crit FROM monster");
    for (int i = 0; i < 13; i++) {
        query.next();
        character[i].SetEnergy(query.value(0).toInt());
        character[i].SetIQ(query.value(1).toInt());
        character[i].SetEQ(query.value(2).toInt());
        character[i].SetMoney(query.value(3).toInt());
        character[i].SetExp(query.value(4).toInt());
        character[i].SetMiss(query.value(5).toInt());
        character[i].SetLike(query.value(6).toInt());
    }
    query.clear();
}

void DataBase::LoadTools(int num) {         // Load tools data, num = 0 for new, others for old
    QSqlQuery query(db);
    QString str = "SELECT book, shield, sword FROM tools WHERE id = " + QString::number(num+1, kDecimal);
    query.exec(str);
    query.next();
    tools.SetItem4(query.value(0).toInt());
    tools.SetItem5(query.value(1).toInt());
    tools.SetItem6(query.value(2).toInt());
    query.clear();
}

void DataBase::LoadIteam(int num) {         // Load keys data, num = 0 for new, others for old
    QSqlQuery query(db);
    QString str = "SELECT red, blue, yellow FROM keys WHERE id = " + QString::number(num+1, kDecimal);
    query.exec(str);
    query.next();
    shopitem.SetItem1(query.value(0).toInt());
    shopitem.SetItem2(query.value(1).toInt());
    shopitem.SetItem3(query.value(2).toInt());
    query.clear();
}

void DataBase::SaveMap(int num) {         // Save map data
    QSqlQuery query(db);
    QString str = "UPDATE map SET layer0=?, layer1=?, layer2=?, layer3=?, layer4=?, layer5=?, layer6=?, layer7=?, layer8=?, layer9=? WHERE id=" + QString::number(num+1, kDecimal);
    query.prepare(str);
    query.bindValue(0, place(0));
    query.bindValue(1, place(1));
    query.bindValue(2, place(2));
    query.bindValue(3, place(3));
    query.bindValue(4, place(4));
    query.bindValue(5, place(5));
    query.bindValue(6, place(6));
    query.bindValue(7, place(7));
    query.bindValue(8, place(8));
    query.bindValue(9, place(9));
    query.exec();
    query.clear();
}

void DataBase::SavePlayer() {         // Save player data
    QSqlQuery query(db);
    QString str = "UPDATE player SET hp=?, attack=?, defend=?,money=?, exp=?, miss=?, crit=?, level=?, posx=?, posy=?, floor=?, toward=?, sex=?, need=? WHERE id=1";
    query.prepare(str);
    query.bindValue(0, player.GetEnerge());
    query.bindValue(1, player.GetIQ());
    query.bindValue(2, player.GetEQ());
    query.bindValue(3, player.GetMoney());
    query.bindValue(4, player.GetExp());
    query.bindValue(5, player.GetMiss());
    query.bindValue(6, player.GetLike());
    query.bindValue(7, player.GetGrade());
    query.bindValue(8, player.GetPosx());
    query.bindValue(9, player.GetPosy());
    query.bindValue(10, player.GetPlace());
    query.bindValue(11, player.GetToward());
    query.bindValue(12, player.GetSex());
    query.bindValue(13, player.GetNeed());
    query.exec();
    query.clear();
}

void DataBase::SaveTools(int num) {         // Save tools data
    QSqlQuery query(db);
    QString str = "UPDATE tools SET book=?, shield=?, sword=? WHERE id=" + QString::number(num+1, kDecimal);
    query.prepare(str);
    query.bindValue(0, tools.GetItem4());
    query.bindValue(1, tools.GetItem5());
    query.bindValue(2, tools.GetItem6());
    query.exec();
    query.clear();
}

void DataBase::SaveIteam(int num) {         // Save keys data
    QSqlQuery query(db);
    QString str = "UPDATE keys SET red=?, blue=?, yellow=? WHERE id=" + QString::number(num+1, kDecimal);
    query.prepare(str);
    query.bindValue(0, shopitem.GetItem1());
    query.bindValue(1, shopitem.GetItem2());
    query.bindValue(2, shopitem.GetItem3());
    query.exec();
    query.clear();
}

QString DataBase::place(int num) {         // Construct layer string
    QString str = " ";
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++) {
            if (map[j][i][num] < 10)
                str += "0";
            str += QString::number(map[j][i][num], kDecimal);
            str += " ";
        }
    return str;
}
