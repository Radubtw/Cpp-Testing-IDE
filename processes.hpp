#ifndef PROCESSES_H
#define PROCESSES_H

#include<QString>
#include <QProcess>
namespace processes
{
class Processes
{
private:
    QString output;
signals:

public:
    void unzipWithTar(const QString &zipFilePath, const QString &extractPath);
    void compileGTest(const QString &gtestDir);
    QString& compileTests(const QString &projectPath);
    QString& runTests(const QString &projectPath);
    QString& compileAndRunTests(const QString &projectPath);
    QString& compileProject(const QString &projectPath);
    QString& runProject(const QString &projectPath);
    QString& compileAndRunProject(const QString &projectPath);


    void readOutput(QProcess& process);
private slots:
};
}
#endif // PROCESSES_H
