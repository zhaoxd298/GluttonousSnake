#ifndef OPTSPACE_H
#define OPTSPACE_H

#include <QFrame>
#include "ui_optspace.h"

namespace Ui {
class optSpace;
}

class optSpace : public QFrame, public Ui::optSpace
{
    Q_OBJECT
    
public:
    explicit optSpace(QWidget *parent = 0);
    ~optSpace();
    
private:
};

#endif // OPTSPACE_H
