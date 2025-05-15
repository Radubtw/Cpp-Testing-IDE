#include <QShortcut>
#include "menubar.h"
#include "processes.hpp"
#include "StyleSheets.h"

MenuBar::MenuBar(QDir dirPath, QWidget* parent) : QMenuBar(parent), dirPath(dirPath)
{
    processes = new Processes(dirPath.path());
    processes->process = new QProcess();
    init();
}


void MenuBar::init()
{
    QIcon runIcon = QIcon(":/assets/play.png");
    QIcon buildIcon = QIcon(":/assets/cog.png");
    QIcon terminalIcon = QIcon(":/assets/terminal.png");

    file = new QMenu("&File");
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
    QAction* regularBuildAction = new QAction("Regular build");
    regularBuildAction->setIcon(buildIcon);
    regularBuildAction->setShortcut(QKeySequence(tr("Ctrl+B")));
    QAction* ninjaBuildAction = new QAction("Ninja build");
    ninjaBuildAction->setIcon(buildIcon);
    ninjaBuildAction->setShortcut(QKeySequence(tr("Ctrl+N")));

    build->addAction(regularBuildAction);
    processActions.push_back(regularBuildAction);
    build->addAction(ninjaBuildAction);
    processActions.push_back(ninjaBuildAction);

    run = new QMenu("&Run");
    QAction *runProjectAction = new QAction("Run project");
    runProjectAction->setIcon(runIcon);
    runProjectAction->setShortcut(QKeySequence(tr("Ctrl+R")));
    QAction *runTestsAction = new QAction("Run tests");
    runTestsAction->setIcon(runIcon);
    runTestsAction->setShortcut(QKeySequence(tr("Ctrl+T")));

    run->addAction(runProjectAction);
    run->addAction(runTestsAction);
    processActions.push_back(runProjectAction);
    processActions.push_back(runTestsAction);

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
    QObject::connect(regularBuildAction, &QAction::triggered, this, &MenuBar::compileTestsRegular);
    QObject::connect(ninjaBuildAction, &QAction::triggered, this, &MenuBar::compileTestsNinja);
    QObject::connect(toggleTreeViewAction, &QAction::triggered, this, &MenuBar::toggleExplorer);
    QObject::connect(splitCodeFieldAction, &QAction::triggered, this, &MenuBar::splitCodeField);
    QObject::connect(testResultsAction, &QAction::triggered, this, &MenuBar::openTestResults);
    QObject::connect(startMenuAction, &QAction::triggered, this, &MenuBar::openStartMenu);

    setStyleSheet("background-color:000000");
    show();
    setStyleSheet(stylesheets::menuBarStyleSheet);
    file->setStyleSheet(stylesheets::menuStyleSheet);
    view->setStyleSheet(stylesheets::menuStyleSheet);
    build->setStyleSheet(stylesheets::menuStyleSheet);
    run->setStyleSheet(stylesheets::menuStyleSheet);
    terminal->setStyleSheet(stylesheets::menuStyleSheet);
    output->setStyleSheet(stylesheets::menuStyleSheet);
    testResults->setStyleSheet(stylesheets::menuStyleSheet);
}

void MenuBar::disableProcessActions()
{
    qDebug() << "=== Attempting to disable actions ===";
    for(const auto& action : processActions) {
        qDebug() << "Action before disable:" << action->text() << "Enabled?" << action->isEnabled();
        action->setEnabled(false);
        qDebug() << "Action after disable:" << action->text() << "Enabled?" << action->isEnabled();
    }
}

void MenuBar::enableProcessActions()
{
    for(const auto& action : processActions)
    {
        action->setEnabled(true);
    }
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
    emit processStarted();
    processes->runTests(dirPath.absolutePath());
}

void MenuBar::compileTestsRegular()
{
    emit processStarted();
    processes->compileRegular(dirPath.absolutePath());
}

void MenuBar::compileTestsNinja()
{
    emit processStarted();
    processes->compileWithNinja(dirPath.absolutePath());
}

