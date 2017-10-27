#include "gamewidget.h"
#include "welcome.h"
#include <QMessageBox>

gameWidget::gameWidget(QWidget *parent) :
    QDialog(parent)
{
    //setAutoFillBackground(true);    // ���Ǹ�����
    setupUi(this);

    connect(opt_frame->upButton, SIGNAL(clicked()), this, SLOT(upbtn_slot()));
    connect(opt_frame->downButton, SIGNAL(clicked()), this, SLOT(downbtn_slot()));
    connect(opt_frame->leftButton, SIGNAL(clicked()), this, SLOT(leftbtn_slot()));
    connect(opt_frame->rightButton, SIGNAL(clicked()), this, SLOT(rightbtn_slot()));
    connect(opt_frame->startButton, SIGNAL(clicked()), this, SLOT(startbtn_slot()));
    connect(opt_frame->backButton, SIGNAL(clicked()), this, SLOT(backbtn_slot()));

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutslot()));

}

gameWidget::~gameWidget()
{
}

void gameWidget::timeoutslot()
{
    // �ж��Ƿ�Ե�ʳ��
    if (game_frame->eat_food()) {
        // ����ʳ������
        game_frame->update_food_coord();

        game_frame->add_food_cnt();

        game_frame->add_score();
        opt_frame->score_display->setText(QString::number(game_frame->get_score()).toUpper());
    }

    //memcpy(snake_bak, snake, sizeof(snake));

    game_frame->change_snake_coord();

    if (game_frame->correct_check()) {
        int ret = QMessageBox::question(this, "��ʾ", "Game over!", QMessageBox::Ok);
        if (QMessageBox::Ok == ret) {
            close();
            delete this;
            //timer->stop();
            return;
         }
    }

    game_frame->update();
    //update();   // ���������������Զ�����paintEvent()���������»��ƽ���
}

void gameWidget::upbtn_slot()
{
    game_frame->set_direct_up();
}

void gameWidget::downbtn_slot()
{
    game_frame->set_direct_down();
}

void gameWidget::leftbtn_slot()
{
    game_frame->set_direct_left();
}

void gameWidget::rightbtn_slot()
{
    game_frame->set_direct_right();
}

void gameWidget::startbtn_slot()
{
    int level = opt_frame->level_spin->value();
    opt_frame->level_spin->setEnabled(false);
    int tm;
    switch (level) {
        case 1:
            tm = 500;
            break;
        case 2:
            tm = 400;
            break;
        case 3:
            tm = 300;
            break;
        case 4:
            tm = 200;
            break;
        case 5:
            tm = 100;
            break;
    }

    timer->start(tm);
}


void gameWidget::backbtn_slot()
{
    this->close();
    delete this;
}

