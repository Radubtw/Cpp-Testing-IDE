#include "windowmanager.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QToolTip { color: #ffffff; background-color: #000000; border: 0px; }");
    WindowManager* windowManager = WindowManager::init();
    windowManager->openStartMenu();
    return a.exec();
}

