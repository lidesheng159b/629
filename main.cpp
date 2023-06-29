#include "mainWindow.h"
#include <QtWidgets/QApplication>
//#pragma execution_character_set("utf-8")    // 解决汉字乱码问题，注意！！！
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IMGPro w;
    w.show();
    return a.exec();
}
