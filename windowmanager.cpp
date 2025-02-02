#include "windowmanager.h"
#include "startMenu.h"
#include "createnewprojectwindow.h"
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

    if (startMenu) // Check if startMenu is not null
    {
        if (startMenu->isActiveWindow()) // Check if startMenu is the active window
        {
            startMenu->close(); // Close the window
        }
    }
    else
    {
        qDebug() << "startMenu is NULL\n";
    }
}

void WindowManager::openNewProjectWindow(QDir dirPath)
{
    newProjectWindow = new CreateNewProjectWindow(dirPath);
    newProjectWindow->show();
}

void WindowManager::closeNewProjectWindow()
{

    if (newProjectWindow) // Check if startMenu is not null
    {
        if (newProjectWindow->isActiveWindow()) // Check if startMenu is the active window
        {
            newProjectWindow->close(); // Close the window
        }
    }
    else
    {
        qDebug() << "startMenu is NULL\n";
    }
}
