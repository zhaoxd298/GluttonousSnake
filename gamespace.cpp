#include "gamespace.h"
#include "optspace.h"
#include "gamewidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QMessageBox>


gameSpace::gameSpace(QWidget *parent) :
    QFrame(parent)
{
    //setupUi(this);

    this->resize(240, 240);

    int width = this->width();
    int height = this->height();
    x_num_max = (width / 20);
    y_num_max = (height / 20);

    snake[0][0] = qrand() % (x_num_max-2) + 1;
    snake[0][1] = qrand() % (y_num_max-2) + 1;
    direction = qrand() % 4;

    foodx = qrand() % x_num_max;
    foody = qrand() % y_num_max;
    foodcount = 0;
    score = 0;
    
}

bool gameSpace::eat_food() const
{
	if (snake[0][0]==foodx && snake[0][1]==foody) {
		return true;
	} else {
		return false;
	}
}

void gameSpace::update_food_coord()
{
	foodx = qrand() % x_num_max;
    foody = qrand() % y_num_max;
}

void gameSpace::change_snake_coord()
{
	// 改变蛇身子坐标
    for (int i=foodcount; i>0; i--) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
    }

    // 改变蛇头坐标
    switch (direction) {
        case UP:
            snake[0][1]--;
            break;
        case DOWN:
            snake[0][1]++;
            break;
        case LEFT:
            snake[0][0]--;
            break;
        case RIGHT:
            snake[0][0]++;
            break;
        default:
            break;
    }
}

bool gameSpace::correct_check()
{
	// 越界监测
    if (snake[0][0]<0 || snake[0][0]>=x_num_max || snake[0][1]<0 || snake[0][1]>=y_num_max) {
        memcpy(snake, snake_bak, sizeof(snake));
        
        return true;
    }

    // 自杀监测
    for (int i=1; i<=foodcount; i++) {
        if (snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1]) {
            memcpy(snake, snake_bak, sizeof(snake));
           
            return true;
        }
    }

    return false;
}

/*void gameSpace::timeoutslot()
{
    // 判定是否吃到食物
    if (snake[0][0]==foodx && snake[0][1]==foody) {
        // 更新食物坐标
        foodx = qrand() % x_num_max;
        foody = qrand() % y_num_max;

        foodcount ++;

        score += 10;
        //score_display->setText(QString::number(score).toUpper());
    }

    memcpy(snake_bak, snake, sizeof(snake));

    // 改变蛇身子坐标
    for (int i=foodcount; i>0; i--) {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
    }

    // 改变蛇头坐标
    switch (direction) {
        case UP:
            snake[0][1]--;
            break;
        case DOWN:
            snake[0][1]++;
            break;
        case LEFT:
            snake[0][0]--;
            break;
        case RIGHT:
            snake[0][0]++;
            break;
        default:
            break;
    }

    // 越界监测
    if (snake[0][0]<0 || snake[0][0]>=x_num_max || snake[0][1]<0 || snake[0][1]>=y_num_max) {
        memcpy(snake, snake_bak, sizeof(snake));
        int ret = QMessageBox::question(this, "提示", "Game over!", QMessageBox::Ok);
        if (QMessageBox::Ok == ret) {
            close();
            delete this;
            //timer->stop();
            return;
         }
    }

    // 自杀监测
    for (int i=1; i<=foodcount; i++) {
        if (snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1]) {
            memcpy(snake, snake_bak, sizeof(snake));
            int ret = QMessageBox::question(this, "提示", "Game over!", QMessageBox::Ok);
            if (QMessageBox::Ok == ret) {
                close();
                delete this;
                //timer->stop();
                return;
             }
        }
    }

    update();   // 调用这个函数后会自动调用paintEvent()函数来重新绘制界面
}*/


