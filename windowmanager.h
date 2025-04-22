#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QDir>
class Widget;
class CreateNewProjectWindow;
class TestResultsWindow;
class WindowManager
{
public:
    WindowManager();
    ~WindowManager();
private:
    static WindowManager* instance;
    Widget* startMenu;
    CreateNewProjectWindow* newProjectWindow;
    TestResultsWindow* testResultsWindow;

public:
    static WindowManager* init();
    void openStartMenu();
    void closeStartMenu();
    void openExistingProjectWindow(QDir dirPath);
    void closeExistingProjectWindow();
    void closeTestResultsWindow();
    //void open
};

#endif // WINDOWMANAGER_H
