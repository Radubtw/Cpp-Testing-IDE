#ifndef PROCESSES_H
#define PROCESSES_H

#include <QString>
#include <QProcess>
#include <QObject>
#include <QWidget>

class Processes : public QObject
{
    Q_OBJECT
private:
    QString output;
    QString projectPath;
signals:
    void outputChanged(QString output);
public:
    Processes(QString projectPath, QObject* parent = nullptr);
    void unzipWithTar(const QString &zipFilePath, const QString &extractPath);
    void compileGTest(const QString &gtestDir);
    void compileTests(const QString &projectPath);
    void runTests(const QString &projectPath);
    void compileAndRunTests(const QString &projectPath);
    void compileProject(const QString &projectPath);
    void runProject(const QString &projectPath);
    void compileAndRunProject(const QString &projectPath);

    QProcess* process;

private slots:
    void readOutput();

};

#endif // PROCESSES_H
