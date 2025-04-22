#include <QShortcut>
#include "menubar.h"
#include "processes.hpp"
MenuBar::MenuBar(QDir dirPath, QWidget* parent) : QMenuBar(parent), dirPath(dirPath)
{
    init();
}


void MenuBar::init()
{
    QIcon runIcon = QIcon(":/assets/play.png");
    QIcon buildIcon = QIcon(":/assets/cog.png");
    QIcon terminalIcon = QIcon(":/assets/terminal.png");

    file = new QMenu("&File");
    file->setStyleSheet("background-color:000000");
    QAction* startMenuAction = new QAction("Open Start Menu");
    file->addAction(startMenuAction);

    view = new QMenu("&View");
    QAction* toggleTreeViewAction = new QAction("Explorer");
    toggleTreeViewAction->setShortcut(QKeySequence("Ctrl+Shift+E"));
    QAction* splitCodeFieldAction = new QAction("Split Code Field");
    splitCodeFieldAction->setShortcut(QKeySequence("Ctrl+/"));

    view->addAction(toggleTreeViewAction);
    view->addAction(splitCodeFieldAction);

    build = new QMenu("&Build");
    QAction* buildTestsAction = new QAction("Build Tests");
    buildTestsAction->setIcon(buildIcon);
    buildTestsAction->setShortcut(QKeySequence(tr("Ctrl+5")));

    build->addAction(buildTestsAction);

    run = new QMenu("&Run");
    QAction *runProjectAction = new QAction("Run project");
    runProjectAction->setIcon(runIcon);
    runProjectAction->setShortcut(QKeySequence(tr("Ctrl+R")));
    QAction *runTestsAction = new QAction("Run tests");
    runTestsAction->setIcon(runIcon);
    runTestsAction->setShortcut(QKeySequence(tr("Ctrl+T")));

    run->addAction(runProjectAction);
    run->addAction(runTestsAction);

    terminal = new QMenu("&Terminal");
    QAction *terminalAction = new QAction("Terminal");
    terminalAction->setIcon(terminalIcon);
    terminalAction->setShortcut(QKeySequence(tr("Ctrl+`")));

    terminal->addAction(terminalAction);

    output = new QMenu("&Output");
    QAction *outputAction = new QAction("Output");
    outputAction->setShortcut(QKeySequence("Ctrl+O"));
    QAction *clearOutputAction = new QAction("Clear Output");
    clearOutputAction->setShortcut(QKeySequence("Ctrl+Shift+O"));

    output->addAction(outputAction);
    output->addAction(clearOutputAction);

    testResults = new QMenu("&Test Results");
    QAction *testResultsAction = new QAction("Show Test Results");
    testResultsAction->setShortcut(QKeySequence("Ctrl+Shift+T"));

    testResults->addAction(testResultsAction);

    addMenu(file);
    addMenu(view);
    addMenu(build);
    addMenu(run);
    addMenu(terminal);
    addMenu(output);
    addMenu(testResults);

    QObject::connect(outputAction, &QAction::triggered, this, &MenuBar::toggleOutput);
    QObject::connect(terminalAction, &QAction::triggered, this, &MenuBar::toggleTerminal);
    QObject::connect(clearOutputAction, &QAction::triggered, this, &MenuBar::clearOutput);
    QObject::connect(runTestsAction, &QAction::triggered, this, &MenuBar::runTests);
    QObject::connect(buildTestsAction, &QAction::triggered, this, &MenuBar::compileTests);
    QObject::connect(toggleTreeViewAction, &QAction::triggered, this, &MenuBar::toggleExplorer);
    QObject::connect(splitCodeFieldAction, &QAction::triggered, this, &MenuBar::splitCodeField);
    QObject::connect(testResultsAction, &QAction::triggered, this, &MenuBar::openTestResults);
    QObject::connect(startMenuAction, &QAction::triggered, this, &MenuBar::openStartMenu);
    setStyleSheet("background-color:000000");
    show();
}

void MenuBar::openStartMenu()
{
    emit startMenuOpened();
}

void MenuBar::toggleOutput()
{
    qDebug() << "Output toggled";
    emit outputToggled();
}

void MenuBar::toggleTerminal()
{
    qDebug() << "Terminal toggled";
    emit terminalToggled();
}

void MenuBar::clearOutput()
{
    emit outputCleared();
}

void MenuBar::toggleExplorer()
{
    emit explorerToggled();
}

void MenuBar::splitCodeField()
{
    emit codeFieldSplitted();
}

void MenuBar::openTestResults()
{
    emit testResultsOpened();
}

void MenuBar::runTests()
{
    emit outputUpdated(QString(processes::Processes{}.compileAndRunTests(dirPath.absolutePath())));
}

void MenuBar::compileTests()
{
   emit outputUpdated(QString(processes::Processes{}.compileTests(dirPath.absolutePath())));
}
