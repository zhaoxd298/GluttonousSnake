#include "welcome.h"
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

welcome::welcome(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(startButton, SIGNAL(clicked()), this, SLOT(clicked_startButton()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(clicked_exitButton()));

}

welcome::~welcome()
{
}

void welcome::show_win()
{
    this->show();
}

void welcome::clicked_startButton()
{
    game = new gameWidget();
    //game->resize(this->width(), this->height());
    //qDebug() << "width0:" << this->width() << "height0:" << this->height();
    this->hide();
    game->exec();
    this->show();
}

void welcome::clicked_exitButton()
{
    this->close();
}
