#ifndef PHONE_H
#define PHONE_H

#include <QObject>

class Phone : public QObject {
    Q_OBJECT
public:
    Phone() {}
    ~Phone() {}
signals:
    void change();
public slots:
    void slotTOGo(); //影响体力金钱心情
    void slotChat(); //影响体力心情好感度
    void slotGame(); //影响体力心情
};

#endif // PHONE_H
