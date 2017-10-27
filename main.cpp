#include <QApplication>
#include <QTextCodec>
#include "welcome.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));
    welcome w;
    w.show();
    
    return a.exec();
}
