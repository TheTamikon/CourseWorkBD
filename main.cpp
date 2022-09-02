#include "authification.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authification w;
    w.show();

    return a.exec();
}