void gameSpace::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int x, y;

    x_num_max = this->width() / 20;
    y_num_max = this->height() / 20;

    //qDebug() << "width1:" << width << "height1:" << height;

    width = (width / 20) * 20;
    height = (height / 20) * 20;
    for (y=0; y<=height; y+=20) {
        painter.drawLine(0, y, width, y);
    }
    for (x=0; x<=width; x+=20) {
        painter.drawLine(x, 0, x, height);
    }

    // 绘制食物
    painter.drawImage(QRectF(foodx*20, foody*20, 20, 20), QImage(":/newPrefix/img/apple.png"));

    // 蛇头
    switch (direction) {
        case UP:
            painter.drawImage(QRectF(snake[0][0]*20, snake[0][1]*20, 20, 20), QImage(":/newPrefix/img/headup.png"));
            break;
        case DOWN:
            painter.drawImage(QRectF(snake[0][0]*20, snake[0][1]*20, 20, 20), QImage(":/newPrefix/img/headdown.png"));
            break;
        case LEFT:
            painter.drawImage(QRectF(snake[0][0]*20, snake[0][1]*20, 20, 20), QImage(":/newPrefix/img/headleft.png"));
            break;
        case RIGHT:
            painter.drawImage(QRectF(snake[0][0]*20, snake[0][1]*20, 20, 20), QImage(":/newPrefix/img/headright.png"));
            break;
        default:
            break;
    }

    // 绘制蛇身体
    for (int i=1; i<foodcount; i++) {

        if ((snake[i][0]==snake[i-1][0] && snake[i][1]<snake[i-1][1] && snake[i][1]==snake[i+1][1] && snake[i][0]<snake[i+1][0]) ||
            (snake[i][1]==snake[i-1][1] && snake[i][0]<snake[i-1][0] && snake[i][0]==snake[i+1][0] && snake[i][1] < snake[i+1][1])) {
             painter.drawImage(QRectF(snake[i][0]*20, snake[i][1]*20, 20, 20), QImage(":/newPrefix/img/tl_corner.png"));

        } else if ((snake[i][1]==snake[i-1][1] && snake[i][0]>snake[i-1][0] && snake[i][0]==snake[i+1][0] && snake[i][1]<snake[i+1][1]) ||
                   (snake[i][0]== snake[i-1][0] && snake[i][1]<snake[i-1][1] && snake[i][1]==snake[i+1][1] && snake[i][0]>snake[i+1][0])) {
            painter.drawImage(QRectF(snake[i][0]*20, snake[i][1]*20, 20, 20), QImage(":/newPrefix/img/tr_corner.png"));

        } else if((snake[i][0]==snake[i-1][0] && snake[i][1]>snake[i-1][1] && snake[i][1]==snake[i+1][1] && snake[i][0]<snake[i+1][0]) ||
                  (snake[i][1]==snake[i-1][1] && snake[i][0]<snake[i-1][0] && snake[i][0]==snake[i+1][0] && snake[i][1]>snake[i+1][1])) {
            painter.drawImage(QRectF(snake[i][0]*20, snake[i][1]*20, 20, 20), QImage(":/newPrefix/img/bl_corner.png"));

        } else if ((snake[i][0]==snake[i-1][0] && snake[i][1]>snake[i-1][1] && snake[i][1]==snake[i+1][1] && snake[i][0]>snake[i+1][0]) ||
                   (snake[i][1]==snake[i-1][1] && snake[i][0]>snake[i-1][0] && snake[i][0]==snake[i+1][0] && snake[i][1]>snake[i+1][1])) {
            painter.drawImage(QRectF(snake[i][0]*20, snake[i][1]*20, 20, 20), QImage(":/newPrefix/img/br_corner.png"));

        } else if (snake[i][1] == snake[i-1][1] && snake[i][0] != snake[i-1][0]) {
            painter.drawImage(QRectF(snake[i][0]*20, snake[i][1]*20, 20, 20), QImage(":/newPrefix/img/h_body.png"));
        } else if (snake[i][0] == snake[i-1][0] &&
                   snake[i][1] != snake[i-1][1]) {
             painter.drawImage(QRectF(snake[i][0]*20, snake[i][1]*20, 20, 20), QImage(":/newPrefix/img/v_body.png"));
        }
    }

    // 绘制蛇尾巴
    if (foodcount) {
        if (snake[foodcount][0]==snake[foodcount-1][0] && snake[foodcount][1]>snake[foodcount-1][1]) {
            painter.drawImage(QRectF(snake[foodcount][0]*20, snake[foodcount][1]*20, 20, 20), QImage(":/newPrefix/img/tailup.png"));
        } else if (snake[foodcount][0] == snake[foodcount-1][0] && snake[foodcount][1]<snake[foodcount-1][1]) {
            painter.drawImage(QRectF(snake[foodcount][0]*20, snake[foodcount][1]*20, 20, 20), QImage(":/newPrefix/img/taildown.png"));
        } else if (snake[foodcount][1] == snake[foodcount-1][1] && snake[foodcount][0]>snake[foodcount-1][0]) {
            painter.drawImage(QRectF(snake[foodcount][0]*20, snake[foodcount][1]*20, 20, 20), QImage(":/newPrefix/img/tailleft.png"));
        } else if (snake[foodcount][1] == snake[foodcount-1][1] && snake[foodcount][0]<snake[foodcount-1][0]) {
            painter.drawImage(QRectF(snake[foodcount][0]*20, snake[foodcount][1]*20, 20, 20), QImage(":/newPrefix/img/tailright.png"));
        }
    }

}
