#include "windowmanager.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowManager* windowManager = WindowManager::init();
    windowManager->openStartMenu();
    return a.exec();
}

