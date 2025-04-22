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

#include "menubar.h"
#include "codefield.h"
#include "outputsection.h"
#include "terminal.h"
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
    QHBoxLayout* secondaryLayout;
    QVBoxLayout* testAndMockButtonsLayout;
    QFileSystemModel* fileSystemModel;
    QTreeView* treeView;
    QVector<CodeField*> codeFields;
    CodeField* testCodeField;
    OutputSection* outputSection;
    Terminal* terminal;
    QTextEdit* selectedClassOrFunction;
    QPushButton* generateTestButton;
    QPushButton* generateMockButton;
    QPushButton* newDirectoryButton;
    QPushButton* newFileButton;
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
    // void createNewDirectory();
    // void createNewFile();
signals:
};

#endif // CREATENEWPROJECTWINDOW_H
