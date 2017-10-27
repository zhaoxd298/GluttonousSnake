#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include <QDialog>
#include "ui_welcome.h"
#include "gamewidget.h"

namespace Ui {
class welcome;
}

class welcome : public QDialog, public Ui::welcome
{
    Q_OBJECT
    
public:
    explicit welcome(QWidget *parent = 0);
    ~welcome();

    void show_win();
    
private:
    gameWidget *game;

private slots:
    void clicked_startButton();
    void clicked_exitButton();
};

#endif // WELCOME_H
