#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView {
    Q_OBJECT
signals:
    void move(int x, int y);
    void events(QString str);
    void date(int num);  //fight -> date
    void change();
    void quit();

public:
    explicit View(QWidget *parent = 0);       // Explicit means "implicit invocation" is not allow
    ~View();
    QString GetStatus() { return status; }
    void SetStatus(QString status) { this->status = status; }
    void keyMain(QKeyEvent *event);
    void keyShop(QKeyEvent *event);
    void keyPhone(QKeyEvent *event); // 类似shop 但是可以用按键触发
    void keyWelcome(QKeyEvent *event);
    void keySelect(QKeyEvent *event);
    void keyLike(QKeyEvent *event); //成功牵手
    void keydate(); //keyfight() -> keydate()
    void keylecture(QKeyEvent *event);
    void keyprof1(QKeyEvent *event);
    void keyprof2(QKeyEvent *event);
    void keyprof3(QKeyEvent *event);
    void keyeat(QKeyEvent *event);
    void keystudy(QKeyEvent *event);
    void keysleep(QKeyEvent *event); //sleep() include stave and random event triggers
    void keymovie(QKeyEvent *event);

    // random events
    void keyexam(QKeyEvent *event);
    void keybook(QKeyEvent *event);
    void keymoney(QKeyEvent *event);


    void action();

protected:
    void keyPressEvent(QKeyEvent *event);       // Rewrite the virtual function keyPressEvent
    void triggerEvent(QKeyEvent *event);
private:
    int access(int x, int y);
    QString status;
    int next_step;
};

#endif // VIEW_H
