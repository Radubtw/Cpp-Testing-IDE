#ifndef CREATENEWPROJECTWINDOW_H
#define CREATENEWPROJECTWINDOW_H
#include <QDir>
#include <QWidget>
#include <QHBoxLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTextEdit>
#include <QPushButton>
#include "codefield.h"
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
    QHBoxLayout* mainLayout;
    QHBoxLayout* secondaryLayout;
    QVBoxLayout* testAndMockButtonsLayout;
    QFileSystemModel* fileSystemModel;
    QTreeView* treeView;
    CodeField* codeField;
    CodeField* testCodeField;
    QTextEdit* selectedClassOrFunction;
    QPushButton* writeTestButton;
    QPushButton* generateTestButton;
    QPushButton* writeMockButton;
    QPushButton* generateMockButton;
    QString currentFilePath;
public:
    void initLayout();
private slots:
    void showFileContent(const QModelIndex &index);
    void saveFileContent();
signals:
};

#endif // CREATENEWPROJECTWINDOW_H
