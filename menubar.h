#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenuBar>
#include <QWidget>
#include <QAction>
#include <QDir>

#include "processes.hpp"

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QDir dirPath, QWidget* parent = nullptr);
    ~MenuBar() = default;
    void init();
    Processes* processes;
private:
    QDir dirPath;
    QMenu* file;
    QMenu* view;
    QMenu* build;
    QMenu* run;
    QMenu* terminal;
    QMenu* output;
    QMenu* testResults;
    QVector<QAction*> processActions{};
signals:
    void outputUpdated(const QString output);
    void outputToggled();
    void outputCleared();
    void terminalToggled();
    void explorerToggled();
    void codeFieldSplitted();
    void testResultsOpened();
    void startMenuOpened();
    void processStarted();
public slots:
    void toggleTerminal();
    void toggleOutput();
    void clearOutput();
    void toggleExplorer();
    void splitCodeField();
    void compileTests();
    void runTests();
    void openTestResults();
    void openStartMenu();
    void disableProcessActions();
    void enableProcessActions();
};

#endif // MENUBAR_H
