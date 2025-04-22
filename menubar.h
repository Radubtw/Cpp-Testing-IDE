#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenuBar>
#include <QWidget>
#include <QAction>
#include <QDir>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QDir dirPath, QWidget* parent = nullptr);
    ~MenuBar() = default;
    void init();
private:
    QDir dirPath;
    QMenu* file;
    QMenu* view;
    QMenu* build;
    QMenu* run;
    QMenu* terminal;
    QMenu* output;
    QMenu* testResults;
signals:
    void outputUpdated(const QString output);
    void outputToggled();
    void outputCleared();
    void terminalToggled();
    void explorerToggled();
    void codeFieldSplitted();
    void testResultsOpened();
    void startMenuOpened();
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
};

#endif // MENUBAR_H
