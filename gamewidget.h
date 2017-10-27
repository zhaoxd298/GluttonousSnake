#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QTimer>
#include "ui_gamewidget.h"
//#include "welcome.h"



namespace Ui {
class gameWidget;
}

class gameWidget : public QDialog, public Ui::gameWidget
{
    Q_OBJECT
    
public:
    explicit gameWidget(QWidget *parent = 0);
    ~gameWidget();

    //welcome *father;
    
private slots:
    void upbtn_slot();
    void downbtn_slot();
    void leftbtn_slot();
    void rightbtn_slot();
    void startbtn_slot();
    void backbtn_slot();

    void timeoutslot();

private:
    QTimer *timer;
};

#endif // GAMEWIDGET_H
