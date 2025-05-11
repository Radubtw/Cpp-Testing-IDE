#ifndef CREATENEWPROJECTWINDOW_H
#define CREATENEWPROJECTWINDOW_H
#include <QDir>
#include <QWidget>
#include <QHBoxLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTextEdit>
#include <QPushButton>
#include <QVector>
#include <QSplitter>

#include "generatedtextedit.h"
#include "clickablelabel.h"
#include "menubar.h"
#include "codefield.h"
#include "outputsection.h"
#include "terminal.h"
#include "processes.hpp"
QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE
class CreateNewProjectWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CreateNewProjectWindow (QDir dirPath = QDir("/"),QWidget *parent = nullptr);
private:
    Ui::Form *ui;
    QDir projectPath;
    QSplitter* horizontalMainSplitter;
    QSplitter* codeFieldsSplitter;
    MenuBar* menuBar;
    QHBoxLayout* mainLayout;
    QGridLayout* secondaryLayout;
    QVBoxLayout* testAndMockButtonsLayout;
    QFileSystemModel* fileSystemModel;
    QTreeView* treeView;
    QVector<CodeField*> codeFields;
    GeneratedTextEdit* testCodeField;
    OutputSection* outputSection;
    Terminal* terminal;
    QTextEdit* selectedClassOrFunction;
    QPushButton* generateTestButton;
    QPushButton* generateMockButton;
    QPushButton* newDirectoryButton;
    QPushButton* newFileButton;
    ClickableLabel* projectName;
    Processes* processes;
    QWidget* treeViewLayoutWidget;
    QString lastClickedPath;
    QLineEdit* newFileLineEdit{};
    QLineEdit* newDirLineEdit{};
    QGridLayout* treeViewLayout;
    //QPushButton* compileAndRunTests;
public:
    void initLayout();
    void initMenuBar(QDir dirPath);
    void connectElements();
private slots:
    void openGenerateTestDialog();
    void generateMock();
    void showFileContent(const QModelIndex &index);
    void saveFileContent();
    void splitCodeField();
    void toggleExplorer();
    void openTestResultsWindow();
    void toggleTerminal();
    void toggleOutput();
    void openStartMenu();
    void readOutput(QString output);
    void createNewDirectory();
    void createNewFile();
    void showNewDirLineEdit();
    void showNewFileLineEdit();
    void clickLabel();
    void clickTreeViewEntry(const QModelIndex index);
signals:
};

#endif // CREATENEWPROJECTWINDOW_H
