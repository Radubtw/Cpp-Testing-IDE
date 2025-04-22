#include "windowmanager.h"
#include "startMenu.h"
#include "createnewprojectwindow.h"
#include "testresultswindow.h"
#include <QDebug>

WindowManager* WindowManager::instance;

WindowManager::WindowManager()
{

}
WindowManager::~WindowManager()
{

}

WindowManager* WindowManager::init()
{
    if(WindowManager::instance == nullptr)
    {
        WindowManager::instance = new WindowManager();
    }
    return WindowManager::instance;
}

void WindowManager::openStartMenu()
{
    startMenu = new Widget();
    startMenu->show();
}

void WindowManager::closeStartMenu()
{

    if (startMenu)
    {
        if (startMenu->isActiveWindow())
        {
            startMenu->close();
        }
    }
    else
    {
        qDebug() << "startMenu is NULL\n";
    }
}

void WindowManager::openExistingProjectWindow(QDir dirPath)
{
    newProjectWindow = new CreateNewProjectWindow(dirPath);
    newProjectWindow->show();
}

void WindowManager::closeExistingProjectWindow()
{

    if (newProjectWindow)
    {
        if (newProjectWindow->isActiveWindow())
        {
            newProjectWindow->close();
        }
    }
    else
    {
        qDebug() << "startMenu is NULL\n";
    }
}

