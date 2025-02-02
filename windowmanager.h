#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QDir>
class Widget;
class CreateNewProjectWindow;
class WindowManager
{
public:
    WindowManager();
    ~WindowManager();
private:
    static WindowManager* instance;
    Widget* startMenu;
    CreateNewProjectWindow* newProjectWindow;

public:
    static WindowManager* init();
    void openStartMenu();
    void closeStartMenu();
    void openNewProjectWindow(QDir dirPath);
    void closeNewProjectWindow();
};

#endif // WINDOWMANAGER_H
