#ifndef OPENNEWPROJECTDIALOG_H
#define OPENNEWPROJECTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QLineEdit>
#include <QCheckBox>

class OpenNewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    OpenNewProjectDialog();
    QString getProjectPath();
    QString getProjectName();
    bool getEmptyProject();
private:
    QLineEdit* projectPath;
    QLineEdit* projectName;
    QCheckBox* emptyProject;
};

#endif // OPENNEWPROJECTDIALOG_H
