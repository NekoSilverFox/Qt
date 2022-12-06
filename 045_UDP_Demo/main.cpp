#include "upd_1.h"
#include "udp_2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Upd_1 w;
    w.show();

    Udp_2 w2;
    w2.show();
    return a.exec();
}
