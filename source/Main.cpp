#include "QEMU-GUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QEMUGUI w;
    //QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(saveSettingsBeforeQuit()));
    w.show();

    return a.exec();
}
