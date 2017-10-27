#ifndef GAMESPACE_H
#define GAMESPACE_H

#include <QFrame>
#include <QPainter>
//#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>

#define UP      0
#define DOWN    1
#define LEFT    2
#define RIGHT   3

namespace Ui {
class gameSpace;
}

class gameSpace : public QFrame
{
    Q_OBJECT
    
public:
    explicit gameSpace(QWidget *parent = 0);
    
    void paintEvent(QPaintEvent *event);
    void set_direct_up() {direction = UP;}
    void set_direct_down() {direction = DOWN;}
    void set_direct_left() {direction = LEFT;}
    void set_direct_right() {direction = RIGHT;}

    bool eat_food() const;
    void update_food_coord(); 
    void add_food_cnt() {foodcount++;}
    void add_score() {score += 10;}
    int get_score() const {return score;}
    void change_snake_coord();
    bool correct_check();
    void set_level_value(int value) {level = value;}
   

private:
    int score;
    int level;
    int direction;
    //QTimer *timer;
    int snake[100][2];  // 保存蛇的每个节点的坐标
    int snake_bak[100][2];
    int foodx, foody;
    int x_num_max, y_num_max;
    int foodcount;

private slots:
    //void timeoutslot();

};

#endif // GAMESPACE_H
