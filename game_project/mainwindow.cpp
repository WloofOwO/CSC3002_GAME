#include "mainwindow.h"
#include "database.h"
#include "player.h"
#include "role.h"
#include "tool.h"
#include "character.h"
#include "shop_item.h"
#include "cheat.h"
#include "phone.h"
#include <QTime>
#include <QtMath>
#include <QApplication>
#include <QDebug>

// Constants
const int kPixlen = 32;             // The pixels of each block
const int kOffsetX = 174;           // The offset of x
const int kOffsetY = 224;           // The offset of y
const int kDecimal = 10;            // Decimal system


// Differnt color
const QString kGreen = "#00EE00";
const QString kBlue = "#0000EE";
const QString kYellow = "#EEEE00";
const QString kPurple = "#8B008B";
const QString kRed = "#EE0000";

// Use extern varible
extern DataBase db;
extern Player player;
extern ShopItem items;
extern Tools tools;
extern Role parameter;
extern int map[14][14][1];
extern int mode;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize private varible
    cheats = new Cheat();
    //phone = new Phone();
    scene = new QGraphicsScene;
    view = new View(this);

    // Create all actions in mainwindow
    CreateActions();

    // Create all menus in mainwindow
    CreateMenus();
    scene->setSceneRect(-200,-200,400,400);

    view->setScene(scene);
    view->setMinimumSize(400,400);
    //view->setRenderHint(QPainter::Antialiasing);
    view->show();

    // Create CONNECT between mainwindow and view
    connect(view, SIGNAL(quit()), this, SLOT(close()));
    connect(view, SIGNAL(change()), this, SLOT(slotDrawScene()));
    connect(view, SIGNAL(date(int)), this, SLOT(slotDate(int)));
    connect(view, SIGNAL(events(QString)), this, SLOT(slotEvent(QString)));
    connect(view, SIGNAL(move(int, int)), this, SLOT(slotMovePlayerItem(int, int)));

    // Set central widget and modify titile
    setCentralWidget(view);
    resize(550,450);
    setWindowTitle(tr("Magic Tower"));

    // Welcome page
    Welcome();
}


MainWindow::~MainWindow() {                  // Destructor
    delete scene;
    delete view;
    delete cheats;
}

void MainWindow::Welcome() {
    slotEvent("welcome");                    // Call the "welcome" slotevent
}

void MainWindow::CreateActions() {           // Create all actions in mainwindow
    // Initialize all actions
    clear = new QAction(tr("Clear"), this);
    newGame = new QAction(tr("NewGame"), this);
    saveGame = new QAction(tr("SaveGame"), this);
    loadGame = new QAction(tr("LoadGame"), this);
    exitGame = new QAction(tr("Quit"), this);
    cheatEnergy = new QAction(tr("Energy+100"), this);
    cheatIQ = new QAction(tr("IQ+10"), this);
    cheatEQ = new QAction(tr("EQ+10"), this);
    cheatMoney = new QAction(tr("Money+50"), this);
    cheatGrade = new QAction(tr("Grade+1"), this);
    cheatLike = new QAction(tr("Like+100"), this);
    cheatMode = new QAction(tr("GodMode"), this);

    // newGame->setShortcut(tr("N"));
    // saveGame->setShortcut(tr("S"));
    // loadGame->setShortcut(tr("L"));
    // exitGame->setShortcut(tr("Q"));

    // Connect all actions
    connect(cheats, SIGNAL(change()), this, SLOT(slotDrawScene()));
    connect(newGame, SIGNAL(triggered()), this, SLOT(slotNewGame()));
    connect(saveGame, SIGNAL(triggered()), this, SLOT(slotSaveGame()));
    connect(loadGame, SIGNAL(triggered()), this, SLOT(slotLoadGame()));
    connect(exitGame, SIGNAL(triggered()), this, SLOT(close()));
    connect(cheatEnergy, SIGNAL(triggered()), cheats, SLOT(slotCheatEnergy()));
    connect(cheatIQ, SIGNAL(triggered()), cheats, SLOT(slotCheatIQ()));
    connect(cheatEQ, SIGNAL(triggered()), cheats, SLOT(slotCheatIQ()));
    connect(cheatMoney, SIGNAL(triggered()), cheats, SLOT(slotCheatMoney()));
    connect(cheatGrade, SIGNAL(triggered()), cheats, SLOT(slotCheatGrade()));
    connect(cheatLike, SIGNAL(triggered()), cheats, SLOT(slotCheatGrade()));
    connect(cheatMode, SIGNAL(triggered()), cheats, SLOT(slotCheatMode()));
}


void MainWindow::CreateMenus() {             // Create all menus in mainwindow
    // file menu
    QMenu *fileMenu = menuBar()->addMenu(tr(" Menu "));
    fileMenu->addAction(newGame);
    fileMenu->addAction(saveGame);
    fileMenu->addAction(loadGame);
    fileMenu->addSeparator();
    fileMenu->addAction(exitGame);

    // cheat menuifferent ending according to sex
    QMenu *cheatMenu = menuBar()->addMenu(tr(" Cheat! "));
    cheatMenu->addAction(cheatEnergy);
    cheatMenu->addAction(cheatIQ);
    cheatMenu->addAction(cheatEQ);
    cheatMenu->addAction(cheatMoney);
    cheatMenu->addAction(cheatGrade);
    cheatMenu->addAction(cheatLike);
    //cheatMenu->addSeparator();
    //cheatMenu->addSeparator();
    //cheatMenu->addSeparator();
    cheatMenu->addAction(cheatMode);
}

void MainWindow::CreateInform() {           // Print player information
    AddPictureItem(-102, 0, "sidebg");
    AddPictureItem(-97, 30, "side");
    AddPictureItem(-85, 5, "info1");
    AddPictureItem(-65, 60, "sex"+QString::number(player.GetSex(), kDecimal));
    AddPictureItem(-82, 130, "info2");
    AddPictureItem(-83, 145, "info3");
    AddPictureItem(-83, 230, "info4");
    AddTextItem(-50, 5, QString::number(player.GetPlace()+1, kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-65, 100, "Grade "+QString::number(player.GetGrade() +1, kDecimal), 10, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 126, QString::number(player.GetEnerge(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 142, QString::number(player.GetIQ(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 158, QString::number(player.GetEQ(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 174, QString::number(player.GetCharm(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 190, QString::number(player.GetMoney(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 206, QString::number(parameter.GetLike(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));

    //AddTextItem(-40, 240, QString::number(keys.GetYellow(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    //AddTextItem(-40, 265, QString::number(keys.GetBlue(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    //AddTextItem(-40, 290, QString::number(keys.GetRed(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    if (mode == -1)
        AddTextItem(-90, 30, "God Mode!!!", 12, kRed);

}



