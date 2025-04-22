#ifndef TERMINAL_H
#define TERMINAL_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QBoxLayout>
#include <QProcess>
class Terminal : public QWidget
{
    Q_OBJECT
public:
    explicit Terminal(QString workingDir, QWidget *parent = nullptr);
    void startProcess(QString workingDir);
private:
    QWidget* widget;
    QBoxLayout* mainLayout;
    QLineEdit* inputLine;
    QTextEdit* terminalOutput;
    QProcess* process;
signals:
private slots:
    void sendCommand();
    void readOutput();
public slots:
    void toggleTerminal();
};

#endif // TERMINAL_H
