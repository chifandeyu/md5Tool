#include "md5Tool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    md5Tool w;
    w.show();
    return a.exec();
}
